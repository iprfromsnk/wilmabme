/**************************************************************************//**
  \file  halMacIsr.h

  \brief Declaration mac timer interface.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      14/01/08 A. Mandychev - Created.
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALMACISR_H
#define _HALMACISR_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <halAppClock.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#if defined(HAL_3d6864MHz)
  #define HAL_NUMBER_OF_TICKS_IN_USEC    0.5
#elif defined(HAL_4MHz)
  #define HAL_NUMBER_OF_TICKS_IN_USEC    0.5
#elif defined(HAL_7d3728MHz)
  #define HAL_NUMBER_OF_TICKS_IN_USEC      1
#elif defined(HAL_8MHz)
  #define HAL_NUMBER_OF_TICKS_IN_USEC      1
#endif

/******************************************************************************
                        Types section.
******************************************************************************/
typedef enum
{
  HAL_RTIMER_REPEAT_MODE   = 0,
  HAL_RTIMER_ONE_SHOT_MODE = 1,
  HAL_RTIMER_STOPPED_MODE  = 2,
} HAL_RTimerMode_t;

typedef struct // Timer description.
{
  volatile HAL_RTimerMode_t    mode;       // Mode.
  volatile uint16_t            period;     // Period of the timer.
  volatile uint16_t            nextEvent;  // Counter of periods.
} RTimerDescr_t;

/******************************************************************************
                        External variables.
******************************************************************************/
// Do not use it in other files.
extern RTimerDescr_t __rtimer;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  Initializes Rtimer and RF ext. interrupts.
******************************************************************************/
void HAL_InitMacIsr(void);

/******************************************************************************
                 Inline static functions prototypes section.
******************************************************************************/
/******************************************************************************
  Starts RTimer. Function should be invoked in critical section.
  Parameters:
    source  - source of invocation.
    mode    - RTimer mode.
    period  - RTimer period.
******************************************************************************/
INLINE bool HAL_StartRtimer(HAL_RTimerMode_t mode, uint16_t period)
{
  if (HAL_RTIMER_STOPPED_MODE != __rtimer.mode)
    return false;

  __rtimer.period    = (uint16_t)(period * HAL_NUMBER_OF_TICKS_IN_USEC);
  __rtimer.mode      = mode;
  __rtimer.nextEvent = TCNT4 + __rtimer.period;
  if (__rtimer.nextEvent > TOP_TIMER_COUNTER_VALUE)
    __rtimer.nextEvent -= TOP_TIMER_COUNTER_VALUE;
  OCR4B = __rtimer.nextEvent;
  // clear possible interrupt by setting logical one.
  TIFR4 = (1 << OCF4B);
  // enable interrupt
  TIMSK4 |= (1 << OCIE4B);
  return true;
}

/******************************************************************************
  Stops RTimer. Function should be invoked in critical section.
******************************************************************************/
INLINE void HAL_StopRtimer(void)
{
  // clear possible interrupt
  TIFR4 &= ~(1 << OCF4B);
  // disable interrupt
  TIMSK4 &= ~(1 << OCIE4B);
  __rtimer.mode = HAL_RTIMER_STOPPED_MODE;
}

/******************************************************************************
  Interrupt handler for rtimer routine.
******************************************************************************/
INLINE void HAL_RtimerHandler(void)
{
  if (HAL_RTIMER_ONE_SHOT_MODE == __rtimer.mode)
  {
    TIMSK4 &= ~(1 << OCIE4B);
    __rtimer.mode = HAL_RTIMER_STOPPED_MODE;
  }
  else
  {
    __rtimer.nextEvent += __rtimer.period;
    if (__rtimer.nextEvent > TOP_TIMER_COUNTER_VALUE)
      __rtimer.nextEvent -= TOP_TIMER_COUNTER_VALUE;
    OCR4B = __rtimer.nextEvent;
  }
}

#endif /* _HALMACISR_H */

// eof halMacIsr.h
