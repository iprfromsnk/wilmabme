/**************************************************************************//**
  \file pdsWriteData.c

  \brief Periodic data save implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <pdsMemAbstract.h>
#include <appTimer.h>
#include <pdsCrcService.h>
#include <pdsAuxService.h>
#include <leds.h>
#ifndef _MAC2_
  #include <apsBindManager.h>
#else  // _MAC2_
  #include <macAddr.h>
#endif // _MAC2_
#include <stddef.h>

/******************************************************************************
                   Defines section
******************************************************************************/
//Macros used to define records in pdsAuxArray
#define AUXRECORD(id) {id, PDS_FIELD_OFFSET(AuxOffsets_t, id)}
#define PDS_FIELD_OFFSET(struct_type, field_name) (offsetof(struct_type, field_name) + SYSTEM_BASE_EEPROM_ADDRESS)
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define AUX_TABLE_MARKER {0, -1}


/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  uint8_t id;
  int16_t offset;
} AuxType_t;

/*
 * Persistence save to eeprom some of ConfigServer values. Values to save enumerated in
 * array pdsAuxArray. pdsAuxArray consist of AuxType_t records. Every record have 2 values:
 * id of item to save, offset - where item in eeprom started, size of area occupied by item
 * calculated by difference from offset of next item.
 *
 * 3 entities used to construct pdsAuxArray. AUXRECORD - macros to define records, AuxOffsets_t
 * structure (below), pdsAuxArray itself. Item added to persistence in 2 steps:
 * - define item size in AuxOffsets_t structure. AUXRECORD use it to calculate offsets
 * - add AUXRECORD(name) to pdsAuxArray. Please pay attention: records in pdsAuxArray must be
 * in the same order and under same features as definition in AuxOffsets table.
 *
 * Mechanism used to automatically calculate offsets based on PDS_FIELD_OFFSET macros.
 * When all macroses gets expanded code looks like this:
 *
 * typedef struct {
 *    uint8_t id1,
 *    uint16_t id2,
 *    ExtAddr_t id3
 * } AuxOffsets_t ;
 * pdsAuxArray =
 * {
 *   id1, __field_offset(AuxOffsets_t, id1),
 *   id2, __field_offset(AuxOffsets_t, id2),
 *   id3, __field_offset(AuxOffsets_t, id3),
 * }
 */

// AuxOffsets_t structure used to automatically calculate offsets in pdsAuxArray.
// Variables of this structure never instantiated.
#ifdef _MAC2_
BEGIN_PACK
typedef struct PACK
{
  ExtAddr_t CS_UID_ID;
  int8_t CS_RF_TX_POWER_ID;
} AuxOffsets_t ;
END_PACK
#else
BEGIN_PACK
typedef struct PACK
{
  ExtAddr_t CS_UID_ID;
  ExtPanId_t CS_EXT_PANID_ID;
  uint32_t CS_CHANNEL_MASK_ID;
  uint8_t CS_CHANNEL_PAGE_ID;
  DeviceType_t CS_DEVICE_TYPE_ID;
  bool CS_RX_ON_WHEN_IDLE_ID;
  int8_t CS_RF_TX_POWER_ID;
  bool CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID;
  bool CS_USER_DESCRIPTOR_AVAILABLE_ID;
  UserDescriptor_t CS_ZDP_USER_DESCRIPTOR_ID;
  uint16_t CS_MANUFACTURER_CODE_ID;
  PanId_t CS_NWK_PANID_ID;
  bool CS_NWK_PREDEFINED_PANID_ID;
  uint8_t CS_SOFT_RESET_REASON_ID;
  ShortAddr_t CS_NWK_ADDR_ID;
  bool CS_NWK_UNIQUE_ADDR_ID;
  bool CS_DTR_WAKEUP_ID;
#if defined(_POWER_FAILURE_)
  ShortAddr_t CS_NWK_PARENT_ADDR_ID;
  uint8_t CS_NWK_DEPTH_ID;
  ExtPanId_t CS_NWK_EXT_PANID_ID;
  uint8_t CS_NWK_LOGICAL_CHANNEL_ID;
#endif //_POWER_FAILURE_
#if defined(_SECURITY_)
  uint8_t CS_NETWORK_KEY_ID[SECURITY_KEY_SIZE];
  ExtAddr_t CS_APS_TRUST_CENTER_ADDRESS_ID;
#ifdef _HIGH_SECURITY_
  uint8_t CS_LINK_KEY_ID[SECURITY_KEY_SIZE];
  uint8_t CS_MASTER_KEY_ID[SECURITY_KEY_SIZE];
#endif //_HIGH_SECURITY_
  uint8_t CS_ZDO_SECURITY_STATUS_ID;
#endif //_SECURITY_
#if defined(_POWER_FAILURE_)
  uint8_t CS_NEIB_TABLE_ID[CS_NEIB_TABLE_SIZE * sizeof(Neib_t)];
#ifdef _BINDING_
  uint8_t CS_APS_BINDING_TABLE_ID[CS_APS_BINDING_TABLE_SIZE];
#endif //_BINDING_
#if defined(_SECURITY_)
  NWK_SecurityIB_t CS_NWK_SECURITY_IB_ID;
#endif //_SECURITY_
#endif //_POWER_FAILURE_
  uint8_t CS_APS_GROUP_TABLE_ID[(CS_APS_GROUP_TABLE_SIZEOF * sizeof(uint8_t))];
#if defined(_SECURITY_)
#if defined(_TC_PERMISSION_TABLE_)
  uint8_t CS_TC_PERMISSION_TABLE_ID[sizeof(ExtAddr_t) * CS_MAX_TC_ALLOWED_DEVICES_AMOUNT];
#endif
#ifdef _HIGH_SECURITY_
  uint8_t CS_APS_KEY_PAIR_DESCRIPTORS_ID[(CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT * sizeof(ApsKeyPairDescriptor_t))];
#endif
#endif //_SECURITY_
} AuxOffsets_t ;
END_PACK
#endif //_MAC2_

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
Callback for timer and eeprom. Work with config server data step by step.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsOnTimerSave(void);

/*******************************************************************************
Look at current parameter id and set next.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsGetId(uint8_t index);

/******************************************************************************
                   Global variables section
******************************************************************************/
HAL_AppTimer_t     pdsEepromSaveServiceTimer;
PDS_CurrentState_t pdsCurrentState;
MEMORY_DESCRIPTOR  pdsStackEepromParams;
uint8_t            savingIsStarted = SAVE_IS_STOPED;

#ifdef _MAC2_
PROGMEM_DECLARE(const AuxType_t pdsAuxArray[]) =
{
  AUXRECORD(CS_UID_ID),
  AUXRECORD(CS_RF_TX_POWER_ID),
};
#else
PROGMEM_DECLARE(const AuxType_t pdsAuxArray[]) =
{
  AUXRECORD(CS_UID_ID),
  AUXRECORD(CS_EXT_PANID_ID),
  AUXRECORD(CS_CHANNEL_MASK_ID),
  AUXRECORD(CS_CHANNEL_PAGE_ID),
  AUXRECORD(CS_DEVICE_TYPE_ID),
  AUXRECORD(CS_RX_ON_WHEN_IDLE_ID),
  AUXRECORD(CS_RF_TX_POWER_ID),
  AUXRECORD(CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID),
  AUXRECORD(CS_USER_DESCRIPTOR_AVAILABLE_ID),
  AUXRECORD(CS_ZDP_USER_DESCRIPTOR_ID),
  AUXRECORD(CS_MANUFACTURER_CODE_ID),
  AUXRECORD(CS_NWK_PANID_ID),
  AUXRECORD(CS_NWK_PREDEFINED_PANID_ID),
  AUXRECORD(CS_SOFT_RESET_REASON_ID),
  AUXRECORD(CS_NWK_ADDR_ID),
  AUXRECORD(CS_NWK_UNIQUE_ADDR_ID),
  AUXRECORD(CS_DTR_WAKEUP_ID),
#if defined(_POWER_FAILURE_)
  AUXRECORD(CS_NWK_PARENT_ADDR_ID),
  AUXRECORD(CS_NWK_DEPTH_ID),
  AUXRECORD(CS_NWK_EXT_PANID_ID),
  AUXRECORD(CS_NWK_LOGICAL_CHANNEL_ID),
#endif //_POWER_FAILURE_
#if defined(_SECURITY_)
  AUXRECORD(CS_NETWORK_KEY_ID),
  AUXRECORD(CS_APS_TRUST_CENTER_ADDRESS_ID),
#ifdef _HIGH_SECURITY_
  AUXRECORD(CS_LINK_KEY_ID),
  AUXRECORD(CS_MASTER_KEY_ID),
#endif //_HIGH_SECURITY_
  AUXRECORD(CS_ZDO_SECURITY_STATUS_ID),
#endif //_SECURITY_

  //This is table marker, item to distinguish params(above) from tables(below).
  //Please pay attention when editing.
  AUX_TABLE_MARKER,

#if defined(_POWER_FAILURE_)
  AUXRECORD(CS_NEIB_TABLE_ID),
#ifdef _BINDING_
  AUXRECORD(CS_APS_BINDING_TABLE_ID),
#endif //_BINDING_
#if defined(_SECURITY_)
  AUXRECORD(CS_NWK_SECURITY_IB_ID),
#endif //_SECURITY_
#endif //_POWER_FAILURE_
  AUXRECORD(CS_APS_GROUP_TABLE_ID),
#if defined(_SECURITY_)
#if defined(_TC_PERMISSION_TABLE_)
  AUXRECORD(CS_TC_PERMISSION_TABLE_ID),
#endif //_TC_PERMISSION_TABLE_
#ifdef _HIGH_SECURITY_
  AUXRECORD(CS_APS_KEY_PAIR_DESCRIPTORS_ID),
#endif //_HIGH_SECURITY_
#endif //_SECURITY_
};
#endif //_MAC2_

//number of records in pdsAuxArray
const uint8_t pdsParamCount = ARRAY_SIZE(pdsAuxArray);

//Size of PDS ConfigServer area, calculated from AuxOffsets_t
const uint16_t pdsDataSize = sizeof(AuxOffsets_t) + SYSTEM_BASE_EEPROM_ADDRESS;
/*******************************************************************************
Start global data save timer.
Parameters:
  callback - The callback method starts when timer fired
  typeInterval - set timer interval. Must be chosen from:
     PDS_LONG_INTERVAL  - 5 minutes
     PDS_SHORT_INTERVAL - 50 msec
Returns:
  none.
*******************************************************************************/
void pdsStartPdsTimer(void (*callback)(void), uint8_t typeInterval)
{
  pdsEepromSaveServiceTimer.callback = callback;
  if (PDS_LONG_INTERVAL ==  typeInterval)
    pdsEepromSaveServiceTimer.interval = STORE_TIMER_TIMEOUT;
  else
    pdsEepromSaveServiceTimer.interval = SHORT_TIMEOUT;
  pdsEepromSaveServiceTimer.mode = TIMER_ONE_SHOT_MODE;
  HAL_StartAppTimer(&pdsEepromSaveServiceTimer);
}

/*******************************************************************************
Start server work.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsStartPersistServer(void)
{
  pdsCurrentState.currentAction = PDS_CS_PARAMETER;
  pdsStartPdsTimer(pdsOnTimerSave, PDS_LONG_INTERVAL);
}

bool pdsCsVariableCompare(void)
{
  static PDS_Default_t fromMemory;
  PDS_Default_t fromEeprom;

  pdsStackEepromParams.data = &(fromEeprom.uint8);
  CS_ReadParameter((CS_ParameterId_t) pdsCurrentState.id, &fromMemory);

  pdsWaitMemoryFree();

  READ_MEMORY(&pdsStackEepromParams, NULL);

  pdsWaitMemoryFree();

  if (0 != memcmp(&(fromMemory.uint8), &(fromEeprom.uint8), pdsStackEepromParams.length)) /* equal */
  {
    pdsStackEepromParams.data = &(fromMemory.uint8);
    WRITE_MEMORY(&pdsStackEepromParams, pdsOnTimerSave);
    return true;
  }

  return false;
}

bool pdsCsMemoryCompare(void)
{
  uint8_t *fromMemory;
  uint8_t fromEeprom;
  uint16_t length;
  uint16_t address;

  pdsStackEepromParams.data = &fromEeprom;
  length = pdsStackEepromParams.length;
  address = pdsStackEepromParams.address;
  pdsStackEepromParams.length = 1;
  CS_GetMemory((CS_MemoryId_t)pdsCurrentState.id, (void *)(&fromMemory));

  uint16_t inc;
  for (inc = 0; inc < length; inc++)
  {
    pdsWaitMemoryFree();

    READ_MEMORY(&pdsStackEepromParams, NULL);

    pdsWaitMemoryFree();

    if (fromMemory[inc] != fromEeprom)
    {
      pdsStackEepromParams.data = fromMemory;
      pdsStackEepromParams.length = length;
      pdsStackEepromParams.address = address;
      WRITE_MEMORY(&pdsStackEepromParams, pdsOnTimerSave);
      return true;
    }

    pdsStackEepromParams.address++;
  }
  return false;
}

/*******************************************************************************
Read data from eeprom, read data from config server.
If they are not equally starts saving.
Parameters:
  none.
Returns:
  true - saving starts
  false - data equally
*******************************************************************************/
bool pdsNeedSaveParam(void)
{
  static uint8_t index = 0;

  pdsGetId(index);

  if (pdsCurrentState.isTableMarker)
  {
    pdsCurrentState.currentAction = PDS_CS_MEMORY;
    pdsGetId(++index);
  }

  if (PDS_CS_PARAMETER == pdsCurrentState.currentAction)
  {
    if (pdsCsVariableCompare())
      return true;
  }

  if (PDS_CS_MEMORY == pdsCurrentState.currentAction)
  {
    if (pdsCsMemoryCompare())
      return true;
  }

  index++;

  if (pdsParamCount == index)
  {
    index = 0;
    pdsCurrentState.currentAction = PDS_STOP_SAVE;
    return true;
  }

  return false;
}

/*******************************************************************************
Callback for timer and eeprom. Work with config server data step by step.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsOnTimerSave(void)
{
#ifdef USE_LED
  BSP_OnLed(LED_YELLOW);
#endif
  savingIsStarted = SAVE_IS_STARTED;

  while (!pdsNeedSaveParam());

  if (PDS_STOP_SAVE == pdsCurrentState.currentAction)
  {
    if (PDS_EEPROM_ERROR == pdsWriteCrc())
    {
      pdsStartPdsTimer(pdsOnTimerSave, PDS_SHORT_INTERVAL);
    }
    else
    {
      pdsStartPersistServer();

#ifdef USE_LED
      BSP_OffLed(LED_YELLOW);
#endif

      savingIsStarted = SAVE_IS_STOPED;
    }
  }
}

/*******************************************************************************
Check is passed value is special - table marker
Parameters:
  item to check.
Returns:
  true if passed value is table marker, false otherwise.
*******************************************************************************/
static bool isTableMarker(AuxType_t *item)
{
  AuxType_t tableMarker = AUX_TABLE_MARKER;
  return (item->id == tableMarker.id && item->offset == tableMarker.offset);
}

/*******************************************************************************
Look at current parameter id and set next.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsGetId(uint8_t index)
{
  AuxType_t item;
  memcpy_P(&item, &pdsAuxArray[index], sizeof(AuxType_t));

  pdsCurrentState.id = item.id;
  pdsStackEepromParams.address = item.offset;
  pdsCurrentState.isTableMarker = isTableMarker(&item);

  //calc item size from offsets
  if (index == ARRAY_SIZE(pdsAuxArray)-1)
  {
    pdsStackEepromParams.length = pdsDataSize - item.offset;
  }
  else
  {
    AuxType_t nextItem;
    memcpy_P(&nextItem, &pdsAuxArray[index+1], sizeof(AuxType_t));
    //if next record is table marker, get next one
    if (isTableMarker(&nextItem))
      memcpy_P(&nextItem, &pdsAuxArray[index+2], sizeof(AuxType_t));
    pdsStackEepromParams.length = nextItem.offset - item.offset;
  }
}
// eof pdsDataServer.c
