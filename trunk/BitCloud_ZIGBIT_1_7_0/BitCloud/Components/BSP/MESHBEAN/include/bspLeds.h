/***************************************************************************//**
\file  bspLeds.h

\brief Declaration of leds defines.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _BSPLEDS_H
#define _BSPLEDS_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <gpio.h>
#include <leds.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/

#define halInitRedLed()       GPIO_0_make_out()
#define halUnInitRedLed()     GPIO_0_make_in()
#define halOnRedLed()         GPIO_0_set()
#define halOffRedLed()        GPIO_0_clr()
#define halReadRedLed()       GPIO_0_read()
#define halToggleRedLed()     GPIO_0_toggle()

#define halInitYellowLed()    GPIO_1_make_out()
#define halUnInitYellowLed()  GPIO_1_make_in()
#define halOnYellowLed()      GPIO_1_set()
#define halOffYellowLed()     GPIO_1_clr()
#define halReadYellowLed()    GPIO_1_read()
#define halToggleYellowLed()  GPIO_1_toggle()

#define halInitGreenLed()     GPIO_2_make_out()
#define halUnInitGreenLed()   GPIO_2_make_in()
#define halOnGreenLed()       GPIO_2_set()
#define halOffGreenLed()      GPIO_2_clr()
#define halReadGreenLed()     GPIO_2_read()
#define halToggleGreenLed()   GPIO_2_toggle()

#endif /*_BSPLEDS_H*/
// eof bspLeds.h
