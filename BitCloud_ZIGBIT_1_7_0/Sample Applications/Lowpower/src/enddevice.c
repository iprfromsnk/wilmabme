/**************************************************************************//**
  \file enddevice.c

  \brief Lowpower application: end device part of application implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifdef _ENDDEVICE_

#include "lowpower.h"
#include "boardabstraction.h"

/***********************************************************************************
  Types definition
 ***********************************************************************************/
typedef enum
{
  END_DEVICE_STATE_WAIT_JOIN,        // Wait while higher layer join network
  END_DEVICE_STATE_START_MEASURE,    // Device is not in sleep state and the temperature must be measured
  END_DEVICE_STATE_MEASURING,        // Temperature measuring
  END_DEVICE_STATE_MESSAGE_SENDING,  // Current temperature sending to the coordinator
  END_DEVICE_STATE_SLEEP_PREPARE,    // Message was sent successfully. Node ready to sleep.
  END_DEVICE_STATE_SLEEP,            // Actually sleep state
  END_DEVICE_STATE_AWAKENING         // Node was interrupted. Awakening.
} EndDeviceState_t;

typedef enum                                            // Data transmission feature state
{
  TRANSMISSION_STATE_IDLE,                     // Data transmission was finished or(and) not started yet
  TRANSMISSION_STATE_BUSY                      // Data transmission in progress
} TransmissionState_t;

/***********************************************************************************
  Local variables
 ***********************************************************************************/
static EndDeviceState_t endDeviceState = END_DEVICE_STATE_WAIT_JOIN;    // Current device state
static TransmissionState_t transmissionState = TRANSMISSION_STATE_IDLE;
static ZDO_SleepReq_t zdoSleepReq;                          // Request parameters for stack sleep
static ZDO_WakeUpReq_t zdoWakeUpReq;                        // Request parameters for stack awakening
static bool typeChanged = false;
static AppSensorType_t currentType = 0;

/***********************************************************************************
  Static function declarations
***********************************************************************************/
static void ZDO_SleepConf(ZDO_SleepConf_t *conf);           // Sleep confirmation handler
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);         // Wake up confirmation handler
static void APS_DataConf(APS_DataConf_t *conf);             // Data transmission confirmation handler

static void sensorHandler(bool result, int16_t value);
static void prepareToSleep(void);

/***********************************************************************************
  Local functions
 ***********************************************************************************/

/********************************************************************
  Description:  End device initialization routine
  Parameters:   none
  Returns:      none
********************************************************************/
static void init(void)
{
  bool rxOnWhenIdle = false;
  DeviceType_t appDeviceType = DEVICE_TYPE_END_DEVICE;

  CS_WriteParameter(CS_DEVICE_TYPE_ID, &appDeviceType);
  CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdle);

  // Prepare APS Data Request
  apsDataReq.dstAddress.shortAddress = 0;                                    // Destination node short address
  apsDataReq.APS_DataConf            = APS_DataConf;                         // Confirm handler
}

/********************************************************************
  Description:  Device common task handler
  Parameters:   none
  Returns:      none
********************************************************************/
static void taskHandler(void)
{
  switch (endDeviceState)                     // Actual device state when one joined network
  {
    case END_DEVICE_STATE_START_MEASURE:            // Device ready to temperature measuring
      typeChanged = false;
      appMessageBuffer.msg.report.type = currentType;
      endDeviceState = END_DEVICE_STATE_MEASURING;
      boardAbstractionReadSensor(currentType, sensorHandler);
      break;

    case END_DEVICE_STATE_MESSAGE_SENDING:        // Message sending state
      if (TRANSMISSION_STATE_IDLE == transmissionState)  // If previous data transmission was finished
      {
        transmissionState = TRANSMISSION_STATE_BUSY;     // Data transmission entity is busy while sending not finished
        APS_DataReq(&apsDataReq);
        boardAbstractionShowIndication(APP_INDICATION_DATA_TRANSMITED);
      }
      break;

    case END_DEVICE_STATE_SLEEP_PREPARE:          // Prepare to sleep state
      if (boardAbstrationIsIdle())                    // Wait for periphery to enter idle
        prepareToSleep();                     // Prepare to sleep
      else
        SYS_PostTask(APL_TASK_ID);            // Still in current state.
      break;

    case END_DEVICE_STATE_AWAKENING:              // Awakening state
      zdoWakeUpReq.ZDO_WakeUpConf = ZDO_WakeUpConf; // ZDO WakeUp confirm handler defining
      ZDO_WakeUpReq(&zdoWakeUpReq);                 // ZDO WakeUp Request sending
      break;

    case END_DEVICE_STATE_MEASURING:              // wait for callback from sensor
    case END_DEVICE_STATE_SLEEP:                  // this must not happen at all
    case END_DEVICE_STATE_WAIT_JOIN:              // wait for notification from common layer
      break;
  }
}

/********************************************************************
  Description:  Data sent handler
  Parameters:   conf - APS Data Confirm primitive
  Returns:      none
********************************************************************/
static void APS_DataConf(APS_DataConf_t *conf)
{
  transmissionState = TRANSMISSION_STATE_IDLE; // Data transmission entity is idle

  if (APS_SUCCESS_STATUS != conf->status || typeChanged) // Data transmission was successfully performed
    endDeviceState = END_DEVICE_STATE_START_MEASURE; // Data transmission wasn't successfully finished. Retry.
  else{
    endDeviceState = END_DEVICE_STATE_SLEEP_PREPARE; // Switch device state to prepare for sleep
    boardAbstractionClose();                               // LEDs and Temperature Sensor closing
  }

  SYS_PostTask(APL_TASK_ID);
}


/********************************************************************
  Description:  Temperature measured handler
  Parameters:   result - measurement status (true - success, 0 - fail)
                temperature - value measured
  Returns:      none
********************************************************************/
static void sensorHandler(bool result, int16_t value)
{
  if (endDeviceState != END_DEVICE_STATE_MEASURING)
    return;

  // Temperature measured will be sent as an application message
  if (true == result)
    appMessageBuffer.msg.report.value = value;
  else
    appMessageBuffer.msg.report.value = 0;

  endDeviceState = END_DEVICE_STATE_MESSAGE_SENDING; //Switch device state to application message sending
  SYS_PostTask(APL_TASK_ID); // Application task posting
}

/********************************************************************
  Description:  Handler of button presses
  Parameters:   b - which button is pressed, either APP_BUTTON_0 or
  APP_BUTTON_0.
  Returns:      none
********************************************************************/
static void buttonHandler(AppButton_t b)
{
  // Device wake up button
  if (APP_BUTTON_1 == b && END_DEVICE_STATE_SLEEP == endDeviceState)
  {
    endDeviceState = END_DEVICE_STATE_AWAKENING; // Device state switching
    SYS_PostTask(APL_TASK_ID);              // Application task posting
  }
}

/********************************************************************
  Description:  ZDO Sleep Confirm handler
  Parameters:   conf - ZDO Sleep Confirm primitive
  Returns:      none
********************************************************************/
static void ZDO_SleepConf(ZDO_SleepConf_t *conf)
{
  if (ZDO_SUCCESS_STATUS == conf->status)   // Stack was slept successfully
  {
    endDeviceState = END_DEVICE_STATE_SLEEP;    // Device actually slept
  }
  else
  {
    SYS_PostTask(APL_TASK_ID);              // Still in current state.
                                            // Application task posting for attempt repeat.
  }
}

/********************************************************************
  Description:  Prepare to sleep
  Parameters:   none
  Returns:      none
********************************************************************/
static void prepareToSleep(void)
{
  zdoSleepReq.ZDO_SleepConf = ZDO_SleepConf;  // Sleep Confirm handler defining
  ZDO_SleepReq(&zdoSleepReq);                 // Sleep Request sending
}

/********************************************************************
  Description: Device wakeup handler.
  Parameters: none
  Returns:    none
********************************************************************/
static void wakeUpHandler(void)
{
  endDeviceState = END_DEVICE_STATE_START_MEASURE;
  boardAbstractionResume();
  SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description:  Common layer informs us about network state change
  if device lost network we must stop current activities
  Parameters:   none
  Returns:      none
********************************************************************/
static void networkStateChanged(AppState_t newState)
{
  if (APP_STATE_NETWORK_JOINING == newState)
    endDeviceState = END_DEVICE_STATE_WAIT_JOIN;
  else if (APP_STATE_NETWORK_JOINED == newState)
    endDeviceState = END_DEVICE_STATE_START_MEASURE;
}

/********************************************************************
  Description:  Data intication handler
  Parameters:   ind - APS Data Indication primitive
  Returns:      none
********************************************************************/
static void dataInd(APS_DataInd_t* ind)
{
  AppSensorTypeMessage_t *msg = (AppSensorTypeMessage_t *)ind->asdu;

  if (msg->type < APP_SENSOR_TYPE_MAX)
  {
    currentType = msg->type;
    typeChanged = true;
  }
}

/********************************************************************
  Description: End device wake up indication
  Parameters: none.
  Returns: none.
********************************************************************/
void ZDO_WakeUpInd(void)
{
  if (END_DEVICE_STATE_SLEEP == endDeviceState)
  {
    wakeUpHandler();
  }
}

/********************************************************************
  Description: Wake up confirmation handler
  Parameters: conf - confirmation parameters
  Returns: nothing.
********************************************************************/
void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf)
{
  if (ZDO_SUCCESS_STATUS == conf->status)
    wakeUpHandler();
  else
    SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description:  Return pointer to partially filled table of
  device type specific operations
  Parameters:   none
  Returns:      none
********************************************************************/
AppClientOps_t* appGetEndDeviceOps(void)
{
  static AppClientOps_t ClientOps =
  {
    .init = init,
    .taskHandler = taskHandler,
    .buttonHandler = buttonHandler,
    .networkStateChanged = networkStateChanged,
    .dataInd = dataInd,
  };

  return &ClientOps;
}

#endif // _ENDDEVICE_

// eof enddevice.c
