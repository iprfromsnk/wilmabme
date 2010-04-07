/**************************************************************************//**
  \file nwkStatusInd.h

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07  V. Panov - Created
    16/06/09  M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_STATUS_IND_H
#define  _NWK_STATUS_IND_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include  <nwk.h>
#include  <nwkAddrConflict.h> 
#include  <nwkFrame.h>

/******************************************************************************
                              Types section
 ******************************************************************************/
/* Internal states of NWK status command receiver. */
typedef  enum  _NwkStateOfStatusReceiver_t
{
  NWK_STATUS_RECEIVER_IDLE_STATE = 0x6A,
  NWK_STATUS_RECEIVER_ADDR_CONFLICT_STATE = 0xDE
}  NwkStateOfStatusReceiver_t;

/* Internal variables of the NWK status command receiver. */
typedef  struct  _NwkStatusReceiver_t
{
  /* Current state of the NWK status command receiver. */
  NwkStateOfStatusReceiver_t  state;
  /* Parameters of address conflict resolution request. */
  NwkAddrConflictReq_t  addrConflict;
}  NwkStatusReceiver_t;

/******************************************************************************
                          Inline functions section
 ******************************************************************************/
/**************************************************************************//**
  \brief Wrapper for NLME-NWK-STATUS indication primitive.
  \param shortAddress - a network address of the device associated with 
     the status information.
  \param status - error code associated with the status indication.
 ******************************************************************************/
INLINE  void  nwkStatusIndicate(const ShortAddr_t shortAddr, 
  const NWK_StatusIndErrorCodes_t  status)
{ 
  NWK_NwkStatusInd_t ind;

  ind.shortAddress = shortAddr;
  ind.status = status;
  NWK_NwkStatusInd(&ind);
}

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Package transmission on link was completed unsuccessfully.
  \param dstAddress - a destination short address of link.
 ******************************************************************************/
void nwkStatusLinkFailure(const ShortAddr_t dstAddress);

/**************************************************************************//**
  \brief Package transmission on link was completed successfully.
  \param dstAddress - a destination short address of link.
 ******************************************************************************/
void nwkStatusLinkSuccess(const ShortAddr_t dstAddress);

#if defined(_ROUTER_) || defined(_COORDINATOR_)
/**************************************************************************//**
  \brief NWK status command has been received.
  \param payload - pointer to status code field and destination address.
  \param header - NWK header of the network status command.
  \param parse - parsed NWK header.
  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
bool nwkStatusFrameInd(const uint8_t *const payload, const NwkFrameHeader_t *const header, 
  const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Reset NWK status receiver.
 ******************************************************************************/
void  nwkResetStatusReceiver(void);

#else
#define  nwkStatusFrameInd  NULL
#define  nwkResetStatusReceiver  NULL
#endif  /* _ROUTER_ or _COORDINATOR_ */
#endif  /* _NWK_STATUS_IND_H */
/* eof nwkStatusInd.h */

