/**************************************************************************//**
  \file nwkSystem.h

  \brief Nerwork system header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    20/06/07  V. Panov - Created.
    16/08/09  M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWKSYSTEM_H
#define _NWKSYSTEM_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include <types.h>

/******************************************************************************
                            Definitions section
 ******************************************************************************/
#define FIELD_OFFSET(TYPE, FIELD)  offsetof(TYPE, FIELD)

#define GET_PARENT_BY_FIELD(TYPE, FIELD, FIELD_POINTER)  \
  ((TYPE *)(((uint8_t *)FIELD_POINTER) - FIELD_OFFSET(TYPE, FIELD)))

/* Converting of time value from milliseconds to seconds.  */ 
#define NWK_MSEC_TO_SEC(time)  ((time) >> 10)
/* Converting of time value from seconds to milliseconds.  */ 
#define NWK_SEC_TO_MSEC(time)  ((time) << 10) 

#define IS_CORRECT_BROADCAST_ADDR(A) \
  ((0xFFFF == (A))||((0xFFFB <= (A))&&((A) <= 0xFFFD)))

#define NWK_NO_EXT_ADDR         0ULL
#define IS_CORRECT_EXT_ADDR(A)  (NWK_NO_EXT_ADDR != (A))

#define IS_CORRECT_EXT_PANID(P) ((0 < (P)) && ((P) < 0xFFFFFFFFFFFFFFFFULL))
#define NWK_NO_EXT_PANID  0ULL

#define NWK_INVALID_PANID  0xFFFF

#endif /* _NWKSYSTEM_H */
/* eof nwkSystem.h */

