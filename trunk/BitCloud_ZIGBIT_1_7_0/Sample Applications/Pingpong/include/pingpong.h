/**************************************************************************//**
  \file pingpong.h
  
  \brief Ping-pong sample application header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
******************************************************************************/
#ifndef _PINGPONG_H
#define _PINGPONG_H

/******************************************************************************
                    Includes section
******************************************************************************/
#ifdef _SLIDERS_
#include "sliders.h"
#endif //#ifdef _SLIDERS_

#ifdef _BUTTONS_
#include "buttons.h"
#endif //#ifdef _BUTTONS_

#ifdef _LEDS_
#include "leds.h"
#endif //#ifdef _LEDS_

#include "lcd.h"

/******************************************************************************
                    Defines section
******************************************************************************/
#ifdef TEST_NETWORK
  #undef _BUTTONS_
  #undef _SLIDERS_
#endif // TEST_NETWORK

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
  #define appReadButtonsState() 0
  #define BSP_KEY0 0
  #define BSP_KEY1 1
#endif // _BUTTONS_

#ifdef _LCD_
  #define appOpenLcd                 BSP_OpenLcd
  #define appSendLcdCmd              BSP_SendLcdCmd
  #define appSendLcdMsg              BSP_SendLcdMsg
  #define appIsLcdOperationCompleted BSP_IsLcdOperationCompleted
#else  // !_LCD_
  INLINE void appSendLcdCmd(uint8_t cmdId) {(void)cmdId;}
  INLINE void appOpenLcd(void){}
  INLINE void appSendLcdMsg(const char *str) {(void)str;}
  INLINE int appIsLcdOperationCompleted(void) { return 1;}
#endif  // _LCD_

#ifdef _SLIDERS_
  #define appReadSliders() BSP_ReadSliders()
#else
  #define appReadSliders() (APP_DEVICE_NWK_ADDRESS | (APP_FINAL_DEVICE << 2))
#endif // _SLIDERS_


#ifdef _LEDS_
  #ifndef HON_IQL
    #define NETWORK_LED LED_GREEN
    #define DATA_LED    LED_YELLOW
    #define BIND_LED    LED_RED
  #else
    #define NETWORK_LED LED_GREEN
    #define DATA_LED    LED_RED
    #define BIND_LED    LED_RED
  #endif
#endif // _LEDS_


#ifndef TIMER_STARTING_NETWORK
  #define TIMER_STARTING_NETWORK 500 // LED blinking interval during network start, ms
#endif

#ifndef TIMER_FW_DELAY
  #define TIMER_FW_DELAY 1000 // Packet forwarding delay, ms
#endif

#define NETWORK_BUTTON BSP_KEY0   // Button used to start/join network
#define DATA_TX_BUTTON BSP_KEY1   // Button used to initiate packet transmission

#define APP_PAYLOAD_SIZE 1 // Appliation payload size in bytes

#define PINGPONG_ENDPOINT   1      // End-point for transmission and receive.

#define START_CLUSTER  0x2000
#define PINGPONG_PROFILE 0x3000
#define BROADCAST_SHORT_ADDRESS 0xffff
#define SLIDER_1_MASK 0x01
#define SLIDER_2_MASK 0x02
#define SLIDER_3_MASK 0x04
#define SLIDERS_MASK (SLIDER_1_MASK | SLIDER_2_MASK | SLIDER_3_MASK)
#define ADDRESS_SLIDERS_MASK (SLIDER_1_MASK | SLIDER_2_MASK)


typedef enum         // Type specifing application state
{
  APP_INITING_STATE,
  APP_AWAITING_NETWORK_START_STATE,
  APP_NETWORK_STARTING_STATE,
  APP_DEVICE_FINDING_STATE,
  APP_IN_NETWORK_STATE,
  APP_NO_NETWORK_STATE,
  APP_NETWORK_DATA_SENDING_STATE,
  APP_WAITING_CONFIRM_STATE,
  APP_SENDING_HEARTBEAT
} AppState_t;

#endif // _PINGPONG_H

// eof pingpong.h
