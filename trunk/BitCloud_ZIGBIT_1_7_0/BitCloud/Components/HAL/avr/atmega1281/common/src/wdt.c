/**************************************************************************//**
  \file  wdt.c

  \brief Implementation of WDT interrupt handler.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      29/05/07 E. Ivanov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#include <wdtCtrl.h>
#include <atomic.h>
#include <halDbg.h>
#include <halDiagnostic.h>
void (*halWdtCallback)() = NULL;

/*******************************************************************************
Registers WDT fired callback.
Parameters:
  wdtCallback - callback.
Returns:
  none.
*******************************************************************************/
void HAL_RegisterWdtCallback(void (*wdtCallback)())
{
  halWdtCallback = wdtCallback;
}

/*******************************************************************************
Starts WDT with interval.
Parameters:
  interval - interval.
Returns:
  none.
*******************************************************************************/
void HAL_StartWdt(HAL_WdtInterval_t interval)
{
  uint8_t i = 0;

  if (NULL != halWdtCallback)
    i = 1 << WDIE;
  ATOMIC_SECTION_ENTER
  BEGIN_MEASURE
  wdt_reset();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR  = (1<<WDE) | interval;

  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR |= (1<<WDE) | i;
  END_MEASURE(HALATOM_STARTWDT_TIME_LIMIT)
  ATOMIC_SECTION_LEAVE
}

/*******************************************************************************
Interrupt handler.
*******************************************************************************/
ISR(WDT_vect)
{
  if (NULL != halWdtCallback)
    halWdtCallback();
  wdt_enable(0);
  for (;;);
}
//eof wdt.c
