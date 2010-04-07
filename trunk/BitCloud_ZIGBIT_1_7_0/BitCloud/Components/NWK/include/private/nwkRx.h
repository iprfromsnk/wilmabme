/**************************************************************************//**
  \file  nwkRx.h

  \brief Functions of processing of input data

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 V. Panov - Created.
    25/11/08 M. Gekk  - Counters of buffers have been remote.
    10/12/08 M. Gekk  - Memory optimization
    08/07/09 M. Gekk  - Redesign
 ******************************************************************************/
#if !defined _NWK_RX_H
#define _NWK_RX_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include  <mac.h> 
#if defined _SECURITY_
#include  <sspSfp.h>
#endif /* _SECURITY_ */

/******************************************************************************
                               Types section
 ******************************************************************************/
/* Input packet meta information. */
typedef struct _NwkInputPacket_t
{
  bool  indicate            :1;
  bool  retransmit          :1;
  bool  decryptRequired     :1;
  uint8_t  reserved         :5;
  uint8_t  *data;
  uint8_t  length;
  NwkParseHeader_t parsedHeader;
  union
  {
    NWK_DataInd_t  dataInd;
#if defined _SECURITY_
    SSP_DecryptFrameReq_t  decryptReq;
#endif /* _SECURITY_ */
  };
} NwkInputPacket_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Handler of incoming packets from MAC-layer
  \param macDataInd - MCPS-DATA indication primitive's parameters.
 ******************************************************************************/
void MAC_DataInd(MAC_DataInd_t *macDataInd);

/**************************************************************************//**
  \brief Confirmation handler of sending an input packet.
  \param inPkt - an input network packet.
 ******************************************************************************/
//void nwkTxTransitPacketConf(NwkInputPacket_t *const inPkt);

/**************************************************************************//**
  \brief The upper layer has completed data processing.
  \param resp - NLDE-DATA indication primitive's parameters structure.
******************************************************************************/
void NWK_DataResp(NWK_DataResp_t *resp);
 
#endif /* _NWK_RX_H */
/* eof nwkRx.h */

