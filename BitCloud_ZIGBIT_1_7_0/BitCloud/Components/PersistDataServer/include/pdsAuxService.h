/***************************************************************************//**
  \file pdsAuxService.h

  \brief The header file describes the auxiliary service of Persistence Data Server

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal

  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/

#ifndef _PDSAUXSERVICE_H
#define _PDSAUXSERVICE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#ifndef _MAC2_
  #include <aps.h>
  #include <nwk.h>
  #include <apsSecurityManager.h>
  #include <appFramework.h>
#else  // _MAC2_
  #include <appTimer.h>
#endif // _MAC2_

/******************************************************************************
                   Define(s) section
******************************************************************************/
/* define for eeprom write highlight */
//#define USE_LED

// offsets table
#define SYSTEM_BASE_EEPROM_ADDRESS    0x0004

// crc area
#define PDS_CRC_AREA                  10
// user area
#define USER_BASE_EEPROM_ADDRESS      (pdsDataSize + PDS_CRC_AREA)

#define PDS_CS_PARAMETER             0
#define PDS_CS_MEMORY                1
#define PDS_STOP_SAVE                2

#define EEPROM_BUSY                  -2
#define EEPROM_ERROR                 -1

#define STORE_TIMER_TIMEOUT  300000ul  // 5 minutes
//#define STORE_TIMER_TIMEOUT  300ul
#define SHORT_TIMEOUT        50ul      // 50 msec
#define PDS_LONG_INTERVAL            0
#define PDS_SHORT_INTERVAL           1
#define SAVE_IS_STARTED              1
#define SAVE_IS_STOPED               0

#define MAX_CS_PDS_VARIABLE_SIZE     16

/******************************************************************************
                   Types section
******************************************************************************/
// crc property
typedef struct
{
  uint8_t crc;
  uint16_t position;
  PDS_DataServerState_t eepromState;
} PDS_ServiceCrc_t;

// crc property
typedef struct
{
  uint8_t id;
  uint8_t currentAction;
  bool isTableMarker;
} PDS_CurrentState_t;

// memory for default value
typedef union
{
  uint8_t resetCRC[PDS_CRC_AREA];
  uint8_t readBuff[MAX_CS_PDS_VARIABLE_SIZE];
  void *__void;
  uint8_t *pUint8;
  uint8_t uint8;
#ifndef _MAC2_
  UserDescriptor_t userDescriptor;
#endif // _MAC2_
} PDS_Default_t;

/******************************************************************************
                   External global variables section
******************************************************************************/
extern PDS_CurrentState_t pdsCurrentState;
extern MEMORY_DESCRIPTOR  pdsStackEepromParams;
extern HAL_AppTimer_t     pdsEepromSaveServiceTimer;
extern uint8_t            savingIsStarted;
extern const uint8_t      pdsParamCount;
extern const uint16_t     pdsDataSize;

#endif /*_PDSAUXSERVICE_H*/
