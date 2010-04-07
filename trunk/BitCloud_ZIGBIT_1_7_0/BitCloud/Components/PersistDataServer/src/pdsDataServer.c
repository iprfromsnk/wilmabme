/***************************************************************************//**
  \file pdsDataServer.c

  \brief Persistence Data Server implementation

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
#include <pdsDataServer.h>
#include <pdsCrcService.h>
#include <pdsAuxService.h>
#include <leds.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
Read data from eeprom and set to config server.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t PDS_ReadParamFromEeprom(void);

/*******************************************************************************
set default value system area and check new crc
Parameters:
  none.
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_SetToDefault(void);

/*******************************************************************************
Look at current parameter id and set next.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsGetId(uint8_t index);

/*******************************************************************************
Start server work.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsStartPersistServer(void);

/*******************************************************************************
Callback for timer and eeprom. Work with config server data step by step.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsOnTimerSave(void);

/******************************************************************************
                   Implementations section
******************************************************************************/
/*******************************************************************************
Read and check crc system area.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t PDS_Init(void)
{
  PDS_ServiceCrc_t crcRead, crcCheck;

#ifdef USE_LED
  BSP_OpenLeds();
#endif

  pdsCheckCrc(&crcCheck);
  if (PDS_EEPROM_ERROR == crcCheck.eepromState)
    return PDS_EEPROM_ERROR;

  pdsReadCrc(&crcRead);
  if (PDS_EEPROM_ERROR == crcRead.eepromState)
    return PDS_EEPROM_ERROR;

  if (0x00 == (uint8_t)(crcCheck.crc + crcRead.crc))
  {
    if (PDS_EEPROM_ERROR == PDS_ReadParamFromEeprom())
    {
      return PDS_EEPROM_ERROR;
    }
    else
    {
      pdsStartPersistServer();
      return PDS_SUCCESS;
    }
  }
  else
  {
    if (PDS_EEPROM_ERROR == PDS_SetToDefault())
    {
      return PDS_EEPROM_ERROR;
    }
    else
    {
      pdsStartPersistServer();
      return PDS_CRC_ERROR;
    }
  }
}

/*******************************************************************************
Read data from eeprom and set to config server.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t PDS_ReadParamFromEeprom(void)
{
  PDS_Default_t memory;
  uint8_t index = 0;

  pdsCurrentState.currentAction = PDS_CS_PARAMETER;

  while (pdsParamCount > index)
  {
    pdsGetId(index);

    if (pdsCurrentState.isTableMarker)
    {
      pdsCurrentState.currentAction = PDS_CS_MEMORY;
      pdsGetId(++index);
    }

    if (PDS_CS_PARAMETER == pdsCurrentState.currentAction)
      pdsStackEepromParams.data = &(memory.uint8);

    if (PDS_CS_MEMORY == pdsCurrentState.currentAction)
      CS_GetMemory((CS_MemoryId_t) pdsCurrentState.id, (void *)(&(pdsStackEepromParams.data)));

    pdsWaitMemoryFree();

    if (EEPROM_ERROR == READ_MEMORY(&pdsStackEepromParams, NULL))
      return PDS_EEPROM_ERROR;

    pdsWaitMemoryFree();

    if (PDS_CS_PARAMETER == pdsCurrentState.currentAction)
      CS_WriteParameter((CS_ParameterId_t) pdsCurrentState.id, &(memory.uint8));

    index++;
  }

  return PDS_SUCCESS;
}

/*******************************************************************************
set default value system area and check new crc
Parameters:
  none.
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_SetToDefault(void)
{
  PDS_Default_t listData;
  PDS_ServiceCrc_t crcCheck;
  uint8_t index = 0;

  CS_PdsDefaultValue();
  for (;;)
  {
    pdsGetId(index);
    if (pdsCurrentState.isTableMarker)
      break;

    CS_ReadParameter((CS_ParameterId_t) pdsCurrentState.id, &listData);
    pdsStackEepromParams.data = &(listData.uint8);

    pdsWaitMemoryFree();

    if (EEPROM_ERROR == WRITE_MEMORY(&pdsStackEepromParams, pdsDummy))
      return PDS_EEPROM_ERROR;

    pdsWaitMemoryFree();

    index++;
  }

  memset(listData.resetCRC, 0xFF, PDS_CRC_AREA);
  pdsStackEepromParams.data = listData.resetCRC;
  pdsStackEepromParams.address = pdsDataSize;
  pdsStackEepromParams.length = PDS_CRC_AREA;

  pdsWaitMemoryFree();

  if (EEPROM_ERROR == WRITE_MEMORY(&pdsStackEepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;

  pdsWaitMemoryFree();

  pdsCheckCrc(&crcCheck);
  if (PDS_EEPROM_ERROR == crcCheck.eepromState)
    return PDS_EEPROM_ERROR;

  crcCheck.crc = 0 - crcCheck.crc;
  pdsStackEepromParams.address = pdsDataSize;
  pdsStackEepromParams.data = &crcCheck.crc;
  pdsStackEepromParams.length = 1;

  pdsWaitMemoryFree();

  if (EEPROM_ERROR == WRITE_MEMORY(&pdsStackEepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;

  pdsWaitMemoryFree();

  return PDS_SUCCESS;
}

/*******************************************************************************
Data save to eeprom immediately
Parameters:
  none
Returns:
  none
*******************************************************************************/
void PDS_FlushData(void)
{
  if (SAVE_IS_STOPED == savingIsStarted)
  { /* Data isn't saving now. Timer is working. */
    HAL_StopAppTimer(&pdsEepromSaveServiceTimer);
    pdsOnTimerSave();
  }  /* Data isn't saving now. Timer is working. */

  while(SAVE_IS_STARTED == savingIsStarted)
  {
    SYS_ForceRunTask();
  }
}

/*******************************************************************************
Dummy function for callback.
*******************************************************************************/
void pdsDummy(void)
{}

/*******************************************************************************
Read data from user area.
Parameters:
  offset - data offset
  data - pointer to configserver data area
  length - data length
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_ReadUserData(uint16_t offset, uint8_t *data, uint16_t length, void (*callback)(void))
{
  MEMORY_DESCRIPTOR pdsUserEepromParams;

  pdsUserEepromParams.address = USER_BASE_EEPROM_ADDRESS + offset;
  pdsUserEepromParams.length = length;
  pdsUserEepromParams.data = data;

  while(SAVE_IS_STARTED == savingIsStarted)
  {
    SYS_ForceRunTask();
  }

  if (NULL == callback)
    callback = pdsDummy;

  pdsWaitMemoryFree();

  if (EEPROM_ERROR == READ_MEMORY(&pdsUserEepromParams, callback))
    return PDS_EEPROM_ERROR;

  if (callback == pdsDummy)
  {
    pdsWaitMemoryFree();
  }

  return PDS_SUCCESS;
}

/*******************************************************************************
Write data to user area.
Parameters:
  offset - data offset
  data - pointer to configserver data area
  length - data length
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_WriteUserData(uint16_t offset, uint8_t *data, uint16_t length, void (*callback)(void))
{
  MEMORY_DESCRIPTOR pdsUserEepromParams;

  pdsUserEepromParams.address = USER_BASE_EEPROM_ADDRESS + offset;
  pdsUserEepromParams.length = length;
  pdsUserEepromParams.data = data;

  while(SAVE_IS_STARTED == savingIsStarted)
  {
    SYS_ForceRunTask();
  }

  if (NULL == callback)
    callback = pdsDummy;

  pdsWaitMemoryFree();

  if (EEPROM_ERROR == WRITE_MEMORY(&pdsUserEepromParams, callback))
    return PDS_EEPROM_ERROR;

  if (callback == pdsDummy)
  {
    pdsWaitMemoryFree();
  }

  return PDS_SUCCESS;
}

// eof pdsDataServer.c
