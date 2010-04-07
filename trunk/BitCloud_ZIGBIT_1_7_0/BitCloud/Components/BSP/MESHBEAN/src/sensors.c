/**************************************************************************//**
\file  sensors.h

\brief Implementation of sensors interface.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    12/05/08 A. Khromykh - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <sensors.h>
#include <pwrCtrl.h>
#include <lm73.h>
#include <tsl2550.h>
#include <battery.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/***************************************************************************//**
\brief Opens temperature sensor.

\return
  BC_FAIL - sensor has been already open. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenTemperatureSensor(void)
{
  result_t result;

  if (BC_SUCCESS == (result = openLm73()))
  {
    bspOnPeriphery(SENSOR_TEMPERATURE);
  }
  return result;
}

/***************************************************************************//**
\brief Closes the temperature sensor.

\return
  BC_FAIL - if a hardware error has occured or
            there is uncompleted ReadData request. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_CloseTemperatureSensor(void)
{
  result_t result;

  if (BC_SUCCESS == (result = closeLm73()))
  {
    bspOffPeriphery(SENSOR_TEMPERATURE);
  }
  return result;
}

/**************************************************************************//**
\brief Reads data from the temperature sensor.
\param[in]
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has
             occured.
\param[in]
    data - sensor data.
\return
    BC_FAIL - previous request was not completed. \n
    BC_SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadTemperatureData(void (*f)(bool result, int16_t data))
{
  return readLm73Data(f);
}

/***************************************************************************//**
\brief Opens the light sensor.
\return
  BC_FAIL - sensor has been already open. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenLightSensor(void)
{
  result_t result;

  if (BC_SUCCESS == (result = openTsl2550()))
  {
    bspOnPeriphery(SENSOR_LIGHT);
  }
  return result;
}

/***************************************************************************//**
\brief Closes the light sensor.
\return
  BC_FAIL - if a hardware error has occured or
         there is uncompleted ReadData request. \n
  BC_SUCCESS  - otherwise.
*******************************************************************************/
result_t BSP_CloseLightSensor(void)
{
  result_t result;

  if (BC_SUCCESS == (result = closeTsl2550()))
  {
    bspOffPeriphery(SENSOR_LIGHT);
  }
  return result;
}

/**************************************************************************//**
\brief Reads data from the light sensor.
\param[in]
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has
             occured.
\param[in]
    data - sensor data.
\return
    BC_FAIL - previous request was not completed. \n
    BC_SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadLightData(void (*f)(bool result, int16_t data))
{
  return readTsl2550Data(f);
}

/***************************************************************************//**
\brief Opens the battery sensor.
\return
  BC_FAIL - sensor has been already open. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenBatterySensor(void)
{
  result_t result;

  if (BC_SUCCESS == (result = openBattery()))
  {
    bspOnPeriphery(SENSOR_BATTERY);
  }
  return result;
}

/***************************************************************************//**
\brief Closes the battery sensor.
\return
  BC_FAIL - sensor was not opened. \n
  BC_SUCCESS  - otherwise.
*******************************************************************************/
result_t BSP_CloseBatterySensor(void)
{
  result_t result;

  if (BC_SUCCESS == (result = closeBattery()))
  {
    bspOffPeriphery(SENSOR_BATTERY);
  }
  return result;
}

/**************************************************************************//**
\brief Reads data from battery sensor.
\param[in]
    data - sensor data.
\return
    BC_FAIL - previous request was not completed, or sensor was not opened. \n
    BC_SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadBatteryData(void (*callback)(uint8_t data))
{
  return readBatteryData(callback);
}

//end of sensors.c
