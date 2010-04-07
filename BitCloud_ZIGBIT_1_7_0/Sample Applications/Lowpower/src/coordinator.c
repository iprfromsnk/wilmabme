/**************************************************************************//**
  \file coordinator.c

  \brief Lowpower application: Coordinator part of application implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifdef _COORDINATOR_

/******************************************************************************
  Includes section
******************************************************************************/

#include <stdio.h>
#include <apsMacros.h>

#include "lowpower.h"
#include "boardabstraction.h"

/***********************************************************************************
  Define(s) section
 ***********************************************************************************/

#define CHANGE_SENSOR_SECS 20

/***********************************************************************************
  Local variables
 ***********************************************************************************/

static bool networkJoined = false;
static bool messageBufferOccupied = false;
static AppSensorType_t currentType = 0;

//Memory needed to send cmds to all childrens
static NodeAddr_t childAddrTable[CS_MAX_CHILDREN_AMOUNT - CS_MAX_CHILDREN_ROUTER_AMOUNT];
static ZDO_GetChildrenAddr_t children =
{
  .childrenTable = childAddrTable,
};
static uint8_t childrenIndex = 0;

/******************************************************************************
  Static functions prototypes section
******************************************************************************/
static void startSending(void);
static void APS_DataConf(APS_DataConf_t *conf); // Data transmission confirmation handler

/********************************************************************
  Description:  Device type specific initialization
  Parameters:   none
  Returns:      none
********************************************************************/
static void init(void)
{
  bool rxOnWhenIdle = true;
  DeviceType_t appDeviceType = DEVICE_TYPE_COORDINATOR;

  //set device type specific params to config server
  CS_WriteParameter(CS_DEVICE_TYPE_ID, &appDeviceType);
  CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdle);

  // Prepare APS Data Request
  apsDataReq.APS_DataConf            = APS_DataConf;                         // Confirm handler

  //if we don't have buttons change sensor every
#ifndef _BUTTONS_
  static HAL_AppTimer_t changeSensorTimerDesc =
  {
    .interval = CHANGE_SENSOR_SECS * 1000,
    .mode = TIMER_REPEAT_MODE,
    .callback = startSending,
  };
  HAL_StartAppTimer(&changeSensorTimerDesc);
#endif
}

/********************************************************************
  Description:  Data indication handler
  Parameters:   ind - APS Data Indication primitive
  Returns:      none
********************************************************************/
static void dataInd(APS_DataInd_t* ind)
{
  AppSensorMessage_t *msg = (AppSensorMessage_t*)ind->asdu;
  boardAbstractionShowMessage(ind->srcAddress.shortAddress, msg->type, msg->value);
}

static void sendStep(void)
{
  if (childrenIndex >= children.childrenCount || messageBufferOccupied || !networkJoined)
    return;

  apsDataReq.dstAddress.shortAddress = children.childrenTable[childrenIndex].shortAddr;
  boardAbstractionShowIndication(APP_INDICATION_DATA_TRANSMITED);
  messageBufferOccupied = true;
  APS_DataReq(&apsDataReq);
}

/********************************************************************
  Description:  Initiate process of changing sensors by end devices.
  Parameters:   none
  Returns:      none
********************************************************************/
static void startSending(void)
{
  if (networkJoined && !messageBufferOccupied)
  {
    currentType = (currentType + 1) % APP_SENSOR_TYPE_MAX;
    appMessageBuffer.msg.cmd.type = currentType;

    children.childrenCount = ARRAY_SIZE(childAddrTable),
    ZDO_GetChildrenAddr(&children);
    childrenIndex = 0;

    sendStep();
  }
}
/********************************************************************
  Description:  Notification about packet delivery
  Parameters:   none
  Returns:      none
********************************************************************/
static void APS_DataConf(APS_DataConf_t *conf)
{
  conf = conf;
  messageBufferOccupied = false;
  childrenIndex++;
  sendStep();
}


/********************************************************************
  Description:  Handler of button presses
  Parameters:   b - pressed button
  Returns:      none
********************************************************************/
static void buttonHandler(AppButton_t b)
{
  // Device wake up button
  if (APP_BUTTON_1 == b)
    startSending();
}

/********************************************************************
  Description:  Common layer informs us about network state change
  if device lost network we must stop current activities
  Parameters:   none
  Returns:      none
********************************************************************/
static void networkStateChanged(AppState_t newState)
{
  networkJoined = (APP_STATE_NETWORK_JOINED == newState);
}

/***********************************************************************************
  Global functions
 ***********************************************************************************/

/********************************************************************
  Description:  Return pointer to partially filled table of
  device type specific operations
  Parameters:   none
  Returns:      Partially filled ClientOps variable
********************************************************************/
AppClientOps_t* appGetCoordinatorOps(void)
{
  static AppClientOps_t ClientOps =
  {
    .init = init,
    .dataInd = dataInd,
    .buttonHandler = buttonHandler,
    .networkStateChanged = networkStateChanged,
  };

  return &ClientOps;
}

#endif // _COORDINATOR_

// eof coordinator.c
