/*************************************************************************//**
  \file apsSmSsp.c

  \brief APS SSP features header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMSSP_H
#define _APSSMSSP_H

#ifdef _SECURITY_

#include <apsMemoryManager.h>
#include <apsSecurityManager.h>


typedef enum
{
  APS_SM_SSPE_SUCCESS_STATUS  = 0x00,
  APS_SM_SSPE_START_STATUS,
  APS_SM_SSPE_FAIL_STATUS,
} ApsSspeStatus_t;


#ifdef _HIGH_SECURITY_
typedef enum
{
  APS_SM_SSPD_SUCCESS_STATUS  = 0x00,
  APS_SM_SSPD_START_STATUS,
  APS_SM_SSPD_FAIL_STATUS,
} ApsSspdStatus_t;
#endif
 
/*****************************************************************************
  APS Frame Encrypt Function
  Parameters: buffer      - APS Security Manager buffer pointer
              dstExtAddr  - destination extended address pointer
              apduLength  - APDU length
  Returns:    APS_SM_SSPE_START_STATUS - encryption process started
              APS_SM_SSPE_FAIL_STATUS - encryption failed
              APS_SM_SSPE_SUCCESS_STATUS - encryption not required
                                                   (not needed)
*****************************************************************************/
uint8_t apsEncryptFrame(ApsBuffer_t *buffer, const ExtAddr_t *dstExtAddr, uint8_t headerLength, uint8_t apduLength);


#ifdef _HIGH_SECURITY_
extern uint32_t *apsSmGetNwkInFrameCounter(NWK_SecMaterialDescriptor_t *keyDescriptor, const ExtAddr_t *srcExtAddr);
extern void apsSmSspProcess(void);
extern void apsSmSecuredNwkDataIndHandler(NWK_DataInd_t *ind);



/*****************************************************************************
  Make a search of key-pair descriptor for extended address specified
  Parameters: address - 64-bit IEEE device address pointer 
  Returns:    NULL - key-pair descriptor not found
              valid key-pair descriptor pointer - in other case
*****************************************************************************/
extern ApsKeyPairDescriptor_t *apsSmGetKeyPairDescriptor(const ExtAddr_t *address);
extern uint8_t *apsSmGetLinkKey(ApsKeyPairDescriptor_t *keyDescriptor);
extern void apsSmSetLinkKey(ApsKeyPairDescriptor_t *keyPairSetDescriptor, uint8_t *key);
extern uint8_t *apsSmGetMasterKey(ApsKeyPairDescriptor_t *keyPairDescriptor);
#endif //#ifdef _HIGH_SECURITY_

extern NWK_SecMaterialDescriptor_t *apsSmGetNwkKeyDescriptor(uint8_t keySeqNumber);
extern NWK_SecurityIB_t *apsSmGetNwkSecurityIb(void);
extern uint8_t *apsSmGetNwkKey(NWK_SecMaterialDescriptor_t *keyDescriptor);
extern void apsSmResetKeyPairSet(void);
extern void apsSmSetNwkSecurityLevel(uint8_t securityLevel);
extern uint8_t apsSmGetNwkSecurityLevel(void);

extern void apsResetSmSsp(void);


extern void apsSmSetNwkSecureAllFrames(bool value);
extern bool apsSmGetNwkSecureAllFrames(void);


extern bool isKeyValid(uint8_t *key);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMSSP_H

//eof apsSmSsp.h

