/**************************************************************************//**
  \file  halPwm.c

  \brief Implementation of hardware depended PWM interface.

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

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <halPwm.h>

/******************************************************************************
                   Defines section
******************************************************************************/
#define START_PWM_CHANNEL(chan) \
  {                             \
    TCCR1A = ((TCCR1A | (1 << COM1##chan##1)) & ~(1 << COM1##chan##0)) | \
             (polarity ? (1 << COM1##chan##0) : 0); \
  }

#define STOP_PWM_CHANNEL(chan) \
  {                            \
    OCR1##chan = 0;            \
    TCCR1A &= ~((1 << COM1##chan##1) | (1 << COM1##chan##0)); \
  }

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
  none.
******************************************************************************/
void halOpenPwm(void)
{
  TCNT1 = 0;
  ICR1  = 0;

  TCCR1A = 0x00;  // set "normal mode" for all channels
  TCCR1B = (1 << WGM13); // PWM, Phase and Frequency Correct, Timer clock stopped.
  TCCR1C = 0xc0;  // force compare for clear output
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
int halStartPwm(HAL_PwmChannel_t channel, HAL_PwmPolarity_t polarity)
{
  switch (channel)
  {
    case PWM_CHANNEL_0:
      GPIO_CHAN0_make_out();
      START_PWM_CHANNEL(A);
      break;

    case PWM_CHANNEL_1:
      GPIO_CHAN1_make_out();
      START_PWM_CHANNEL(B);
      break;

    case PWM_CHANNEL_2:
      GPIO_CHAN2_make_out();
      START_PWM_CHANNEL(C);
      break;

    default:
      return -1;
  }
  return 0;
}

/******************************************************************************
Stops PWM on specified channel.
Parameters:
  channel - channel number
Returns:
  -1 - wrong channel specified
   0 - success
******************************************************************************/
int halStopPwm(HAL_PwmChannel_t channel)
{
  switch (channel)
  {
    case PWM_CHANNEL_0:
      STOP_PWM_CHANNEL(A);
      GPIO_CHAN0_make_in();
      break;

    case PWM_CHANNEL_1:
      STOP_PWM_CHANNEL(B);
      GPIO_CHAN1_make_in();
      break;

    case PWM_CHANNEL_2:
      STOP_PWM_CHANNEL(C);
      GPIO_CHAN2_make_in();
      break;

    default:
      return -1;
  }
  return 0;
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
int halSetPwmFrequency(uint16_t top, HAL_PwmPrescaler_t prescaler)
{
  if (prescaler > PWM_PRESCALER_1024)
    return -1;

  TCCR1B = TCCR1B & ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // stop timer

  ICR1  = top;  // set top register
  TCNT1 = ICR1;  // clear timer

  OCR1A = 0;  // clear PWM registers (all channels)
  OCR1B = 0;
  OCR1C = 0;

  TCCR1B |= prescaler; // run timer

  return 0;
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
int halSetPwmCompareValue(HAL_PwmChannel_t channel, uint16_t cmpValue)
{
  switch (channel)
  {
    case PWM_CHANNEL_0:
      OCR1A = cmpValue;
      break;

    case PWM_CHANNEL_1:
      OCR1B = cmpValue;
      break;

    case PWM_CHANNEL_2:
      OCR1C = cmpValue;
      break;

    default:
      return -1;
  }
  return 0;
}

/******************************************************************************
Closes the PWM.
Parameters:
  none
Returns:
  none
******************************************************************************/
void halClosePwm(void)
{
  TCCR1A = 0;
  TCCR1B = 0; // disable PWM, stop timer
}

// eof halPwm.c
