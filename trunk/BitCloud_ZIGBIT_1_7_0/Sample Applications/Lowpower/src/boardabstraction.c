/**************************************************************************//**
  \file boardabstraction.c

  \brief Lowpower application: device abstraction layer

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

/*****************************************************************************\*
Includes section
******************************************************************************/

#include <appTimer.h>
#include <sensors.h>                                    // BSP sensors header
#include <usart.h>                                      // HAL USART header
#include <stdio.h>
#include <aps.h>

#include "boardabstraction.h"
#include "boardstubs.h"

/*****************************************************************************\*
Define(s) section
******************************************************************************/

#define APP_USART_TX_BUFFER_SIZE             500        // USART Tx buffer size
#define APP_JOINING_INDICATION_PERIOD       500L        // Period of blinking during starting network

// Leds aliases definition
#define LED_TYPE_NETWORK    LED_GREEN     // Network status LED
#define LED_TYPE_RECEIVED  LED_YELLOW    // Data receiving status LED
#define LED_TYPE_TRANSMITED    LED_RED       // Data transmission status LED

/*****************************************************************************\*
Types section
******************************************************************************/

typedef enum
{
  TURN_OFF_TX_MASK = (1<<0),
  TURN_OFF_RX_MASK = (1<<1),
} TurnOffMask_t ;

/*****************************************************************************\*
  Implementations section
******************************************************************************/

#ifndef APP_USE_NONE

// USART Tx buffer
static uint8_t usartTxBuffer[APP_USART_TX_BUFFER_SIZE];

// USART descriptor (required by stack)
static HAL_UsartDescriptor_t usartDescriptor =
{
  .tty             = APP_USART_CHANNEL,
  .mode            = USART_MODE_ASYNC,
  .baudrate        = USART_BAUDRATE_38400,
  .dataLength      = USART_DATA8,
  .parity          = USART_PARITY_NONE,
  .stopbits        = USART_STOPBIT_1,
  .rxBuffer        = NULL,
  .rxBufferLength  = 0,
  .txBuffer        = usartTxBuffer,
  .txBufferLength  = APP_USART_TX_BUFFER_SIZE,
  .rxCallback      = NULL,
  .txCallback      = NULL,
  .flowControl     = USART_FLOW_CONTROL_NONE,
};
#endif //APP_USE_NONE

//what to turnOff in turnOffTimer callback
static TurnOffMask_t offMask = 0;


/***********************************************************************************
  Local functions
 ***********************************************************************************/


/********************************************************************
  Description:  Timer callback. Turn off receive/transmit leds and LCD symbols
  Parameters:   none
  Returns:      none
********************************************************************/
static void turnOffTimerFired(void)
{
  //LED
  if (offMask & TURN_OFF_RX_MASK)
    appOffLed(LED_TYPE_RECEIVED);
  if (offMask & TURN_OFF_TX_MASK)
    appOffLed(LED_TYPE_TRANSMITED);

  //LCD
  appSendLcdCmd(LCD_CMD_SYMB_TRX_OFF);

  offMask = 0;
}

/********************************************************************
  Description:  turn on receive/transmit leds and LCD symbols
  Parameters:   type - type of indication to show
  Returns:      none
********************************************************************/
static void turnOnShortIndication(AppIndication_t type)
{
  static HAL_AppTimer_t turnOffTimerDesc =
  {
    .interval = 500,
    .mode = TIMER_ONE_SHOT_MODE,
    .callback = turnOffTimerFired,
  };

  //LED
  if (APP_INDICATION_DATA_RECEIVED == type)
    appOnLed(LED_TYPE_RECEIVED);
  else if (APP_INDICATION_DATA_TRANSMITED == type)
    appOnLed(LED_TYPE_TRANSMITED);

  //LCD
  if (APP_INDICATION_DATA_RECEIVED == type)
    appSendLcdCmd(LCD_CMD_SYMB_TRX_RX);
  else if (APP_INDICATION_DATA_TRANSMITED == type)
    appSendLcdCmd(LCD_CMD_SYMB_TRX_TX);

  if (0 == offMask)
    HAL_StartAppTimer(&turnOffTimerDesc);

  if (APP_INDICATION_DATA_RECEIVED == type){
    offMask |= TURN_OFF_RX_MASK;
  }else if (APP_INDICATION_DATA_TRANSMITED == type){
    offMask |= TURN_OFF_TX_MASK;
  }
}

/********************************************************************
  Description:  Network search periodic timer
  Parameters:   none
  Returns:      none
********************************************************************/
static void networkSearchStep(void)
{
  //LCD logic
  const int range = LCD_CMD_SYMB_ANTENNA_OFF - LCD_CMD_SYMB_ANTENNA_LEVEL_0;
  static int current = 0;
  appSendLcdCmd(current + LCD_CMD_SYMB_ANTENNA_LEVEL_0);
  current = (current + 1) % range;
  appSendLcdCmd(LCD_CMD_SYMB_ZIGBEE_OFF);

  //LED logic
  appToggleLed(LED_TYPE_NETWORK);
}

/********************************************************************
  Description:  Button API glue. Converts from BSP to device API
  Parameters:   none
  Returns:      none
********************************************************************/
static AppKeyCallback_t keyCallback = NULL;
static void keyReleased(uint8_t key)
{
  switch(key)
  {
    case BSP_KEY0:
      if (keyCallback)
        keyCallback(APP_BUTTON_0);
      break;
    case BSP_KEY1:
      if (keyCallback)
        keyCallback(APP_BUTTON_1);
      break;
  }
}

/********************************************************************
  Description:  Battery Sensor handler. Converts BSP API to the boardabstraction.h API.
  Parameters:   none
  Returns:      none
********************************************************************/
#ifdef _BATTERY_SENSOR_
static AppSensorCallback_t batteryCallback = NULL;
void batterySensorHandler(uint8_t val)
{
  if (batteryCallback)
    batteryCallback(true, val);
  batteryCallback = NULL;
}
#endif

/***********************************************************************************
  Global functions
 ***********************************************************************************/

/********************************************************************
  Description: Open periphery.
  Parameters: none.
  Returns: none.
********************************************************************/
void boardAbstractionOpen(void)
{
  USART_Open(&usartDescriptor); // Open USART

  appOpenLeds();

  appOpenLcd();

#if defined(_TEMPERATURE_SENSOR_) || defined(_LIGHT_SENSOR_) || defined(_BATTERY_SENSOR_)
  BSP_OpenTemperatureSensor();
  BSP_OpenLightSensor();
  BSP_OpenBatterySensor();
#endif

  appOpenButtons(NULL, keyReleased);
}

/********************************************************************
  Description: Open devices and restore indication state.
  Parameters: none.
  Returns: none.
********************************************************************/

void boardAbstractionResume(void)
{
  boardAbstractionOpen();

  appOnLed(LED_TYPE_NETWORK);

  appSendLcdCmd(LCD_CMD_SYMB_TRX_OFF);
  appSendLcdCmd(LCD_CMD_SYMB_ZIGBEE_ON);
  appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_2);
  appSendLcdCmd(LCD_CMD_SYMB_SPACE_OFF);
}

/********************************************************************
  Description: Close periphery.
  Shutdown all indications.
  Parameters: none.
  Returns: none.
********************************************************************/
void boardAbstractionClose(void)
{
  USART_Close(&usartDescriptor); // Open USART

  appCloseLeds();

#if defined(_TEMPERATURE_SENSOR_) || defined(_LIGHT_SENSOR_) || defined(_BATTERY_SENSOR_)
  BSP_CloseTemperatureSensor();
  BSP_CloseLightSensor();
  BSP_CloseBatterySensor();
#endif

//  appCloseButtons();

  appSendLcdCmd(LCD_CMD_SYMB_TRX_OFF);
  appSendLcdCmd(LCD_CMD_SYMB_ZIGBEE_OFF);
  appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_OFF);
  appSendLcdCmd(LCD_CMD_SYMB_SPACE_MOON);
  appSendLcdMsg(" ");
}

/********************************************************************
  Description: Return true if thereis nothing to do in HW layer
  Parameters: none.
  Returns: none.
********************************************************************/
bool boardAbstrationIsIdle(void)
{
  bool retval = true;

  if (appReadButtonsState() & BSP_KEY1)
    retval = false;

  if (!appIsLcdOperationCompleted())
    retval = false;

  return retval;
}

/***********************************************************************************
  Board independent UI primitives. Try to show requested indications on available HW.
  Use LCD and Leds, VCP and USART waht is avaliable
 ***********************************************************************************/

/********************************************************************
  Description: print sensor value on available HW
  Parameters: none.
  Returns: none.
********************************************************************/
static char *sensorNames[APP_SENSOR_TYPE_MAX] =
{
  "Temperature",
  "Battery",
  "Light",
};
void boardAbstractionShowMessage(ShortAddr_t sender, AppSensorType_t type, int16_t value)
{
  char str[100];

  //write to usart
  snprintf(str, sizeof(str), "Received from 0x%04X: %s = %d\r\n",
             sender, sensorNames[type], value);
  USART_Write(&usartDescriptor, (uint8_t*)str, strlen(str));

  //write to lcd
  snprintf(str, sizeof(str), "%02X %3d%1c", sender & 0xFF,
      value % 100, sensorNames[type][0]); //write data to LCD
  appSendLcdMsg(str);
}

/********************************************************************
  Description: Shows indication on LCD or leds
  Parameters: type - indication to show
  Returns: none.
********************************************************************/
void boardAbstractionShowIndication(AppIndication_t type)
{
  static HAL_AppTimer_t networkSearchTimerDesc =
  {
    .interval = 500,
    .mode = TIMER_REPEAT_MODE,
    .callback = networkSearchStep,
  };

  switch(type)
  {
    case APP_INDICATION_NETWORK_SEARCH:
      HAL_StartAppTimer(&networkSearchTimerDesc);
      break;

    case APP_INDICATION_NETWORK_STARTED:
      appOnLed(LED_TYPE_NETWORK);
      appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_2);
      appSendLcdCmd(LCD_CMD_SYMB_ZIGBEE_ON);
      HAL_StopAppTimer(&networkSearchTimerDesc);
      break;

    case APP_INDICATION_DATA_RECEIVED:
    case APP_INDICATION_DATA_TRANSMITED:
      turnOnShortIndication(type);
      break;
  }
}

/***********************************************************************************
  Periphery device independent glue.
  Try to play good if requested periphery not present.
 ***********************************************************************************/

/********************************************************************
  Description: register key callback.
  Not called at all if buttons not present on board.
  Parameters: none.
  Returns: none.
********************************************************************/
void boardAbstractionRegisterKeyCallback(AppKeyCallback_t cb)
{
  keyCallback = cb;
}

/********************************************************************
  Description: Device independent read sensors function
  just call cb with false reded param if requested sensor
  type not supported
  Parameters:  t - sensor type
  cb - callback to call when sensor answers data
  Returns: none.
********************************************************************/
void boardAbstractionReadSensor(AppSensorType_t t, AppSensorCallback_t cb)
{
#ifdef _TEMPERATURE_SENSOR_
  if (APP_SENSOR_TYPE_TEMPERATURE == t)
  {
    BSP_ReadTemperatureData(cb);
    return;
  }
#endif
#ifdef _BATTERY_SENSOR_
  if (APP_SENSOR_TYPE_BATTERY == t)
  {
    batteryCallback = cb;
    BSP_ReadBatteryData(batterySensorHandler);
    return;
  }
#endif
#ifdef _LIGHT_SENSOR_
  if (APP_SENSOR_TYPE_LIGHT == t)
  {
    BSP_ReadLightData(cb);
    return;
  }
#endif
  (void)t; //warning prevention
  cb(false, 0);
}

/********************************************************************
  Description: Device independent read sliders function
  return NWK_NODE_ADDRESS if device don't have sliders
  Parameters: none.
  Returns: value reded from sliders.
********************************************************************/
uint8_t boardAbstractionReadSliders(void)
{
  return appReadSliders();
}
