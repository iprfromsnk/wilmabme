/****************************************************************************//**
  \file bcSysSleep.h

  \brief
    Implementation of the system sleep service.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    8/06/09 A. Khromykh - Created
*********************************************************************************/

#ifndef _MNSYSSLEEP_H
#define _MNSYSSLEEP_H
/*********************************************************************************
                          Includes section.
**********************************************************************************/
#include <sleep.h>

/*********************************************************************************
                          Function prototypes section.
**********************************************************************************/
/******************************************************************************//**
\brief Prepares system for sleep.
**********************************************************************************/
void SYS_Sleep(void);

#endif /* _MNSYSSLEEP_H */
