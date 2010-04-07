/**************************************************************************//**
  \file  nwkTxSecurity.h

  \brief Interface of transmission security.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    31/08/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_TX_SECURITY_H
#define _NWK_TX_SECURITY_H
#if defined _SECURITY_
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <mac.h>
#include <sspSfp.h>
#include <nwkTx.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Check of that enciphering for a proceeding network packet is required.
  \param dataReqObj - pointer to a request to send a network packet.
  \return 'true' if encrypting is required otherwise 'false'
 ******************************************************************************/
bool nwkIsEncryptingRequired(NwkDataReqObj_t *const dataReqObj);

/**************************************************************************//**
  \brief Request to encrypt an output network packet.
  \param encryptReq - encrypt frame primitive's parameters structure.
  \param macDataReq - MCPS-DATA request primitive's parameters structure.
 ******************************************************************************/
void nwkEncryptOutputPacket(SSP_EncryptFrameReq_t *const encryptReq,
  const MAC_DataReq_t *const macDataReq);

/**************************************************************************//**
  \brief Request to decrypt an output network packet.
  \param decryptReq - decrypt frame primitive's parameters structure.
  \param macDataReq - MCPS-DATA request primitive's parameters structure.
 ******************************************************************************/
void nwkDecryptOutputPacket(SSP_DecryptFrameReq_t  *const decryptReq,
  const MAC_DataReq_t *const macDataReq);

#endif /* _SECURITY_ */
#endif /* _NWK_TX_SECURITY_H */
/* eof nwkTxSecurity.h */

