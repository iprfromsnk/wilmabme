/**************************************************************************//**
  \file   uid.c

  \brief  Implementation of UID interface.

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
#include <w1.h>
#include <uid.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
 UID discovery.
 Parameters:
   id - UID buffer pointer.
 Returns:
   0 - if UID of DS2411 has been found without error;
  -1 - if there are some erros during UID discovery.
******************************************************************************/
int HAL_ReadUid(uint64_t *id)
{
  if (W1_SUCCESS_STATUS == HAL_SearchW1Device(DS2411, (uint8_t *) id, 1, NULL))
  {
    *((uint8_t *) id + 7) = *((uint8_t *) id + 0);
    *id >>= 8;
    return 0;
  }
  else
    return -1;
}

// eof uid.c
