/**************************************************************************//**
  \file  halMacIsr.c

  \brief mac interrupts implementation.

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

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <halMacIsr.h>
#include <halRfCtrl.h>
#include <atomic.h>
#include <halDiagnostic.h>
/******************************************************************************
                   Global variables section
******************************************************************************/
RTimerDescr_t __rtimer;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
  Initializes Rtimer.
******************************************************************************/
void HAL_InitMacIsr(void);

/******************************************************************************
  Redirect interrupt event depending on the TrxState.
  Parameters: none.
  Returns: none.
******************************************************************************/
void phyDispatcheRTimerEvent(void);

/******************************************************************************
  Redirect interrupt event depending on the TrxState.
  Parameters: none.
  Returns: none.
******************************************************************************/
void phyDispatcheRfInterrupt(void);

/******************************************************************************
                    Implementations section
******************************************************************************/
/******************************************************************************
  Initializes Rtimer.
******************************************************************************/
void HAL_InitMacIsr(void)
{
  __rtimer.mode = HAL_RTIMER_STOPPED_MODE;
  HAL_InitRfIrq();
}

/******************************************************************************
  Output compare unit (channel B) interrupt handler.
******************************************************************************/
ISR(TIMER4_COMPB_vect)
{
  BEGIN_MEASURE
  HAL_RtimerHandler();
  phyDispatcheRTimerEvent();
  END_MEASURE(HALISR_TIMER3_COMPA_TIME_LIMIT)
}

/****************************************************************
  Interrupt service routine.
  Do not move this ISR! It could be omitted in your project.
****************************************************************/
ISR(INT5_vect)
{
  BEGIN_MEASURE
  phyDispatcheRfInterrupt();
  END_MEASURE(HALISR_PHYDISPATCH_RFINT_TIME_LIMIT)
}

// eof halMacIsr.c
