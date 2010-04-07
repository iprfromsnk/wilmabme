/************************************************************//**
  \file rs232Controller.h

  \brief Functions for RS232 level converter interface.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    28.09.09 A. Taradov - Created
*****************************************************************/
#ifndef _RS232CONTROLLER_H
#define _RS232CONTROLLER_H

/****************************************************************
                   Prototypes section
*****************************************************************/

/************************************************************//**
\brief Enable RS232 level converter.
****************************************************************/
static inline void BSP_EnableRs232(void)
{
#if defined(BOARD_RCB128RFA1) && defined(BSP_ENABLE_RS232_CONTROL)
  // ~EN
  GPIO_D4_make_out();
  GPIO_D4_clr();

  // FORCEON
  GPIO_D6_make_out();
  GPIO_D6_set();

  // ~FORCEOFF
  GPIO_D7_make_out();
  GPIO_D7_set();
#endif
};

/************************************************************//**
\brief Disable RS232 level converter.
****************************************************************/
static inline void BSP_DisableRs232(void)
{
#if defined(BOARD_RCB128RFA1) && defined(BSP_ENABLE_RS232_CONTROL)
  GPIO_D4_make_in();
  GPIO_D6_make_in();
  GPIO_D7_make_in();
#endif
};

#endif /* _RS232CONTROLLER_H */
