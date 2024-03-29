/**************************************************************************//**
  \file sspHashHandler.h

  \brief Hash routine header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
      29/11/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _SSPHASHHANDLER_H
#define _SSPHASHHANDLER_H

#ifdef _HIGH_SECURITY_

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <types.h>
#include <sspCommon.h>

/******************************************************************************
                        Definitions section.
******************************************************************************/
#define MAX_HASH_TEXT_SIZE 53 // 1 + 2*sizeof(uint64_t) + 2*CHALLENGE_SIZE + sizeof(uint32_t)
#define IPAD               0x36
#define OPAD               0x5C

/******************************************************************************
                        Types' definitions section.
******************************************************************************/
/******************************************************************************
  TBD
******************************************************************************/
typedef struct
{
  // Service field - for internal needs.
  SSP_Service_t service;
  // There is should be an additional memory before and after text (16 bytes in both cases).
  uint8_t *text/*[SECURITY_KEY_SIZE + textSize + 16]*/;
  // Pointer to key fir Keyed Hash Function.
  uint8_t (*key)[SECURITY_KEY_SIZE];
  // Size of the text.
  uint8_t textSize;
  // Buffer for generated hash. Shoul be initialized by the user.
  uint8_t (*hash_i)[SECURITY_KEY_SIZE];
  void (*sspKeyedHashMacConfirm)(void);
} SspKeyedHashMacReq_t;

/******************************************************************************
  TBD
******************************************************************************/
typedef enum
{ 
  HASH_STATE_IDLE,
  HASH_STATE_CREATE_HASH1,
  HASH_STATE_CREATE_HASH2,
} SspHashHandlerState_t;

/******************************************************************************
  TBD
******************************************************************************/
typedef struct
{
  uint8_t *M/*[textSize + 16]*/;
  uint8_t (*hash_i)[SECURITY_KEY_SIZE];
  uint8_t textSize;
  void (*bcbHashConf)(void);
} SspBcbHashReq_t;

/******************************************************************************
  TBD
******************************************************************************/
typedef struct
{ 
  SspBcbHashReq_t       *currentBcbHashReq;
  SspKeyedHashMacReq_t  *keyedHashMacReq;
  SspBcbHashReq_t       bcbHashReq;
  uint8_t               bcbBlockCounter;
  SspHashHandlerState_t hashHandlerState;
} SspHashHandlerMem_t;


/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Keyed hash function implementation.
  Parameters:
    param - parameters of the primitive (for detailed description look at 
             SspKeyedHashMacReq_t declaration).
  Return:
    none.
********************************************************************************/
void sspKeyedHashMacReq(SspKeyedHashMacReq_t *param);

/*******************************************************************************
  Block Cipher Based hash function implementation.
  Parameters:
    param - parameters of the primitive (for detailed description look at 
             SspBcbHashReq_t declaration).
  Return:
    none.
********************************************************************************/
void sspBcbHashReq(SspBcbHashReq_t *param);

#endif // _HIGH_SECURITY_

#endif //_SSPHASHHANDLER_H

//eof sspHashHandler.h
