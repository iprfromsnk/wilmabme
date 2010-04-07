/**************************************************************************//**
  \file  pwm.c

  \brief Implementation of PWM interface.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
     10/11/08 A. Taradov - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halPwm.h>
#include <pwm.h>

/******************************************************************************
                   Defines section
******************************************************************************/

/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   Global variables section
******************************************************************************/

/******************************************************************************
                   Implementations section
******************************************************************************/

/******************************************************************************
Initializes the PWM.
Parameters:
  none.
Returns:
  -1 - Timer/Counter 1 is already in use
   0 - success
******************************************************************************/
int HAL_OpenPwm(void)
{
  halOpenPwm();

  return 0;
}

/******************************************************************************
Starts PWM on specified channel.
Parameters:
  channel - channel number
  polarity - polarity of pulse on this channel
Returns:
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int HAL_StartPwm(HAL_PwmChannel_t channel, HAL_PwmPolarity_t polarity)
{
  return halStartPwm(channel, polarity);
}

/******************************************************************************
Stops PWM on specified channel.
Parameters:
  channel - channel number
Returns:
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int HAL_StopPwm(HAL_PwmChannel_t channel)
{
  return halStopPwm(channel);
}

/******************************************************************************
Sets base frequency (common for all channels).
Parameters:
  top - value for the TOP register
  prescaler - clock prescaler
Returns:
  -1 - invalid prescaler specified
   0 - success
******************************************************************************/
int HAL_SetPwmFrequency(uint16_t top, HAL_PwmPrescaler_t prescaler)
{
  return halSetPwmFrequency(top, prescaler);
}

/******************************************************************************
Sets compare value for the PWM channel.
Parameters:
  channel - channel number
  cmpValue - compare value
Returns:
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int HAL_SetPwmCompareValue(HAL_PwmChannel_t channel, uint16_t cmpValue)
{
  return halSetPwmCompareValue(channel, cmpValue);
}

/******************************************************************************
Closes the PWM.
Parameters:
  none
Returns:
  -1 - PWM was not opened
   0 - success
******************************************************************************/
int HAL_ClosePwm(void)
{
  halStopPwm(PWM_CHANNEL_0);
  halStopPwm(PWM_CHANNEL_1);
  halStopPwm(PWM_CHANNEL_2);

  halClosePwm();

  return 0;
}

// eof pwm.c
