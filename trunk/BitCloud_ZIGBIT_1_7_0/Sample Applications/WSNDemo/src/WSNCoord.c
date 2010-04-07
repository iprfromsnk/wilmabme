/**********************************************************************//**
  \file WSNCoordinatorApp.c

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
#ifdef _COORDINATOR_

#include <WSNDemoApp.h>
#include <WSNVisualizer.h>

extern AppMessageRequest_t  appMessage;
extern HAL_AppTimer_t deviceTimer;
extern bool subTaskRequested;

static void deviceTimerFired(void);
static void appSensorsesGot(void);
void appInitDeviceCoordinator(void);

/***********************************************************************************
  Process coordinator functionality.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
void appCoordinatorTaskHandler(AppEvent_t event, void *param)
{
  param = param; // warning prevention

  switch (appDeviceState)
  {
    case READING_SENSORS_STATE:
      switch (event)
      {
        case APP_PROCESS:
          appReadLqiRssi();
          appStartSensorManager();
          appGetSensorData(appSensorsesGot);
          break;

        case APP_READING_DONE:
          appDeviceState = SENDING_DEVICE_STATE;
          appStopSensorManager();
          appPostSubTaskTask();
          break;

        default:
          break;
      }
      break;

    case SENDING_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          visualizeSerialTx();
          appSendMessageToUsart(&appMessage.data);
          appDeviceState = STARTING_TIMER_STATE;
          appPostSubTaskTask();
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
          break;

        case APP_TIMER_FIRED:
          appDeviceState = READING_SENSORS_STATE;
          appPostSubTaskTask();
          break;

        default:
          break;
      }
      break;

    case WAITING_DEVICE_STATE:
      switch (event)
      {
        default:
          appDeviceState = INITIAL_DEVICE_STATE;
          appPostSubTaskTask();
          break;
      }
      break;

    case INITIAL_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          HAL_StopAppTimer(&deviceTimer);

          deviceTimer.interval = APP_TIMER_SENDING_PERIOD;
          deviceTimer.mode     = TIMER_ONE_SHOT_MODE;
          deviceTimer.callback = deviceTimerFired;
          appDeviceState = READING_SENSORS_STATE;
          appPostSubTaskTask();
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }
}


void appInitDeviceCoordinator(void)
{
  appDeviceState = INITIAL_DEVICE_STATE;
  appPostSubTaskTask();
}

static void appSensorsesGot(void)
{
  appCoordinatorTaskHandler(APP_READING_DONE, NULL);
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
  appCoordinatorTaskHandler(APP_TIMER_FIRED, NULL);
}


/***********************************************************************************
  Radio data has been received. It should be resent into USART.

  Parameters:
    indData - received data parameters and payload

  Return:
    none

 ***********************************************************************************/
void APS_DataIndCoord(APS_DataInd_t *indData)
{
  visualizeAirRxFinished();
  APL_WRITE_LOG(0x62)
  appSendMessageToUsart((AppMessage_t *)indData->asdu);
}

#endif

//eof WSNCoordinator.c
