/**********************************************************************//**
  \file WSNRouterEndDeviceApp.c

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

#ifdef _ROUTER_
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>

extern AppMessageRequest_t  appMessage;
extern AppState_t appState;
extern APS_DataReq_t  messageParams;
extern HAL_AppTimer_t deviceTimer;
extern bool subTaskRequested;
extern void appLeaveNetwork(void);

static void deviceTimerFired(void);
static void APS_DataConf(APS_DataConf_t *confInfo);
void APS_DataIndRouter(APS_DataInd_t *indData);
static void appSensorsesGot(void);
void appInitDeviceRouter(void);


/***********************************************************************************
  Process router functionality.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
void appRouterTaskHandler(AppEvent_t event, void *param)
{
  switch (appDeviceState)
  {
    case WAITING_DEVICE_STATE:
      switch (event)
      {
        case APP_READING_DONE:
          appDeviceState = SENDING_DEVICE_STATE;
          appStopSensorManager();
          appPostSubTaskTask();
          break;

        case APP_SENDING_DONE:
          if (APS_SUCCESS_STATUS == ((APS_DataConf_t *)param)->status)
          {
            APL_WRITE_LOG(0x71)
            visualizeAirTxFInished();

            failedTransmission = 0;
            appMessage.data.parentShortAddr = NWK_GetNextHop(0x0000);
            appReadLqiRssi();
            appDeviceState = STARTING_TIMER_STATE;
          }
          else
          {
            appDeviceState = SENDING_DEVICE_STATE;
            APL_WRITE_LOG(0x72)

            if (APP_THRESHOLD_FAILED_TRANSMISSION < ++failedTransmission)
            {
              appDeviceState = INITIAL_DEVICE_STATE;
              failedTransmission = 0;
              appLeaveNetwork();
              return;
            }
          }
          appPostSubTaskTask();
          break;

        case APP_TIMER_FIRED:
          appDeviceState = READING_SENSORS_STATE;
          appPostSubTaskTask();
          break;

        default:
          break;
      }
      break;

    case READING_SENSORS_STATE:
      switch (event)
      {
        case APP_PROCESS:
          appReadLqiRssi();
          appStartSensorManager();
      	  appDeviceState = WAITING_DEVICE_STATE; // need to put here in a case if run context isn't broken
          appGetSensorData(appSensorsesGot);
          break;

        default:
          break;
      }
      break;

    case SENDING_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          visualizeAirTxStarted();
          APL_WRITE_LOG(0x70)

          APS_DataReq(&messageParams);
          appDeviceState = WAITING_DEVICE_STATE;
          break;

        default:
          break;
      }
      break;

    case STARTING_TIMER_STATE:
      switch (event)
      {
        case APP_PROCESS:
          HAL_StartAppTimer(&deviceTimer);
          appDeviceState = WAITING_DEVICE_STATE;
          break;

        default:
          break;
      }
      break;

    case INITIAL_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          HAL_StopAppTimer(&deviceTimer); // Have to be stopped before start
          deviceTimer.interval = APP_TIMER_SENDING_PERIOD;
          deviceTimer.mode     = TIMER_ONE_SHOT_MODE;
          deviceTimer.callback = deviceTimerFired;

          // Prefilling request parameters
          messageParams.profileId               = simpleDescriptor.AppProfileId;
          messageParams.dstAddrMode             = APS_SHORT_ADDRESS;
          messageParams.dstAddress.shortAddress = 0;
          messageParams.dstEndpoint             = 1;
          messageParams.clusterId               = 1;
          messageParams.srcEndpoint             = 1;
          messageParams.asduLength              = sizeof(appMessage.data);
          messageParams.asdu                    = (uint8_t *)(&appMessage.data);
          messageParams.txOptions.acknowledgedTransmission = 1;
          messageParams.radius                  = 0x0;
          messageParams.APS_DataConf            = APS_DataConf;

          appDeviceState = READING_SENSORS_STATE;
          appPostSubTaskTask();
          break;

        default:
          break;
      }
      break;

    case REINITIAL_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          break;

        default:
          appDeviceState = INITIAL_DEVICE_STATE;
          appPostSubTaskTask();
          break;
      }

    default:
      break;
  }
}

// appRouterTaskHandler must be called from main state machine after this function
void appInitDeviceRouter(void)
{
  if (WAITING_DEVICE_STATE == appDeviceState)
    appDeviceState = REINITIAL_DEVICE_STATE;
  else
  {
    appDeviceState = INITIAL_DEVICE_STATE;
    appPostSubTaskTask();
  }
}

void APS_DataIndRouter(APS_DataInd_t *indData)
{
  indData = indData;
}

static void appSensorsesGot(void)
{
  appRouterTaskHandler(APP_READING_DONE, NULL);
}

/***********************************************************************************
  Device timer event.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
static void deviceTimerFired(void)
{
  appRouterTaskHandler(APP_TIMER_FIRED, NULL);
}

/***********************************************************************************
  Confirmation of message sent.

  Parameters:
    confInfo - confirmation information

  Return:
    none

 ***********************************************************************************/
static void APS_DataConf(APS_DataConf_t *confInfo)
{
  appRouterTaskHandler(APP_SENDING_DONE, confInfo);
}

#endif
//eof WSNRouterEndDeviceApp.c
