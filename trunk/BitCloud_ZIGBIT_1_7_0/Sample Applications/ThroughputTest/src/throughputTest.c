/**************************************************************************//**
  \file throughputTest.c

  \brief Throughput Test Application

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#include "throughputTest.h"

#ifdef TEST_NETWORK
  #undef _BUTTONS_
  #undef _SLIDERS_
#endif // TEST_NETWORK

#define TIMER_STARTING_NETWORK 500 // Period of blinking during starting network

typedef enum  // Application states
{
  APP_INITING_STATE,
  APP_NETWORK_STARTING_STATE,
  APP_IN_NETWORK_STATE,
  APP_NO_NETWORK_STATE
} AppState_t;

/***********************************************************************************
  Global variables
***********************************************************************************/
DeviceType_t   appDeviceType; // Device type (Coordinator/Router/End device)
APS_RegisterEndpointReq_t endpointParams; // Endpoint parameters

/***********************************************************************************
  Local variables
 ***********************************************************************************/
static AppState_t             appState = APP_INITING_STATE; // Current application state
static ZDO_StartNetworkReq_t  networkParams; // Start network request parameters

// Endpoint parameters
static SimpleDescriptor_t simpleDescriptor = {END_POINT, 1, 1, 1, 0, 0 , NULL, 0, NULL};

static HAL_AppTimer_t  startingNetworkTimer; // Timer indicating starting network
static HAL_AppTimer_t  delayTimer; // Timer period of waiting after network start

/***********************************************************************************
  Local functions
 ***********************************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo); // Network start/join confirmation callback

/********************************************************************
  Description: Network starting timer has fired. Toggle indication

  Parameters: none.

  Returns: nothing.
********************************************************************/
void startingNetworkTimerFired(void)
{
  appToggleLed(NETWORK_LED);
}

/********************************************************************
  Description: Application task handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void APL_TaskHandler(void)
{
  uint8_t sliders;

  switch (appState)
  {
    // Node has initial state
    case APP_INITING_STATE:

      appOpenLeds();
      endpointParams.simpleDescriptor = &simpleDescriptor;

#ifdef _SLIDERS_
      sliders = BSP_ReadSliders();
#else
  #ifdef APP_DEV_TYPE_COORDINATOR
      sliders = SLIDER0;
  #elif defined APP_DEV_TYPE_ROUTER
      sliders = 0;
  #else
    #error please choose device type either APP_DEV_TYPE_COORDINATOR or APP_DEV_TYPE_ROUTER
  #endif
#endif //_SLIDERS_

      // Setting device type
      if (sliders & SLIDER0)
      {
        // Coordinator
        appDeviceType = DEVICE_TYPE_COORDINATOR;
        endpointParams.APS_DataInd = APS_DataIndCoord;
#ifdef _SECURITY_
        {
          uint64_t tcAddr;
          CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &tcAddr);
          CS_WriteParameter(CS_UID_ID, &tcAddr);
        }
#endif
      }
      else
      {
        // All other states mean Router
        appDeviceType = DEVICE_TYPE_ROUTER;
        endpointParams.APS_DataInd = NULL;
      }
      CS_WriteParameter(CS_DEVICE_TYPE_ID, &appDeviceType);
      appInitUARTManager();  // Init UART manager

      // Configure and start network starting timer
      startingNetworkTimer.interval = TIMER_STARTING_NETWORK;
      startingNetworkTimer.mode     = TIMER_REPEAT_MODE;
      startingNetworkTimer.callback = startingNetworkTimerFired;
      HAL_StartAppTimer(&startingNetworkTimer);

      appState = APP_NETWORK_STARTING_STATE; // Switch state
      SYS_PostTask(APL_TASK_ID);
      break;

    case APP_NETWORK_STARTING_STATE:
      {
        // Configure network start parameters
        networkParams.ZDO_StartNetworkConf = ZDO_StartNetworkConf;

        // Start network
        ZDO_StartNetworkReq(&networkParams);
        break;
      }

    // Node is in network
    case APP_IN_NETWORK_STATE:

      // Process task dependent on device type
      switch (appDeviceType)
      {
        case DEVICE_TYPE_COORDINATOR:
          appCoordTaskHandler();
          break;

        case DEVICE_TYPE_ROUTER:
          appRouterTaskHandler();
          break;

        case DEVICE_TYPE_END_DEVICE:
        default:
          break;
      }

    // Node is out of network
    case APP_NO_NETWORK_STATE:
      break;

    default:
      break;
  }
}

/********************************************************************
  Description: Delay after network start/join has fired

  Parameters: none.

  Returns: nothing.
********************************************************************/
static void delayTimerFired(void)
{
  SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description: ZDO_StartNetwork primitive confirmation was received.

  Parameters: confirmInfo - confirmation information

  Returns: nothing.
********************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo)
{
  if (ZDO_SUCCESS_STATUS == confirmInfo->status)
  {
    HAL_StopAppTimer(&startingNetworkTimer);
    appOnLed(NETWORK_LED); // Indicate successful network join by turning LED on

    appState = APP_IN_NETWORK_STATE; // Switch state

    // Register endpoint
    APS_RegisterEndpointReq(&endpointParams);

    // Configure and start delay timer
    delayTimer.interval = TIMER_DELAY_PERIOD;
    delayTimer.mode     = TIMER_ONE_SHOT_MODE;
    delayTimer.callback = delayTimerFired;
    HAL_StartAppTimer(&delayTimer);
  }
  else
  {
    SYS_PostTask(APL_TASK_ID);
  }
}

/********************************************************************
  Description: ZDO_MgmtNwkUpdateNotf primitive confirmation was received

  Parameters: nwkParams - updated network parameters

  Returns: nothing.
********************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  // Network is lost/left
  if (ZDO_NETWORK_LOST_STATUS == nwkParams->status)
  {
    HAL_StartAppTimer(&startingNetworkTimer); // Start indication of network join process
    appState = APP_NETWORK_STARTING_STATE;    // In order to rejoin, switch application to network starting state

    SYS_PostTask(APL_TASK_ID);
  }
}


/********************************************************************
  Description: dummy wakeup event handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void ZDO_WakeUpInd(void)
{
}

/********************************************************************
  Description: dummy sleep event handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void ZDO_SleepInd(void)
{
}

/********************************************************************
  Description: prints uint32 number, passed count of less
  significant digits.
  Parameters: where - where to print,
              value - value to print
              digits - digits number to print
  Returns: nothing.
********************************************************************/
void printUint32(uint8_t *where, uint32_t value, uint8_t digits)
{
  while(digits--)
  {
    uint16_t digit = value & 0xf;
    if(digit >= 10)
      digit -= 10;
    where[digits] = digit + '0';
    value /= 10;
  }
}

// eof throughputTest.c
