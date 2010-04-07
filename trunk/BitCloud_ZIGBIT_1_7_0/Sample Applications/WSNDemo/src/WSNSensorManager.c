/**********************************************************************//**
  \file WSNSensorManager.c

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13/06/07 I. Kalganova - Modified
**************************************************************************/

#include <types.h>
#include <taskManager.h>
#include <sensors.h>
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>

extern AppMessageRequest_t  appMessage;
// Prototipes
static void temperatureDataReady(bool result, int16_t temperature);
static void lightDataReady(bool result, int16_t light);
static void batteryDataReady(uint8_t battery);

static void (*callback)(void);

/***********************************************************************************
  Init sensors.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
void appStartSensorManager(void)
{
#ifdef _TEMPERATURE_SENSOR_
  assert(BC_SUCCESS == BSP_OpenTemperatureSensor(), 0xf007);
#endif // _TEMPERATURE_SENSOR_
#ifdef _LIGHT_SENSOR_
  assert(BC_SUCCESS == BSP_OpenLightSensor(), 0xf008);
#endif // _LIGHT_SENSOR_
#ifdef _BATTERY_SENSOR_
  assert(BC_SUCCESS == BSP_OpenBatterySensor(), 0xf009);
#endif // _BATTERY_SENSOR_
}

void appStopSensorManager()
{
  // No checking for return status  yet
#ifdef _TEMPERATURE_SENSOR_
  assert(BC_SUCCESS == BSP_CloseTemperatureSensor(), 0xf004);
#endif // _TEMPERATURE_SENSOR_
#ifdef _LIGHT_SENSOR_
  assert(BC_SUCCESS == BSP_CloseLightSensor(), 0xf005);
#endif // _LIGHT_SENSOR_
#ifdef _BATTERY_SENSOR_
  assert(BC_SUCCESS == BSP_CloseBatterySensor(), 0xf006);
#endif // _BATTERY_SENSOR_
}
/***********************************************************************************
  Ask sensors data.

  Parameters:
    sensorId - sensor id

  Return:
    none

 ***********************************************************************************/
void appGetSensorData(void (*sensorsesGot)(void))
{
  callback = sensorsesGot;

#ifdef OMIT_READING_SENSORS
  callback();
#else
  #ifdef _TEMPERATURE_SENSOR_
    assert(BC_SUCCESS == BSP_ReadTemperatureData(temperatureDataReady), 0xf001);
  #else
    temperatureDataReady(0, 0);
  #endif //_TEMPERATURE_SENSOR_
#endif
}

static void temperatureDataReady(bool result, int16_t temperature)
{
  //save sensor data
  if (result)
    appMessage.data.meshbean.temperature = temperature;
  else
    appMessage.data.meshbean.temperature = 0;

#ifdef _LIGHT_SENSOR_
  assert(BC_SUCCESS == BSP_ReadLightData(lightDataReady), 0xf002);
#else
  lightDataReady(0, 0);
#endif //_LIGHT_SENSOR_
}

static void lightDataReady(bool result, int16_t light)
{
  if (result)
    appMessage.data.meshbean.light = light;
  else
    appMessage.data.meshbean.light = 0;

#ifdef _BATTERY_SENSOR_
  assert(BC_SUCCESS == BSP_ReadBatteryData(batteryDataReady), 0xf003);
#else
  batteryDataReady(0);
#endif // _BATTERY_SENSOR_
}

static void batteryDataReady(uint8_t battery)
{
  appMessage.data.meshbean.battery = battery;
  callback();
}

//eof WSNSensorManager.c
