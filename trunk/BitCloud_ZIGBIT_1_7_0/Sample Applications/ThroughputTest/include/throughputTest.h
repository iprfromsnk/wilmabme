/**************************************************************************//**
  \file throughputTest.h

  \brief Throughput Test Application header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _THROUGHPUTTEST_H
#define _THROUGHPUTTEST_H

#include "taskManager.h"
#include "configServer.h"
#include "appFramework.h"

#include "aps.h"
#include "zdo.h"
#include "uid.h"

#ifdef _LEDS_
#include "leds.h"
#endif //#ifdef _LEDS_

#include "sliders.h"
#include "usart.h"
#include "appTimer.h"
#include "dbg.h"

#ifdef _LCD_
#include "lcd.h"
#endif //#ifdef _LCD_

#define END_POINT 1  // End-point address for transmission and reception

#define NETWORK_LED LED_GREEN
#define DATA_TX_LED LED_YELLOW
#define DATA_RX_LED LED_YELLOW
#define TIMER_LED   LED_RED

#define MSG_LENGTH 50 // UART message length.

#ifndef TIMER_TRACK_PERIOD
#define TIMER_TRACK_PERIOD 1000  // Period of sending amount of received packets (ms)
#endif

#if defined(_LEDS_)
  #define appOpenLeds() BSP_OpenLeds()
  #define appCloseLeds() BSP_CloseLeds()
  #define appOnLed(id) BSP_OnLed(id)
  #define appOffLed(id) BSP_OffLed(id)
  #define appToggleLed(id) BSP_ToggleLed(id)
#elif defined(_LCD_)
  #define LED_RED    1
  #define LED_YELLOW 2
  #define LED_GREEN  3
  #define appOpenLeds()  BSP_OpenLcd()
  #define appCloseLeds()
  #define appOnLed(id)     if (LED_GREEN == id) BSP_SendLcdCmd(LCD_CMD_LED_ON)
  #define appOffLed(id)    if (LED_GREEN == id) BSP_SendLcdCmd(LCD_CMD_LED_OFF)
  #define appToggleLed(id) if (LED_GREEN == id) BSP_SendLcdCmd(LCD_CMD_LED_TOGGLE)
#else
  #define appOpenLeds()
  #define appCloseLeds()
  #define appOnLed(id)
  #define appOffLed(id)
  #define appToggleLed(id)
#endif // _LEDS_

/***********************************************************************************
  Global variables
***********************************************************************************/
extern APS_RegisterEndpointReq_t endpointParams; // Endpoint parameters

/***********************************************************************************
  Global functions
***********************************************************************************/
void appCoordTaskHandler(void); // Application task handler for coordinator
void appRouterTaskHandler(void); // Application task handler for router
void appInitUARTManager(void);
void appWriteDataToUart(uint8_t* aData, uint8_t aLength); // Message transmission to UART
void APS_DataIndCoord(APS_DataInd_t *indData); // Indication callback for incoming data packet on coordinator
void printUint32(uint8_t *where, uint32_t value, uint8_t digits); //utility function, prints uint32_t values

#endif // _THROUGHPUTTEST_H
