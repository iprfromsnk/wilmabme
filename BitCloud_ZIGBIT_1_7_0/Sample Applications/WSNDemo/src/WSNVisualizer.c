/**********************************************************************//**
  \file WSNVisualizer.c

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    18/12/08 A. Luzhetsky - Modified
**************************************************************************/

/************************************************************************
**************************************************************************/
#include <WSNDemoApp.h>

/************************************************************************
**************************************************************************/
void visualizeAppStarting(void);
void visualizeNwkStarting(void);
void visualizeNwkStarted(void);
void visualizeNwkLeaving(void);
void visualizeNwkLeft(void);
void visualizeAirTxStarted(void);
void visualizeAirTxFInished(void);
void visualizeAirRxFinished(void);
void visualizeSerialTx(void);
void visualizeWakeUp(void);
void visualizeSleep(void);

/************************************************************************
**************************************************************************/
void visualizeAppStarting(void)
{
  appOpenLeds();

  appOpenLcd();
  appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_2);
  appSendLcdCmd(LCD_CMD_SYMB_ZIGBEE_ON);
  appSendLcdCmd(LCD_CMD_LED_ON);
  appSendLcdCmd(LCD_CMD_SYMB_RAVEN_ON);
  appSendLcdMsg("WSNDEMO");
}

/************************************************************************
**************************************************************************/
void visualizeNwkStarting(void)
{
  appToggleLed(LED_RED);
  appOffLed(LED_YELLOW);
  appOffLed(LED_GREEN);

  appSendLcdCmd(LCD_CMD_LED_TOGGLE);
  appSendLcdMsg("JOINING");
}

/************************************************************************
**************************************************************************/
void visualizeNwkStarted(void)
{
  appOnLed(LED_RED);
  appOffLed(LED_YELLOW);
  appOffLed(LED_GREEN);

  appSendLcdCmd(LCD_CMD_LED_ON);
  appSendLcdCmd(LCD_CMD_SYMB_SPACE_SUN);
  #ifdef APP_DEV_TYPE_COORDINATOR
    appSendLcdMsg("COORD  ");
  #elif defined APP_DEV_TYPE_ROUTER
    appSendLcdMsg("ROUTER ");
  #elif defined APP_DEV_TYPE_ENDDEVICE
    appSendLcdMsg("ENDDEV ");
  #endif
}

/************************************************************************
**************************************************************************/
void visualizeNwkLeaving(void)
{
  appOffLed(LED_GREEN);

  appSendLcdCmd(LCD_CMD_LED_OFF);
  appSendLcdMsg("LEAVING");
}

/************************************************************************
**************************************************************************/
void visualizeNwkLeft(void)
{
  appOffLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeAirTxStarted(void)
{
  appOnLed(LED_GREEN);

  appSendLcdCmd(LCD_CMD_SYMB_TRX_TX);
}

/************************************************************************
**************************************************************************/
void visualizeAirTxFInished(void)
{
  appOffLed(LED_GREEN);

  appSendLcdCmd(LCD_CMD_SYMB_TRX_RX);
}

/************************************************************************
**************************************************************************/
void visualizeAirRxFinished(void)
{
  appToggleLed(LED_YELLOW);

  appSendLcdCmd(LCD_CMD_SYMB_TRX_RX);
  appSendLcdCmd(LCD_CMD_SYMB_TRX_TX);
}

/************************************************************************
**************************************************************************/
void visualizeSerialTx(void)
{
  appToggleLed(LED_GREEN);
}

/************************************************************************
**************************************************************************/
void visualizeWakeUp(void)
{
  appOpenLeds();
  appOnLed(LED_RED);

  appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_2);
  appSendLcdCmd(LCD_CMD_SYMB_ZIGBEE_ON);
  appSendLcdCmd(LCD_CMD_LED_ON);
  appSendLcdCmd(LCD_CMD_SYMB_RAVEN_ON);
  appSendLcdCmd(LCD_CMD_SYMB_SPACE_SUN);
  appSendLcdMsg("ENDDEV ");
}

/************************************************************************
**************************************************************************/
void visualizeSleep(void)
{
  appCloseLeds();

  appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_0);
  appSendLcdCmd(LCD_CMD_SYMB_SPACE_MOON);
  appSendLcdCmd(LCD_CMD_LED_OFF);
  appSendLcdCmd(LCD_CMD_SYMB_TRX_OFF);
}

/************************************************************************
**************************************************************************/
int isVisualizerReadyToSleep(void)
{
  return appIsLcdOperationCompleted();
}

// eof WSNVisualizer.c
