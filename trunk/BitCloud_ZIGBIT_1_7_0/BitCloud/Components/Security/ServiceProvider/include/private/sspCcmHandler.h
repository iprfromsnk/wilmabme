/**************************************************************************//**
  \file sspCcmHandler.h

  \brief CCM routine header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      2006 - VGribanovsky created.
      29/11/2007 - ALuzhetsky API corrected.
******************************************************************************/
#ifndef _SSPCCMHANDLER_H
#define _SSPCCMHANDLER_H


/******************************************************************************
                        Includes section.
******************************************************************************/
#include <types.h>


/******************************************************************************
                        Definitions section.
******************************************************************************/
#define CCM_MIC_MAX_SIZE 16
#define CCM_NONCE_SIZE   13

/******************************************************************************
                        Types' definitions section.
******************************************************************************/
/**************************************************************************//**
  TBD
******************************************************************************/
typedef enum // To be killed!!!
{
  CCM_STATE_IDLE,
  CCM_STATE_SET_KEY_WHILE_AUTHENTIC,
  CCM_STATE_SET_KEY_WHILE_ENCRYPT,
  CCM_STATE_CALCULATE_X1,
  CCM_STATE_CALCULATE_XN_FOR_HEADER,
  CCM_STATE_CALCULATE_XN_FOR_PAYLOAD,
  CCM_STATE_CALCULATE_LAST_X_FOR_HEADER,
  CCM_STATE_CALCULATE_LAST_X_FOR_PAYLOAD,
  CCM_STATE_CRYPT_NEXT_PAYLOAD_BLOCK,
  CCM_STATE_CRYPT_MIC
} SspCcmState_t;

/**************************************************************************//**
  \brief Input param structure for CCM encrypt & authentification  
  OR decode & authentification check.
******************************************************************************/
typedef struct 
{
  // key
  uint8_t (*key)[SECURITY_KEY_SIZE];
  // nonce
  uint8_t (*nonce)[CCM_NONCE_SIZE];
  // header
  uint8_t *a/*[len_a]*/;
  // pdu
  uint8_t *m/*[len_m]*/;
  // MIC length (or MAC - message authentication code).
  uint8_t M;
  // header length
  uint8_t len_a;
  // pdu length
  uint8_t len_m;
  // mic
  uint8_t *mic/*[M]*/;
  // aes temp buffer
  //uint8_t (*aesTemp)[AES_TEMP_BUF_SIZE];
  // aes text buffer
  //uint8_t (*aesText)[SECURITY_BLOCK_SIZE];
  void (*ccmConfirm)(void);
} CcmReq_t;

/******************************************************************************
  \brief Cryptographic context. Used for only for MIC generation and checking.
******************************************************************************/
typedef struct
{
  uint8_t textSize;
  uint8_t *text/*[textSize]*/;
  uint8_t (*prevX)[SECURITY_BLOCK_SIZE];
  uint8_t (*key)[SECURITY_KEY_SIZE];
  uint8_t (*aesTemp)[AES_TEMP_BUF_SIZE];
} CcmAuthCtx_t;

/******************************************************************************
  \brief Cryptohraphic ontext for encryption/decryption operations.
******************************************************************************/
typedef struct
{
//  uint8_t textSize;
//  uint8_t *text/*[textSize]*/;
  uint8_t counter;
  uint8_t (*nonce)[CCM_NONCE_SIZE];
  uint8_t (*key)[SECURITY_KEY_SIZE];
  uint8_t (*aesText)[SECURITY_BLOCK_SIZE];
  uint8_t (*aesTemp)[AES_TEMP_BUF_SIZE];
} CcmCryptCtx_t;

/**************************************************************************//**
  TBD
******************************************************************************/
typedef struct
{
  SspCcmState_t ccmState;
  CcmReq_t   *ccmReq;
  uint8_t    x_i[SECURITY_BLOCK_SIZE];
  union
  {
    CcmAuthCtx_t  ccmAuthCtx;
    CcmCryptCtx_t ccmCryptCtx;
  };
} SspCcmHandlerMem_t;


/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  Calculate the CCM* authentication tag (CBC-MAC in RFC 3610 terms).
  Arguments:
    key - AES-128 key;
    nonce_block - 16-byte block containing nonce in bytes 1..13
    (bytes 0,14,15 are arbitrary);
    frame - ptr to data to be protected by the authentication tag;
    len_auth - data that have to be authentified only;
    len_crypt - data that have to be authentified and encrypted;
    auth - buffer to place the authentication tag;
    M - MIC length,
    temp - 176-byte array used by AES encryption algorithm.
    If M=0 (which is permitted by ZigBee Standard but not by RFC 3610)
    the function returns immediately.
  Limitations: does not work correctly if len_auth >= 0xfeff.
******************************************************************************/
void ccmAuthReq(CcmReq_t *ccmParam);


/******************************************************************************
  Encrypt the buffer in place by the CCM*. Arguments:
    key - AES-128 key;
    nonce_block - 16-byte block containing nonce in bytes 1..13
    (bytes 0,14,15 are arbitrary);
    payload - buffer to be encrypted;
    len_payload - length of this buffer;
    auth - MIC which have to be encrypted additionally (also in place);
    M - its length;
    temp - 176-byte array used by AES encryption algorithm.
******************************************************************************/
void ccmEncryptReq(CcmReq_t *);

#endif //_SSPCCMHANDLER_H

//eof sspCcmHandler.h
