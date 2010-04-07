/**************************************************************************//**
  \file   sleepTimer.c

  \brief  The implementation of the sleep timer.

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

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sleepTimer.h>
#include <halSleepTimerClock.h>

/******************************************************************************
                   Global variables section
******************************************************************************/
volatile HAL_SleepTimer_t *halSleepTimerPointer = NULL;

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
  Delete sleep timer from list
******************************************************************************/
void halClearSleepTimerList(void)
{
  halSleepTimerPointer = NULL;
}

/******************************************************************************
Starts sleep timer. Interval must be greater one tick time.
  Parameters:
    sleepTimer - address of the HAL_SleepTimer_t.
  Retuirns:
    -1 - interval can not be counted out.
     0 - otherwise.
******************************************************************************/
int HAL_StartSleepTimer(HAL_SleepTimer_t *sleepTimer)
{
  // Convert millisecond interval to the sleep timer ticks.
  uint32_t tempValue = (halSleepTimerFrequency() * sleepTimer->interval) / 1000ul;

  if (!sleepTimer)
    return -1;

  if (!tempValue)
    return -1;// Can't count out interval

  if (halSleepTimerPointer) // there is active timer
    return -1;

  // Start asynchronous timer2.
  halSetSleepTimerInterval(tempValue);
  // Start sleep timer.
  halSleepTimerPointer = sleepTimer;
  return 0;
}// end sleepTimer_start

/******************************************************************************
Removes timer.
Parameters:
  sleepTimer - address of the timer that must be removed wrom the list
Returns:
  -1 - there is no the timer in the list.
   0 - otherwise.
******************************************************************************/
int HAL_StopSleepTimer(HAL_SleepTimer_t *sleepTimer)
{
  if (!sleepTimer)
    return -1;

  if (sleepTimer != halSleepTimerPointer) // The others is working
    return -1;

  halClearTimeControl();
  halClearSleepTimerList();

  return 0;
}

/******************************************************************************
Interrupt handler about sleep interval was completed.
******************************************************************************/
void halAsyncTimerHandler(void)
{
  if (NULL == halSleepTimerPointer)  // there isn't work timer
    return;

  if (TIMER_REPEAT_MODE == halSleepTimerPointer->mode)
  {
    if (NULL != halSleepTimerPointer->callback)
      halSleepTimerPointer->callback();

    if (NULL == halSleepTimerPointer)  // user can delete timer in callback
      return;

    halSetSleepTimerInterval(halSleepTimerPointer->interval);
  }
  else
  { /* If next sleep timer starts in callback previous then will be bug.
       halSleepTimerPointer must be NULL to start next timer. It is fix. */
    void (* tempPointer)() = halSleepTimerPointer->callback;

    halSleepTimerPointer = NULL;

    if (NULL != tempPointer)
      tempPointer();
  }
}

//eof sleepTimer.c
