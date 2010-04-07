/**************************************************************************//**
  \file  sleep.h

  \brief Interface to control power save mode.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      29/06/07 E. Ivanov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _SLEEP_H
#define _SLEEP_H

/******************************************************************************
                   Includes section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/
//it is used for reliable wake up
typedef enum
{
  ACTIVE_MODE,
  SLEEP_MODE
} WakeupStation_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
  Disconnects TRSLEEP pin from comparator output.
*******************************************************************************/
void halPowerOn(void);

/*******************************************************************************
  Shutdown system.
  NOTES:
  the application should be sure the poweroff will not be
  interrupted after the execution of the sleep().
*******************************************************************************/
void halPowerOff(void);

/******************************************************************************
  Prepares system for power-save, power-down.
  Power-down the mode is possible only when internal RC is used
  Parametres:
  none.
  Returns:
  -1 there is no possibility to power-down system.
******************************************************************************/
int HAL_Sleep(void);

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/*******************************************************************************
  Makes MCU enter Idle mode.
*******************************************************************************/
INLINE void HAL_IdleMode(void)
{
  SMCR = 0x1;
  __SLEEP;
  SMCR = 0;
}

#endif /* _SLEEP_H */
// eof sleep.h
