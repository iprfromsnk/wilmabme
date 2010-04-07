/**************************************************************************//**
  \file sspSfpHandler.h

  \brief SFP routine header file.

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

#ifndef _SSPSFPHANDLER_H
#define _SSPSFPHANDLER_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <sspManager.h>
#include <sspSfp.h>
#include <sspAesHandler.h>
#include <sspCcmHandler.h>


/******************************************************************************
                        Definitions section.
******************************************************************************/
#define SECURITY_CONTROL_FIELD_LENGTH 1
#define FRAME_COUNTER_FIELD_LENGTH    4
#define KEY_SEQ_NUMBER_FIELD_LENGTH   1

/******************************************************************************
                        Types definition section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD
******************************************************************************/
typedef enum
{
  SFP_STATE_IDLE,
  SFP_STATE_ENCRYPTION_KEY_TRANSFORMING,
  SFP_STATE_ENCRYPTION_AUTHENTIC,
  SFP_STATE_ENCRYPTION_ENCRYPT,
  SFP_STATE_DECRYPTION_KEY_TRANSFORMING,
  SFP_STATE_DECRYPTION_AUTHENTIC,
  SFP_STATE_DECRYPTION_ENCRYPT
} SspSfpHandlerState_t;

/**************************************************************************//**
  \brief TBD
******************************************************************************/
typedef struct
{
  SspSfpHandlerState_t sfpState;
  uint8_t              nonce[CCM_NONCE_SIZE];
  uint8_t              transformedKey[SECURITY_KEY_SIZE];
  uint8_t              mic[CCM_MIC_MAX_SIZE];
  uint8_t              auxiliaryHeaderLength;
  union
  {
    CcmReq_t             ccmReq;
#ifdef _HIGH_SECURITY_
    SspKeyedHashMacReq_t hashMacReq;
#endif // _HIGH_SECURITY_
  };
  struct
  {
    uint8_t keyExpander[16];
    uint8_t text;
    uint8_t bitsExpander[16]; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }; // For hash function
} SspSfpHandlerMem_t;

/**************************************************************************//**
  \brief Security Control field format.
******************************************************************************/
typedef struct
{
  uint8_t securityLevel : 3;
  uint8_t keyIdentifier : 2;
  uint8_t extendedNonce : 1;
  uint8_t reserved      : 2;
} SecurityCtrlField_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  Encrypts frame. Encoding is based on incoming param which are extracted from
  SSP_EncryptFrameReq param.
  Parameters:
    none.
  Return:
    none.
******************************************************************************/
void sspEncryptFrameReqHandler(void);

/******************************************************************************
  Decrypts frame. Decrypting is based on incoming param which are extracted from
  SSP_DecryptFrameReq param.
  Parameters:
    none.
  Return:
    none.
******************************************************************************/
void sspDecryptFrameReqHandler(void);

/******************************************************************************
  Parses auxiliary frame header.
  Parameters:
    param - contains pointer to the frame and parameters to be initialized.
  Return:
    Auxiliary header length.
******************************************************************************/
uint8_t sspParseAuxiliaryHeaderHandler(SSP_ParseAuxiliaryHeader_t *param);

/******************************************************************************
  Security Frame Processor Handler's task.
  Parameters:
    none
  Return:
    none.
******************************************************************************/
void sspSfpTaskHandler(void);

#endif //_SSPSFPHANDLER_H

// eof sspSfpHandler.h
