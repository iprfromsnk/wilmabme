/**************************************************************************//**
  \file  irq.h

  \brief The header file describes the IRQ interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    5/12/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _IRQ_H
#define _IRQ_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define IRQPORTF

/** \brief The low level generates an interrupt request. */
#define  IRQ_LOW_LEVEL        0
/** \brief The high level generates an interrupt request (valid only for arm). */
#define  IRQ_HIGH_LEVEL       1
/** \brief Any edge generates an interrupt request (valid only for avr and xmega). */
#define  IRQ_ANY_EDGE         2
/** \brief Falling edge generates an interrupt request. */
#define  IRQ_FALLING_EDGE     3
/** \brief Rising edge generates an interrupt request. */
#define  IRQ_RISING_EDGE      4
/** \brief interrupt is disabled. (valid only for xmega)*/
#define  IRQ_IS_DISABLED      5
/** \brief interrupt is not changed previous state. (valid only for xmega)*/
#define  IRQ_IS_NOT_CHANGED   6

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief numbers of possible interrupt. */
typedef enum
{
#if defined(AT91SAM7X256) || defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || \
    defined(AT90USB1287) || defined(ATMEGA128RFA1)
/** \brief number of valid interrupt for arm. */
  IRQ_0 = 0,
/** \brief number of valid interrupt for arm. */
  IRQ_1 = 1,
  IRQ_2 = 2,
  IRQ_3 = 3,
  IRQ_4 = 4,
  IRQ_5 = 5,
/** \brief number of valid interrupt for avr. */
  IRQ_6 = 6,
/** \brief number of valid interrupt for avr. */
  IRQ_7 = 7,
#endif
#if defined(ATXMEGA128A1) || defined(ATXMEGA256A3)
  #if defined(IRQPORTA)
    IRQ_A0,
    IRQ_A1,
  #endif
  #if defined(IRQPORTB)
    IRQ_B0,
    IRQ_B1,
  #endif
  #if defined(IRQPORTC)
    IRQ_C0,
    IRQ_C1,
  #endif
  #if defined(IRQPORTD)
    IRQ_D0,
    IRQ_D1,
  #endif
  #if defined(IRQPORTE)
    IRQ_E0,
    IRQ_E1,
  #endif
  #if defined(IRQPORTF)
    IRQ_F0,
    IRQ_F1,
  #endif
#endif
#if defined(ATXMEGA128A1)
  #if defined(IRQPORTJ)
    IRQ_J0,
    IRQ_J1,
  #endif
  #if defined(IRQPORTH)
    IRQ_H0,
    IRQ_H1,
  #endif
  #if defined(IRQPORTK)
    IRQ_K0,
    IRQ_K1,
  #endif
#endif
  IRQ_LIMIT
} HAL_IrqNumber_t;

#if defined(AT91SAM7X256) || defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || \
    defined(AT90USB1287) || defined(ATMEGA128RFA1)
/** \brief interrupt activation condition. */
typedef uint8_t HAL_IrqMode_t;
#endif
#if defined(ATXMEGA128A1) || defined(ATXMEGA256A3)
/** \brief interrupt activation condition. */
typedef struct
{
  uint32_t pin0 : 3;
  uint32_t pin1 : 3;
  uint32_t pin2 : 3;
  uint32_t pin3 : 3;
  uint32_t pin4 : 3;
  uint32_t pin5 : 3;
  uint32_t pin6 : 3;
  uint32_t pin7 : 3;
} HAL_IrqMode_t;
#endif

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Registers the user's irqNumber external interrupt

\param[in]
   irqNumber - IRQ number. Must be chosen from: \n
            IRQ_0 (for arm)  \n
            IRQ_1 (for arm) \n
            IRQ_6 (for avr) \n
            IRQ_7 (for avr) \n
            IRQ_PC (for xmega. P - port name, C - interrupt number. For example: IRQ_D1) \n
\param[in]
   irqMode - Controls the sort of interrupt. For avr and arm must be chosen from: \n
            IRQ_LOW_LEVEL         // The low level generates an interrupt request. \n
            IRQ_HIGH_LEVEL        // The high level generates an interrupt request (valid only for arm). \n
            IRQ_ANY_EDGE          // Any edge generates an interrupt request (valid only for avr).  \n
            IRQ_FALLING_EDGE      // Falling edge generates an interrupt request. \n
            IRQ_RISING_EDGE       // Rising edge generates an interrupt request. \n

            irqMode is bit field for xmega . Bit field includes members pinX (X - pin number of selected port). \n
            All members that bit field must have value:

            IRQ_LOW_LEVEL         // The low level generates an interrupt request. \n
            IRQ_ANY_EDGE          // Any edge generates an interrupt request.  \n
            IRQ_FALLING_EDGE      // Falling edge generates an interrupt request. \n
            IRQ_RISING_EDGE       // Rising edge generates an interrupt request. \n
            IRQ_IS_DISABLED       // Pin is not used for interrupt request. \n

\param[in]
   f         - user's interrupt handler. Handler must be executed less than 100 us.
\return
  -1 - if irqNumber is out of range, \n
       not valid irq mode, \n
       such interrupt has been already registered. \n
   0 - otherwise.
******************************************************************************/
int HAL_RegisterIrq(HAL_IrqNumber_t irqNumber, HAL_IrqMode_t irqMode, void (*f)(void));

/**************************************************************************//**
\brief Enables the irqNumber interrupt.
\param[in]
   irqNumber - IRQ number
\return
   -1 - if irqNumber is out of range or has not been registered yet. \n
    0 - otherwise.
******************************************************************************/
int HAL_EnableIrq(HAL_IrqNumber_t irqNumber);

/**************************************************************************//**
\brief Disables the irqNumber interrupt.
\param[in]
   irqNumber - IRQ number
\return
   -1 - if irqNumber is out of range or has not been registered yet. \n
    0 - otherwise.
******************************************************************************/
int HAL_DisableIrq(HAL_IrqNumber_t irqNumber);

/**************************************************************************//**
\brief Unregisters the user's irqNumber interrupt
\param[in]
   irqNumber - IRQ number
\return
   -1 - if irqNumber is out of range or has not been registered yet. \n
    0 - otherwise.
******************************************************************************/
int HAL_UnregisterIrq(HAL_IrqNumber_t irqNumber);

#endif /* _IRQ_H */
//eof irq.h
