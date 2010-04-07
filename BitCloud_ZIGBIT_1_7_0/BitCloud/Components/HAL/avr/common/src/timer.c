/**************************************************************************//**
  \file  timer.c

  \brief Functions to manipulate by timers list.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      7/12/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <bcTimer.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Adds timer to the timer's list.
Parameters:
  head - address of pointer to head of the timers list.
  timer - address of timer that must be added to the list.
Returns:
  none.
******************************************************************************/
void halAddTimer(Timer_t **head, Timer_t *timer)
{
  if (*head)
  {
    timer->service.next = *head;
  }
  *head = timer; // top of list
}

/******************************************************************************
Removes timer from the timers list.
Parameters:
  head - address of pointer to head of the timers list.
  prev - address of the timer before the timer that must be removed from the list.
  p - address of timer that must be removed from the list.
Returns:
  pointer to next cell or pointer to head if deleting is head
******************************************************************************/
Timer_t* halRemoveTimer(Timer_t **head, Timer_t *prev, Timer_t *p)
{
  Timer_t *t;

  if (p == *head)
  {// removing first element of list
    t = p->service.next;
    p->service.next = 0;
    *head = t;
    return *head;
  }
  else
  {
    prev->service.next = p->service.next;
    p->service.next = 0;
    return prev->service.next;
  }
}

/******************************************************************************
The search of the timer in the timers list before one.
Parameters:
  head - address of pointer to head of the timers list.
Returns:
  pointer to saerching timer
******************************************************************************/
Timer_t *halFindPrevTimer(Timer_t **head,  Timer_t *p)
{
  Timer_t *t = *head;

  for (; t ;)
  {
    if (t->service.next == p)
      return t;
    t = t->service.next;
  }
  return NULL;
}
//eof timer.c
