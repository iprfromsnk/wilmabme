/**************************************************************************//**
  \file boardabstraction.h

  \brief device abstraction layer API.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

******************************************************************************/

#ifndef _BOARDABSTRACTION_H_
#define _BOARDABSTRACTION_H_

/*****************************************************************************\*
Includes section
******************************************************************************/

#include <types.h>

/*****************************************************************************\*
Define(s) section
******************************************************************************/

#ifdef TEST_NETWORK
  #undef _BUTTONS_
  #undef _SLIDERS_
#endif // TEST_NETWORK

/*****************************************************************************\*
Types section
******************************************************************************/

typedef enum _Indication_t
{
  APP_INDICATION_NETWORK_SEARCH,
  APP_INDICATION_NETWORK_STARTED,
  APP_INDICATION_DATA_RECEIVED,
  APP_INDICATION_DATA_TRANSMITED,
} AppIndication_t;

typedef enum
{
  APP_SENSOR_TYPE_TEMPERATURE,
  APP_SENSOR_TYPE_BATTERY,
  APP_SENSOR_TYPE_LIGHT,
  APP_SENSOR_TYPE_MAX,
} AppSensorType_t;

typedef enum
{
  APP_BUTTON_0,
  APP_BUTTON_1,
} AppButton_t;

typedef void (*AppKeyCallback_t)(AppButton_t key);
typedef void (*AppSensorCallback_t)(bool readed, int16_t value);

/*****************************************************************************\*
Prototypes section
******************************************************************************/

//State change functions
void boardAbstractionOpen(void);
void boardAbstractionResume(void);
void boardAbstractionClose(void);
bool boardAbstrationIsIdle(void);

//UI primitives
void boardAbstractionShowIndication(AppIndication_t ind);
void boardAbstractionShowMessage(ShortAddr_t sender, AppSensorType_t type, int16_t sensorValue);

//periphery
void boardAbstractionReadSensor(AppSensorType_t t, AppSensorCallback_t cb);
void boardAbstractionRegisterKeyCallback(AppKeyCallback_t cb);
uint8_t boardAbstractionReadSliders(void);

#endif /* _BOARDABSTRACTION_H_ */
