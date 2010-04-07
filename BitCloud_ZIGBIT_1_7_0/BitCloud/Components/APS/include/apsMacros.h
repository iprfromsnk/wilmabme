/*************************************************************************//** 
  \file apsMacros.h

  \brief The header file describes the public APS macroses

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal

*****************************************************************************/ 

#ifndef _APSMACROS_H
#define _APSMACROS_H

/******************************************************************************
                   Includes section
******************************************************************************/

/******************************************************************************
                   Define(s) section
******************************************************************************/
#undef FIELD_OFFSET
#define FIELD_OFFSET(struct_type, field_name) (((uint8_t*) &((struct_type *)(NULL))->field_name) - (uint8_t*)NULL)
#define GET_STRUCT_BY_FIELD_POINTER(struct_type, field_name, field_pointer) ((struct_type *) (((uint8_t *) field_pointer) - FIELD_OFFSET(struct_type, field_name)))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define SET_FLAG(FLAG_VARIABLE, FLAG_ID) \
          do {FLAG_VARIABLE |= 1 << FLAG_ID;} while(0)

#define CLR_FLAG(FLAG_VARIABLE, FLAG_ID) \
          do {FLAG_VARIABLE &= ~(1 << FLAG_ID);} while(0)

#define GET_FLAG_VALUE(FLAG_VARIABLE, FLAG_ID) \
          (FLAG_VARIABLE & (1 << FLAG_ID))

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
                   Inline static functions section 
******************************************************************************/

#endif  //#ifndef _APSMACROS_H

//eof apsMacros.h
