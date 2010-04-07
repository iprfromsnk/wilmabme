/**************************************************************************//**
  \file boardstubs.h

  \brief various stubs for BSP_* functions

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

******************************************************************************/
#ifndef _BOARDSTUBS_H_
#define _BOARDSTUBS_H_

#include "leds.h"
#include "lcd.h"
#include "buttons.h"
#include "sliders.h"

#ifdef APP_USE_VCP
  #include <vcpVirtualUsart.h>
#endif


#if defined(APP_USE_USART)
  #define USART_Open HAL_OpenUsart
  #define USART_Write HAL_WriteUsart
  #define USART_Close HAL_CloseUsart
#elif defined(APP_USE_VCP)
  #define USART_Open VCP_OpenUsart
  #define USART_Write VCP_WriteUsart
  #define USART_Close VCP_CloseUsart
#elif defined(APP_USE_NONE)
  #define USART_Open(d)
  #define USART_Write(d,b,s)
  #define USART_Close(d)
#endif

#ifdef _LEDS_
  #define appOpenLeds() BSP_OpenLeds()
  #define appCloseLeds() BSP_CloseLeds()
  #define appOnLed(id) BSP_OnLed(id)
  #define appOffLed(id) BSP_OffLed(id)
  #define appToggleLed(id) BSP_ToggleLed(id)
#else
  #define appOpenLeds() do{}while(0)
  #define appCloseLeds() do{}while(0)
  #define appOnLed(id) do{(void)id;}while(0)
  #define appOffLed(id) do{(void)id;}while(0)
  #define appToggleLed(id) do{(void)id;}while(0)
#endif // _LEDS_

#ifdef _BUTTONS_
  #define appOpenButtons(pressed, released) BSP_OpenButtons(pressed, released)
  #define appCloseButtons() BSP_CloseButtons()
  #define appReadButtonsState() BSP_ReadButtonsState()
#else
  #define appOpenButtons(pressed, released) do{(void)pressed; (void)released;}while(0)
  #define appCloseButtons()
  #define appReadButtonsState() 0
#endif // _BUTTONS_

#ifdef _SLIDERS_
  #define appReadSliders() BSP_ReadSliders()
#else
  #define appReadSliders() APP_NWK_NODE_ADDRESS
#endif // _SLIDERS_

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


#endif /* _BOARDSTUBS_H_ */
