/**************************************************************************//**
  \file blink.h
  
  \brief Blink application header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
******************************************************************************/

#ifndef _BLINK_H
#define _BLINK_H

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

#ifdef _LCD_
#include "lcd.h"
#endif //#ifdef _LCD_


/******************************************************************************
                    Defines section
******************************************************************************/
#define APP_BLINK_INTERVAL             (APP_BLINK_PERIOD / 2)       // Blink interval.
#define APP_MIN_BLINK_INTERVAL         (APP_MIN_BLINK_PERIOD / 2)   // Minimum blink interval.
#define APP_MAX_BLINK_INTERVAL         (APP_MAX_BLINK_PERIOD / 2)   // Maximum blink interval.

#ifndef _BUTTONS_
  #define BSP_KEY0 0
  #define BSP_KEY1 1
#endif //#ifndef _BUTTONS_

#define APP_HALF_PERIOD_BUTTON          BSP_KEY0                // Button that reduces blink interval to a half.
#define APP_DOUBLE_PERIOD_BUTTON        BSP_KEY1                // Button that doubles blink interval.

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


#endif // _BLINK_H

// eof blink.h
