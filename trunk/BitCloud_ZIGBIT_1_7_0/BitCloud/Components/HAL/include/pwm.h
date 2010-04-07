/**************************************************************************//**
  \file pwm.h

  \brief Description of the PWM interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
   10/11/08 A. Taradov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _PWM_H
#define _PWM_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>

/**************************************************************************//**
\brief PWM prescaler
******************************************************************************/
typedef enum
{
  PWM_STOPPED,
  PWM_PRESCALER_1,
  PWM_PRESCALER_8,
  PWM_PRESCALER_32,
  PWM_PRESCALER_64,
  PWM_PRESCALER_128,
  PWM_PRESCALER_256,
  PWM_PRESCALER_1024
} HAL_PwmPrescaler_t;

/**************************************************************************//**
\brief PWM channel
******************************************************************************/
typedef enum
{
  PWM_CHANNEL_0,
  PWM_CHANNEL_1,
  PWM_CHANNEL_2,
} HAL_PwmChannel_t;

/**************************************************************************//**
\brief PWM impulse polarity
******************************************************************************/
typedef enum
{
  /** \brief PWM output is low when duty cycle = 0% */
  PWM_POLARITY_NON_INVERTED,
  /** \brief PWM output is high when duty cycle = 0% */
  PWM_POLARITY_INVERTED
} HAL_PwmPolarity_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes the PWM.

\return
  -1 - Timer/Counter 1 is already in use \n
   0 - success
******************************************************************************/
int HAL_OpenPwm(void);

/**************************************************************************//**
\brief Starts PWM on specified channel.
\param[in]
  channel - channel number.
  polarity - polarity of pulse on this channel
\return
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int HAL_StartPwm(HAL_PwmChannel_t channel, HAL_PwmPolarity_t polarity);

/**************************************************************************//**
\brief Stops PWM on specified channel.
\param[in]
  channel - channel number.
\return
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int HAL_StopPwm(HAL_PwmChannel_t channel);

/**************************************************************************//**
\brief Sets base frequency (common for all channels).
\param[in]
  top - value for the TOP register
  prescaler - clock prescaler
\return
  -1 - invalid prescaler specified
   0 - success
******************************************************************************/
int HAL_SetPwmFrequency(uint16_t top, HAL_PwmPrescaler_t prescaler);

/**************************************************************************//**
\brief Sets compare value for the PWM channel.
\param[in]
  channel - channel number
  cmpValue - compare value
\return
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int HAL_SetPwmCompareValue(HAL_PwmChannel_t channel, uint16_t cmpValue);

/**************************************************************************//**
\brief Closes the PWM.

\return
  -1 - PWM was not opened \n
   0 - success
******************************************************************************/
int HAL_ClosePwm(void);

#endif /* _PWM_H */

// eof pwm.h
