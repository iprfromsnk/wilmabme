/**************************************************************************//**
  \file  resetReason.h

  \brief The header file describes the the reset reason interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    5/12/07 A. Khromykh - Created.
    2/09/09 M. Gekk     - Platform XMega is supported.
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _RESETREASON_H
#define _RESETREASON_H

/* \cond */
/******************************************************************************
                              Define(s) section
 ******************************************************************************/
#define TEMP_WARM_RESET   0x12
/* \endcond */

/******************************************************************************
                               Types section
 ******************************************************************************/
/** \brief The reset reason types. */
#if defined(AT91SAM7X256)
  typedef enum
  {
    /** \brief VDDCORE rising */
    POWER_ON_RESET   = 0x00,
    /** \brief Watchdog fault occurred */
    WDT_RESET        = 0x02,
    /** \brief Processor reset required by the software */
    WARM_RESET       = 0x03,
    /** \brief NRST pin detected low */
    EXTERNAL_RESET   = 0x04,
    /** \brief BrownOut reset occurred */
    BROWN_OUT_RESET  = 0x05
  } HAL_ResetReason_t;
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) || defined(ATMEGA128RFA1) 
  typedef enum
  {
    /** \brief jump to the NULL pointer was issued. */
    NULL_PTR_DEREF_RESET = 0x0,
    /** \brief the supply voltage was below reset threshold. */
    POWER_ON_RESET       = 0x1,
    /** \brief a low level was present on RESET pin. */
    EXTERNAL_RESET       = 0x2,
    /** \brief the supply voltage was below Brown-out reset threshold. Set by fuses.*/
    BROWN_OUT_RESET      = 0x4,
    /** \brief Watch Dog Timer period expired. */
    WDT_RESET            = 0x8,
    /** \brief MCU was reset by JTAG. */
    JTAG_RESET           = 0x10,
    /** \brief software reset. */
    WARM_RESET           = 0x11
  } HAL_ResetReason_t;
#elif defined(ATXMEGA128A1) || defined(ATXMEGA256A3)
  typedef enum
  {
    /** \brief Power-on reset is released when the VCC stops rising or when 
     * the VCC level has reached the Power-on Threshold Voltage (VPOT) level. */
    POWER_ON_RESET       = (1U << 0),
    /** \brief The external reset will trigger when the RESET pin is driven 
     * below the RESET pin threshold voltage, VRST. */
    EXTERNAL_RESET       = (1U << 1),
    /** \brief The VCC level falls bellow the trigger level for a minimum time. */
    BROWN_OUT_RESET      = (1U << 2),
    /** \brief Watchdog reset will be given if the WDT is not reset from t
     * he software within a programmable timout period, */
    WATCHDOG_RESET       = (1U << 3),
    /** \brief The Program and Debug Interface reset contains a separate reset source 
     * that is used to reset the device during external programming and debugging. */
    DEBUG_RESET          = (1U << 4),
    /** \brief The Software reset makes it possible to issue a system reset from 
     * software by writing to the Software Reset bit in the Reset Control Register. */
    SOFTWARE_RESET       = (1U << 5),
    /** \brief There is a negative spike on the VCC level. The VCC fall must be 
     * significant and last for longer than a minimum time.  */
    SPIKE_RESET          = (1U << 6)
  } HAL_ResetReason_t;
#endif

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief Returns the reset reason.
  \return The reason of reset.
 ******************************************************************************/
HAL_ResetReason_t HAL_ReadResetReason(void);

/**************************************************************************//**
  \brief Software reset.
 ******************************************************************************/
void HAL_WarmReset(void);

#endif /* _RESETREASON_H */
/* resetReason.h */
