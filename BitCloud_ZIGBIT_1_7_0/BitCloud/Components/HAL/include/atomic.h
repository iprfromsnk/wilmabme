/**************************************************************************//**
  \file  atomic.h

  \brief The header file describes the atomic sections

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    20/08/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
 
#ifndef _ATOMIC_H
#define _ATOMIC_H

/******************************************************************************
                   Includes section
******************************************************************************/
#if defined(AT91SAM7X256)
  #include <inttypes.h>
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) \
   || defined(ATXMEGA128A1) || defined(ATXMEGA256A3) || defined(ATMEGA128RFA1)
  #include <halAtomic.h>
#endif

#if defined(AT91SAM7X256)
/******************************************************************************
                   Types section
******************************************************************************/
typedef  uint32_t atomic_t;

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/******************************************************************************
 Disables global interrupt. Enter atomic section.
******************************************************************************/
void halStartAtomic(atomic_t volatile *pAtomic);

/******************************************************************************
 Exit atomic section
******************************************************************************/
void halEndAtomic(atomic_t volatile *pAtomic);
#endif

#if defined(AT91SAM7X256)
  /** \brief Marks the begin of atomic section */
  #define ATOMIC_SECTION_ENTER  {volatile atomic_t __atomic; halStartAtomic(&__atomic);
  /** \brief Marks the end of atomic section */
  #define ATOMIC_SECTION_LEAVE  halEndAtomic(&__atomic);}
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) \
   || defined(ATXMEGA128A1) || defined(ATXMEGA256A3) || defined(ATMEGA128RFA1)
  /** \brief Marks the begin of atomic section */
  #define ATOMIC_SECTION_ENTER {atomic_t __atomic = halStartAtomic();
  /** \brief Marks the end of atomic section */
  #define ATOMIC_SECTION_LEAVE halEndAtomic(__atomic);}
#endif

#endif
// eof atomic.h
