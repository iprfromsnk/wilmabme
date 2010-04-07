/**********************************************************************//**
  \file WSNDemoApp.c
  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13/06/07 I. Kalganova - Modified
**************************************************************************/

#include <WSNDemoApp.h>
#include <WSNVisualizer.h>
#include <taskManager.h>
#include <zdo.h>
#include <configServer.h>
#include <aps.h>
#include <mac.h>

#if APP_USE_OTAU == 1
  #include <otauServer.h>
#endif

#if defined _POWER_FAILURE_ && defined _BUTTONS_
  #include <pdsDataServer.h>
  #include <resetReason.h>
#endif // defined _POWER_FAILURE_ && defined _BUTTONS_

#define TIMER_STARTING_NETWORK 500 // Period of blinking during starting network
#define TIMER_WAKEUP 50 // Wakeup period

/***********************************************************************************
  Types
***********************************************************************************/
typedef enum
{
  START_BLINKING,
  STOP_BLINKING
} BlinkingAction_t;


/***********************************************************************************
  Prototypes
***********************************************************************************/
void APS_DataIndCoord(APS_DataInd_t *indData);
void APS_DataIndRouter(APS_DataInd_t *indData);
void APS_DataIndDevice(APS_DataInd_t *indData);
void appPostSubTaskTask(void);
void appPostGlobalTask(void);
/***********************************************************************************
  Global variables
 ***********************************************************************************/
AppState_t     appState        = APP_INITING_STATE;//application state
DeviceState_t  appDeviceState  = INITIAL_DEVICE_STATE;

AppMessageRequest_t  appMessage;
//request parameters for APS_DataReq primitive
APS_DataReq_t messageParams;
HAL_AppTimer_t deviceTimer;
uint8_t failedTransmission = 0;
//static bool globalTaskRequested = false;

/***********************************************************************************
  Local variables
 ***********************************************************************************/
static DeviceType_t deviceType;
static ZDO_StartNetworkReq_t networkParams; //request params for ZDO_StartNetworkReq
//endpoint parameters
SimpleDescriptor_t simpleDescriptor = {1, 1, 1, 1, 0, 0 , NULL, 0, NULL};
static APS_RegisterEndpointReq_t endpointParams;
// Timer indicating starting network
static HAL_AppTimer_t startingNetworkTimer;
static ZDO_ZdpReq_t leaveReq;

/***********************************************************************************
  Local functions
 ***********************************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo);
static void startingNetworkTimerFired(void);
static void zdpLeaveResp(ZDO_ZdpResp_t *zdpResp);
static void initSubStateMachine(void);
static void appTaskHandler(AppEvent_t event, void *param);
static void manageBlinkingDuringRejoin(BlinkingAction_t action);

/***********************************************************************************
  Implementation
 ***********************************************************************************/


/***********************************************************************************
  Application task.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
void APL_TaskHandler(void)
{
  appTaskHandler(APP_PROCESS, NULL);
}

static void appTaskHandler(AppEvent_t event, void *param)
{
  bool rxOnWhenIdleFlag = true;
  uint8_t sliders;

  switch (appState)
  {
    //node is in network
    case APP_IN_NETWORK_STATE:
    {
      switch (event)
      {
        case APP_PROCESS:
        {
#ifdef _COORDINATOR_
          if (deviceType == DEVICE_TYPE_COORDINATOR)
            appCoordinatorTaskHandler(APP_PROCESS, NULL);
#endif
#ifdef _ROUTER_
          if (deviceType == DEVICE_TYPE_ROUTER)
            appRouterTaskHandler(APP_PROCESS, NULL);
#endif
#ifdef _ENDDEVICE_
          if (deviceType == DEVICE_TYPE_END_DEVICE)
            appEndDeviceTaskHandler(APP_PROCESS, NULL);
#endif
          break;
        }

        case APP_NETWORK_STATE_UPDATED:
        {
          ZDO_MgmtNwkUpdateNotf_t *updateParam = param;

          switch (updateParam->status)
          {
            case ZDO_NETWORK_LOST_STATUS:
              APL_WRITE_LOG(0x03)
              appState = APP_STOP_STATE;
              break;

            case ZDO_NETWORK_LEFT_STATUS:
              APL_WRITE_LOG(0x04)
              appState = APP_STARTING_NETWORK_STATE;
              visualizeNwkLeft();
              failedTransmission = 0;
              appPostGlobalTask();
              break;

            case ZDO_NWK_UPDATE_STATUS:
            case ZDO_NETWORK_STARTED_STATUS:
              // Update parameters being sent to coordinator
              appMessage.data.shortAddr       = updateParam->nwkUpdateInf.shortAddr;
              appMessage.data.panID           = updateParam->nwkUpdateInf.panId;
              appMessage.data.parentShortAddr = updateParam->nwkUpdateInf.parentShortAddr;
              appMessage.data.workingChannel  = updateParam->nwkUpdateInf.currentChannel;
              break;

            default:
              break;
          }
        }

        default:
          break;
      }
      break;
    }

    case APP_INITING_STATE: //node has initial state
    {
      switch (event)
      {
        case APP_PROCESS:
        {
          visualizeAppStarting();
#ifdef _COORDINATOR_
          if (DEVICE_TYPE_COORDINATOR == appMessage.data.nodeType)
            appStartUsartManager();  //init USART manager
          else
#endif // _COORDINATOR_
          SYS_InitLog();

#if defined _POWER_FAILURE_ && defined _BUTTONS_
          bool powerFailure;

          CS_ReadParameter(CS_POWER_FAILURE_ID, &powerFailure);

          if (powerFailure)
          {
            appOpenButtons(NULL, NULL);
            // check up the first button on a pressed state
            if (appReadButtonsState() & 0x01)
            {
              // the button is pressed
              PDS_SetToDefault();
              HAL_WarmReset(); // Reset the system.
            }
            appCloseButtons();
          }
#endif // defined _POWER_FAILURE_ && defined _BUTTONS_

          endpointParams.simpleDescriptor = &simpleDescriptor;

          // Setting device type
	  sliders = appReadSliders();

          if (SLIDER0 & sliders)
          { // Coordinator
#ifdef _COORDINATOR_
#ifdef _SECURITY_
            uint64_t tcAddr;
            CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &tcAddr);
            CS_WriteParameter(CS_UID_ID, &tcAddr);
#endif
            appMessage.data.nodeType = DEVICE_TYPE_COORDINATOR;
            endpointParams.APS_DataInd = APS_DataIndCoord;
#endif
          }
          else
          {
            if (SLIDER1 & sliders)
            {  // Router
#ifdef _ROUTER_
              appMessage.data.nodeType = DEVICE_TYPE_ROUTER;
              endpointParams.APS_DataInd = APS_DataIndRouter;
#endif
            }
            else
            { // All other states are end device
#ifdef _ENDDEVICE_
              appMessage.data.nodeType = DEVICE_TYPE_END_DEVICE;
              endpointParams.APS_DataInd = APS_DataIndDevice;
#endif
            }
          }
          // For not coordinator CS_UID is set to equal UID chip by ZDO before
          { // To remove unalignment access warning for ARM.
            ExtAddr_t extAddr;

            CS_ReadParameter(CS_UID_ID, &extAddr);
            appMessage.data.extAddr = extAddr;
          }
          APS_RegisterEndpointReq(&endpointParams);

          // it is needed because devType is 2 bytes and nodeType is 1 byte
          deviceType = appMessage.data.nodeType;
          CS_WriteParameter(CS_DEVICE_TYPE_ID, &deviceType);

          if (DEVICE_TYPE_END_DEVICE == appMessage.data.nodeType)
          {
            rxOnWhenIdleFlag = false;
            CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdleFlag);
          }
          else
          {
            rxOnWhenIdleFlag = true;
            CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdleFlag);
          }

          APL_WRITE_LOG(0x00)
#if APP_USE_OTAU == 1
          OTAU_Init();
#endif

          appMessage.data.messageType     = APP_DATA_MESSAGE_TYPE;
          appMessage.data.channelMask     = CS_CHANNEL_MASK;
          appMessage.data.softVersion     = 0x01010100;
          appMessage.data.boardType       = MESHBEAN_SENSORS_TYPE;
          appMessage.data.sensorsSize     = sizeof(appMessage.data.meshbean);

          startingNetworkTimer.interval = TIMER_STARTING_NETWORK;
          startingNetworkTimer.mode     = TIMER_REPEAT_MODE;
          startingNetworkTimer.callback = startingNetworkTimerFired;

          appState = APP_STARTING_NETWORK_STATE;
          appPostGlobalTask();
          break;
        }

        default:
          break;
      }
      break;
    }

    case APP_STARTING_NETWORK_STATE:
    {
      switch (event)
      {
        case APP_PROCESS:
          manageBlinkingDuringRejoin(START_BLINKING);
          visualizeNwkStarting();
          failedTransmission = 0;

          APL_WRITE_LOG(0x01)
          // Start network
          networkParams.ZDO_StartNetworkConf = ZDO_StartNetworkConf;
          ZDO_StartNetworkReq(&networkParams);
          break;

        case APP_NETWORK_STARTING_DONE:
        {
          ZDO_StartNetworkConf_t *startInfo = param;
          manageBlinkingDuringRejoin(STOP_BLINKING);
          if (ZDO_SUCCESS_STATUS == startInfo->status)
          {
            APL_WRITE_LOG(0x02)
            appState = APP_IN_NETWORK_STATE;
            failedTransmission = 0;

            visualizeNwkStarted();
            // Network parameters, such as short address, should be saved
            appMessage.data.panID           = startInfo->PANId;
            appMessage.data.shortAddr       = startInfo->shortAddr;
            appMessage.data.parentShortAddr = startInfo->parentAddr;
            appMessage.data.workingChannel  = startInfo->activeChannel;
            initSubStateMachine();
          }
          else
            appPostGlobalTask();
          break;
        }

        case APP_NETWORK_STATE_UPDATED:
        {
          ZDO_MgmtNwkUpdateNotf_t *updateParam = param;
          switch (updateParam->status)
          {
            case ZDO_NETWORK_STARTED_STATUS:
              APL_WRITE_LOG(0x0C)
              // Network parameters, such as short address, should be saved
              appMessage.data.panID           = updateParam->nwkUpdateInf.panId;
              appMessage.data.shortAddr       = updateParam->nwkUpdateInf.shortAddr;
              appMessage.data.parentShortAddr = updateParam->nwkUpdateInf.parentShortAddr;
              appMessage.data.workingChannel  = updateParam->nwkUpdateInf.currentChannel;
              manageBlinkingDuringRejoin(STOP_BLINKING);

              appState = APP_IN_NETWORK_STATE;
              failedTransmission = 0;
              visualizeNwkStarted();
              initSubStateMachine();
              break;
            default:
              break;
          }
        }
        default: break;
      }
      break;
    }
    case APP_LEAVING_NETWORK_STATE:
    {
      ZDO_MgmtLeaveReq_t *zdpLeaveReq = &leaveReq.req.reqPayload.mgmtLeaveReq;

      switch(event)
      {
        case APP_PROCESS:
          APL_WRITE_LOG(0x0A)
          visualizeNwkLeaving();
          leaveReq.ZDO_ZdpResp =  zdpLeaveResp;
          leaveReq.reqCluster = MGMT_LEAVE_CLID;
          leaveReq.dstAddrMode = EXT_ADDR_MODE;
          leaveReq.dstExtAddr = 0;
          zdpLeaveReq->deviceAddr = 0;
          zdpLeaveReq->rejoin = 0;
          zdpLeaveReq->removeChildren = 1;
          zdpLeaveReq->reserved = 0;
          ZDO_ZdpReq(&leaveReq);
          break;

        case APP_LEAVE_DONE:
          if (ZDO_SUCCESS_STATUS == ((ZDO_ZdpResp_t *)param)->respPayload.status)
          {
            APL_WRITE_LOG(0x0B)
            appState = APP_STOP_STATE;
          }
          appPostGlobalTask();
          break;

        case APP_NETWORK_STATE_UPDATED:
        {
          ZDO_MgmtNwkUpdateNotf_t *updateParam = param;

          switch (updateParam->status)
          {
            case ZDO_NETWORK_LOST_STATUS:
              APL_WRITE_LOG(0x03)
              appState = APP_STOP_STATE;
              break;
            case ZDO_NETWORK_LEFT_STATUS:
              APL_WRITE_LOG(0x04)
              appState = APP_STARTING_NETWORK_STATE;
              appPostGlobalTask();
              break;
            default:
              break;
          }
          break;
        }

        default:
          break;
      }
      break;
    }

    case APP_STOP_STATE:
    {
      switch(event)
      {
        case APP_NETWORK_STATE_UPDATED:
        {
          ZDO_MgmtNwkUpdateNotf_t *updateParam = param;

          switch (updateParam->status)
          {
            case ZDO_NETWORK_STARTED_STATUS:
              APL_WRITE_LOG(0x0C)
              appState = APP_IN_NETWORK_STATE;
              appMessage.data.shortAddr       = updateParam->nwkUpdateInf.shortAddr;
              appMessage.data.panID           = updateParam->nwkUpdateInf.panId;
              appMessage.data.parentShortAddr = updateParam->nwkUpdateInf.parentShortAddr;
              appMessage.data.workingChannel  = updateParam->nwkUpdateInf.currentChannel;
              appPostGlobalTask();
              break;

            case ZDO_NETWORK_LEFT_STATUS:
              APL_WRITE_LOG(0x04)
              appState = APP_STARTING_NETWORK_STATE;
              appPostGlobalTask();
              break;

            default:
              break;
          }
        }
        default:
          break;
      }
      break;
    }

    default:
      break;
  }
}

// The response means that the command has been received successfully but not precessed yet
static void zdpLeaveResp(ZDO_ZdpResp_t *zdpResp)
{
  appTaskHandler(APP_LEAVE_DONE, zdpResp);
}

/***********************************************************************************
  ZDO_StartNetwork primitive confirmation was received.

  Parameters:
    confirmInfo - confirmation information

  Return:
    none

 ***********************************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo)
{
  appTaskHandler(APP_NETWORK_STARTING_DONE, confirmInfo);
}


void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  appTaskHandler(APP_NETWORK_STATE_UPDATED, nwkParams);
}

void ZDO_WakeUpInd(void)
{
#ifdef _ENDDEVICE_
  if (APP_IN_NETWORK_STATE == appState)
  {
    appEndDeviceTaskHandler(APP_WOKEUP, NULL);
  }
#endif
}

// For blinking
static void startingNetworkTimerFired(void)
{
  visualizeNwkStarting();
}

void initSubStateMachine(void)
{
#ifdef _COORDINATOR_
  if (deviceType == DEVICE_TYPE_COORDINATOR)
    appInitDeviceCoordinator();
#endif
#ifdef _ROUTER_
  if (deviceType == DEVICE_TYPE_ROUTER)
    appInitDeviceRouter();
#endif
#ifdef _ENDDEVICE_
  if (deviceType == DEVICE_TYPE_END_DEVICE)
    appInitDeviceEndDevice();
#endif
}

void appReadLqiRssi(void)
{
  ZDO_GetLqiRssi_t lqiRssi;

  lqiRssi.nodeAddr = appMessage.data.parentShortAddr;
  ZDO_GetLqiRssi(&lqiRssi);

  appMessage.data.lqi  = lqiRssi.lqi;
  appMessage.data.rssi = lqiRssi.rssi;
}

static void manageBlinkingDuringRejoin(BlinkingAction_t action)
{
  static bool run = false;

  if (START_BLINKING == action)
  {
    if (!run)
    {
      HAL_StartAppTimer(&startingNetworkTimer);
      run = true;
    }
  }

  if (STOP_BLINKING == action)
  {
    run = false;
    HAL_StopAppTimer(&startingNetworkTimer);
  }
}

void appPostGlobalTask(void)
{
  SYS_PostTask(APL_TASK_ID);
}

void appPostSubTaskTask(void)
{
  SYS_PostTask(APL_TASK_ID);
}

void appLeaveNetwork(void)
{
  if (APP_IN_NETWORK_STATE == appState)
  {
    appState = APP_LEAVING_NETWORK_STATE;
    appPostGlobalTask();
  }
}

//eof WSNDemoApp.c

