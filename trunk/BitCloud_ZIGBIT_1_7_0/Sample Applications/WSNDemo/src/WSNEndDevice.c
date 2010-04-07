/**********************************************************************//**
  \file WSNEndDeviceApp.c

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
#ifdef _ENDDEVICE_
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>

//request parameters for APS_DataReq primitive
extern APS_DataReq_t  messageParams;
extern AppMessageRequest_t  appMessage;
extern AppState_t appState;
extern bool subTaskRequested;
extern void appLeaveNetwork(void);

static ZDO_SleepReq_t sleepReq;

static void APS_DataConf(APS_DataConf_t *confInfo);
static void ZDO_SleepConf(ZDO_SleepConf_t *conf);
static void appSensorsesGot(void);
void APS_DataIndDevice(APS_DataInd_t *indData);
void appInitDeviceEndDevice(void);


/***********************************************************************************
  Process end device functionality.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
void appEndDeviceTaskHandler(AppEvent_t event, void *param)
{
  switch (appDeviceState)
  {
    case WAITING_DEVICE_STATE:
      switch (event)
      {
        case APP_SENDING_DONE:
          if (APS_SUCCESS_STATUS == ((APS_DataConf_t *)param)->status)
          {
            APL_WRITE_LOG(0x71)
            visualizeAirTxFInished();
            failedTransmission = 0;
            appDeviceState = SLEEPPING_DEVICE_STATE;
          }
          else
          {
            APL_WRITE_LOG(0x72)
            if (APP_THRESHOLD_FAILED_TRANSMISSION < ++failedTransmission)
            {
              appDeviceState = INITIAL_DEVICE_STATE;
              failedTransmission = 0;
              appLeaveNetwork();
              return;
            }
            else
              appDeviceState = SENDING_DEVICE_STATE;
          }
          appPostSubTaskTask();
          break;

        case APP_SLEEP_DONE:
          if (ZDO_SUCCESS_STATUS == ((ZDO_SleepConf_t *)param)->status)
          {
            appDeviceState = SLEEPPING_DEVICE_STATE;
//            visualizeSleep();
          }
          else
          {
            appDeviceState = SLEEPPING_DEVICE_STATE;
            APL_WRITE_LOG(0x7E)
            appPostSubTaskTask();
          }
          break;

        case APP_READING_DONE:
          appStopSensorManager();
          appDeviceState = SENDING_DEVICE_STATE;
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
          appStartSensorManager();
          appReadLqiRssi();
      	  appDeviceState = WAITING_DEVICE_STATE;
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

    case SLEEPPING_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          APL_WRITE_LOG(0x7C)
          visualizeSleep();
          if (!isVisualizerReadyToSleep())// Wait for Visualizer ready
          {
            appDeviceState = WAITING_VISUALIZER_STATE;
            appPostSubTaskTask();
          }
          else
          {
            appDeviceState = WAITING_DEVICE_STATE;
            ZDO_SleepReq(&sleepReq);
          }
          break;

        case APP_WOKEUP:
          visualizeWakeUp();

          APL_WRITE_LOG(0x7F)

          appDeviceState = READING_SENSORS_STATE;
          appPostSubTaskTask();
          break;

        default:
          break;
      }
      break;

    case WAITING_VISUALIZER_STATE:
      switch (event)
      {
        case APP_PROCESS:
          if (!isVisualizerReadyToSleep())// Wait for Visualizer ready
          {
            appPostSubTaskTask();
          }
          else
          {
            appDeviceState = WAITING_DEVICE_STATE;
            ZDO_SleepReq(&sleepReq);
          }
          break;
        default:
          break;
      }
      break;
    case INITIAL_DEVICE_STATE:
      switch (event)
      {
        case APP_PROCESS:
          sleepReq.ZDO_SleepConf = ZDO_SleepConf;
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

// appEndDeviceTaskHandler must be called from main state machine after this function
void appInitDeviceEndDevice(void)
{
  if (WAITING_DEVICE_STATE == appDeviceState)
    appDeviceState = REINITIAL_DEVICE_STATE;
  else
  {
    appDeviceState = INITIAL_DEVICE_STATE;
    appPostSubTaskTask();
  }
}

static void appSensorsesGot(void)
{
  appEndDeviceTaskHandler(APP_READING_DONE, NULL);
}

void ZDO_SleepConf(ZDO_SleepConf_t *conf)
{
  appEndDeviceTaskHandler(APP_SLEEP_DONE, conf);
}

static void APS_DataConf(APS_DataConf_t *confInfo)
{
  appEndDeviceTaskHandler(APP_SENDING_DONE, confInfo);
}

void ZDO_SleepInd(void)
{
}

void APS_DataIndDevice(APS_DataInd_t *indData)
{
  indData = indData;
}

#endif

//eof WSNEndDevice.c
