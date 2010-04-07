/***************************************************************************//**
  \file WSNDemoApp.h

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
*******************************************************************************/
#ifndef _WSNDEMOAPP_H
#define _WSNDEMOAPP_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <macAddr.h>
#include <appFramework.h>
#include <configServer.h>
#include <appTimer.h>
#include <aps.h>
#include <uid.h>
#include <appTimer.h>
#include <zdo.h>
#include <dbg.h>

#ifdef _SLIDERS_
  #include "sliders.h"
#endif // _SLIDERS_

#ifdef _LEDS_
  #include "leds.h"
#endif // _LEDS_

#ifdef _BUTTONS_
  #include "buttons.h"
#endif // _BUTTONS_

//#ifdef _LCD_
  #include "lcd.h"
//#endif // _LCD_


/******************************************************************************
                    Defines section
******************************************************************************/
#ifdef TEST_NETWORK
  #undef _BUTTONS_
  #undef _SLIDERS_
  #define OMIT_READING_SENSORS
#endif // TEST_NETWORK

#define MESHBEAN_SENSORS_TYPE         1
#define MAX_USART_MESSAGE_QUEUE_COUNT 5
#define MAX_DEVICE_MESSAGE_LEN        10
#define APP_DATA_MESSAGE_TYPE         1
/* At worst each byte will be transformed to two bytes + size of crc
 * + size of 4 bytes: 0x10, 0x02, 0x10, 0x03. */
#define MAX_RAW_APP_MESSAGE_SIZE  (2 + 2 * sizeof(AppMessage_t) + 2 + 1)

#ifndef APP_TIMER_SENDING_PERIOD
#define APP_TIMER_SENDING_PERIOD         1000
#endif

typedef enum
{
  APP_PROCESS,
  APP_NETWORK_STARTING_DONE,
  APP_NETWORK_STATE_UPDATED,
  APP_LEAVE_DONE,
  APP_SENDING_DONE,
  APP_READING_DONE,
  APP_SLEEP_DONE,
  APP_WOKEUP,
  APP_TIMER_FIRED,
} AppEvent_t;


typedef enum
{
  APP_INITING_STATE,
  APP_STARTING_NETWORK_STATE,
  APP_IN_NETWORK_STATE,
  APP_LEAVING_NETWORK_STATE,
  APP_STOP_STATE
} AppState_t;

typedef enum
{
  INITIAL_DEVICE_STATE,
  SENDING_DEVICE_STATE,
  READING_SENSORS_STATE,
  SLEEPPING_DEVICE_STATE,
  STARTING_TIMER_STATE,
  WAITING_DEVICE_STATE,
  WAITING_VISUALIZER_STATE,
  REINITIAL_DEVICE_STATE
} DeviceState_t;

BEGIN_PACK
typedef struct
{
  uint8_t     messageType;
  uint8_t     nodeType;
  ExtAddr_t   extAddr;
  ShortAddr_t shortAddr;
  uint32_t    softVersion;
  uint32_t    channelMask;
  PanId_t     panID;
  uint8_t     workingChannel;
  ShortAddr_t parentShortAddr;
  uint8_t     lqi;
  int8_t      rssi;
  //additional field
  uint8_t     boardType;//1
  uint8_t     sensorsSize;//1
  struct {
    uint32_t  battery;
    uint32_t  temperature;
    uint32_t  light;
  } meshbean;
} PACK AppMessage_t;

typedef struct
{
  uint8_t        header[APS_ASDU_OFFSET];
  AppMessage_t   data;
  uint8_t        footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET];
} PACK AppMessageRequest_t;
END_PACK

extern uint16_t       appPANId;
extern ShortAddr_t    appShortAddr;
extern uint8_t        appChannel;
extern DeviceState_t  appDeviceState;
extern int16_t        appTemperatureValue;
extern int16_t        appLightValue;
extern uint8_t        appBatteryValue;
extern DeviceType_t   appDeviceType;
extern ShortAddr_t    appParentAddr;
extern uint64_t       appUid;
extern SimpleDescriptor_t simpleDescriptor;
extern uint8_t        failedTransmission;

/******************************************************************************
                    Functions' prototypes section
******************************************************************************/
extern void appStartSensorManager(void);
extern void appStopSensorManager(void);
extern void appGetSensorData(void (*sensorsesGot)(void));
extern void appCoordTaskHandler(void);
extern void appRouterTaskHandler(AppEvent_t event, void *param);
extern void appEndDeviceTaskHandler(AppEvent_t event, void *param);
extern void appFillAppMessage(AppMessage_t *newMessagePoint);
extern void appStartUsartManager(void);
extern void appStopRouter(void);
extern void appPostSubTaskTask(void);
extern void SYS_InitLog(void);
extern void appReadLqiRssi(void);
extern void appInitDeviceCoordinator(void);
extern void appInitDeviceRouter(void);
extern void appInitDeviceEndDevice(void);
extern void SYS_StartLog(void);
extern void SYS_StopLog(void);
extern void appSendMessageToUsart(AppMessage_t *newMessage);
extern void appCoordinatorTaskHandler(AppEvent_t event, void *param);

#ifdef _LEDS_
  #define appOpenLeds() BSP_OpenLeds()
  #define appCloseLeds() BSP_CloseLeds()
  #define appOnLed(id) BSP_OnLed(id)
  #define appOffLed(id) BSP_OffLed(id)
  #define appToggleLed(id) BSP_ToggleLed(id)
#else
  #define appOpenLeds()
  #define appCloseLeds()
  #define appOnLed(id)
  #define appOffLed(id)
  #define appToggleLed(id)
#endif // _LEDS_

#ifdef _BUTTONS_
  #define appOpenButtons(pressed, released) BSP_OpenButtons(pressed, released)
  #define appCloseButtons() BSP_CloseButtons()
  #define appReadButtonsState() BSP_ReadButtonsState()
#else
  #define appOpenButtons(pressed, released)
  #define appCloseButtons()
  #define appReadButtonsState()
#endif // _BUTTONS_

#ifdef _SLIDERS_
  #define appReadSliders() BSP_ReadSliders()
#else
  #define SLIDER0 (1 << 0)
  #define SLIDER1 (1 << 1)
  #define SLIDER2 (1 << 2)

  #ifdef APP_DEV_TYPE_COORDINATOR
    #define appReadSliders() SLIDER0

  #elif defined APP_DEV_TYPE_ROUTER
    #define appReadSliders() SLIDER1

  #elif defined APP_DEV_TYPE_ENDDEVICE
    #define appReadSliders() SLIDER2
  #endif

#endif // _SLIDERS_

#ifdef _LCD_
  #define appOpenLcd                 BSP_OpenLcd
  #define appSendLcdCmd              BSP_SendLcdCmd
  #define appSendLcdMsg              BSP_SendLcdMsg
  #define appIsLcdOperationCompleted BSP_IsLcdOperationCompleted
#else  // !_LCD_
  INLINE void appSendLcdCmd(uint8_t cmdId){(void)cmdId;}
  INLINE void appOpenLcd(void){}
  INLINE void appSendLcdMsg(const char *str){(void)str;}
  INLINE int appIsLcdOperationCompleted(void){return 1;}
#endif  // _LCD_


#endif /*_WSNDEMOAPP_H*/

// eof WSNDemoApp.h
