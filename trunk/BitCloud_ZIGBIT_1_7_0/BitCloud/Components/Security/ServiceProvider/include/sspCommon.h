/**************************************************************************//**
  \file sspCommon.h
  
  \brief Declarations of common Security Service Provider's fields and types.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
      06/12/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _SSPCOMMON_H
#define _SSPCOMMON_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <types.h>

/******************************************************************************
                        Definitions section.
******************************************************************************/
#define SECURITY_KEY_SIZE   16
#define SECURITY_BLOCK_SIZE 16

/******************************************************************************
                        Types section.
******************************************************************************/
/**************************************************************************//**
  \brief Possible status values of different SSP primitives.
******************************************************************************/
typedef enum
{
  SSP_SUCCESS_STATUS,
  SSP_NOT_PERMITED_STATUS,
  SSP_MAX_FRM_COUNTER_STATUS,
  SSP_BAD_CCM_OUTPUT_STATUS,
} SSP_Status_t;

/**************************************************************************//**
  \brief Internal service fields which give an opportunity to compose requests' queue.
******************************************************************************/
typedef struct                         
{
  void    *next;
  uint8_t requestId;
} SSP_Service_t;

#endif //_SSPCOMMON_H

// eof sspCommon.h
