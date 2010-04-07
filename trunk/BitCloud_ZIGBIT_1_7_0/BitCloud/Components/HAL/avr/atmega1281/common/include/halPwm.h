/**************************************************************************//**
  \file  halPwm.h

  \brief Declaration of hardware depended PWM interface.

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

#ifndef _HALPWM_H
#define _HALPWM_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <gpio.h>
#include <pwm.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes the PWM.
\param[in]
  none
******************************************************************************/
void halOpenPwm(void);

/**************************************************************************//**
\brief Starts PWM on specified channel.
\param[in]
  channel - channel number
  polarity - polarity of pulse on this channel
\return
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int halStartPwm(HAL_PwmChannel_t channel, HAL_PwmPolarity_t polarity);

/**************************************************************************//**
\brief Stops PWM on specified channel.
\param[in]
  channel - channel number.
\return
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int halStopPwm(HAL_PwmChannel_t channel);

/**************************************************************************//**
\brief Sets base frequency (common for all channels).
\param[in]
  top - value for the TOP register
  prescaler - clock prescaler
\return
  -1 - invalid prescaler specified
   0 - success
******************************************************************************/
int halSetPwmFrequency(uint16_t top, HAL_PwmPrescaler_t prescaler);

/**************************************************************************//**
\brief Sets compare value for the PWM channel.
\param[in]
  channel - channel number
  cmpValue - compare value
\return
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int halSetPwmCompareValue(HAL_PwmChannel_t channel, uint16_t cmpValue);

/**************************************************************************//**
\brief Closes the PWM.
******************************************************************************/
void halClosePwm(void);

/******************************************************************************
                   Inline static functions section
******************************************************************************/
// the macros for the manipulation by pwm channel0
HAL_ASSIGN_PIN(CHAN0, B, 5);
// the macros for the manipulation by pwm channel1
HAL_ASSIGN_PIN(CHAN1, B, 6);
// the macros for the manipulation by pwm channel2
HAL_ASSIGN_PIN(CHAN2, B, 7);

#endif /* _HALPWM_H */

// eof halPwm.h
