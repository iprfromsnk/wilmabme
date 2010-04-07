/**************************************************************************//**
  \file lowpower.h

  \brief Lowpower application header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _LOWPOWER_H
#define _LOWPOWER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <types.h>
#include <configServer.h>                               // Config Server header
#include <appFramework.h>                               // Main stack types
#include <zdo.h>                                        // Main ZDO header
#include <aps.h>                                        // Main APS header

#include "boardabstraction.h"

/******************************************************************************
                    Defines section
******************************************************************************/

#define APP_ENDPOINT                        2       // Endpoint will be used
#define APP_PROFILE_ID                      1       // Profile Id will be used
#define APP_CLUSTER_ID                      1       // Cluster Id will be used

/*****************************************************************************\*
Types section
******************************************************************************/
typedef enum
{
  APP_STATE_INITIAL,           // Application initial state (after Power On or Reset)
  APP_STATE_START_WAIT,        // Waiting while the Button0 was not pressed
  APP_STATE_NETWORK_JOINING,   // Joining network state
  APP_STATE_NETWORK_JOINED,    // Network available
} AppState_t;

// SensorValueReport sent from endpoint to coordinator
BEGIN_PACK
typedef struct
{
  AppSensorType_t type;
  int16_t value;
} PACK AppSensorMessage_t;
END_PACK

// ChangeSensorType message sent from coordinator to endpoints
BEGIN_PACK
typedef struct
{
  AppSensorType_t type;
} PACK AppSensorTypeMessage_t;
END_PACK


// Aplication message buffer
BEGIN_PACK
typedef struct
{
  // Auxilliary header (stack required)
  uint8_t           header[APS_ASDU_OFFSET];
  // Actually application message
  union {
    AppSensorMessage_t report;
    AppSensorTypeMessage_t cmd;
  } msg;
  // Auxilliary footer (stack required)
  uint8_t           footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET];
} PACK AppMessageBuffer_t;
END_PACK

typedef struct _ClientOps_t
{
  void (*init)(void);
  void (*taskHandler)(void);
  void (*dataInd)(APS_DataInd_t* ind);
  void (*buttonHandler)(AppButton_t b);
  void (*networkStateChanged)(AppState_t newState);
} AppClientOps_t;

/*****************************************************************************\*
External variables section
******************************************************************************/

extern APS_DataReq_t apsDataReq; // APS Data Request primitive (for application message sending)
extern AppMessageBuffer_t appMessageBuffer; // Application message buffer

/******************************************************************************
                    Functions prototypes section
******************************************************************************/

AppClientOps_t* appGetCoordinatorOps(void);
AppClientOps_t* appGetEndDeviceOps(void);

#endif // _LOWPOWER_H

// eof lowpower.h
