/**************************************************************************//**
  \file  nwkJoinInd.h

  \brief Join indication header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 S. Vladykin - Created.
    10/12/08 M. Gekk     - Optimization of NWK memory.
    13/02/09 M. Gekk     - Refactoring
 ******************************************************************************/
#if !defined _NWK_JOININD_H
#define _NWK_JOININD_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include  <types.h>
#include  <mac.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Payload of rejoin response command */
BEGIN_PACK
typedef struct PACK
{
  uint8_t      commandId;
  /* If the rejoin was successful, this two-octet field contains the new network 
   * address assigned to the rejoining device. If the rejoin was not successful, 
   * this field contains the broadcast address (0xffff). ZigBee spec r17, 3.4.7.3.1. */
  uint16_t     networkAddr;
  /* This field shall contain one of the nonreserved association status values */
  uint8_t      rejoinStatus;
} NwkRejoinRespCmd_t;
END_PACK

/* Service fields of rejoin response */
typedef struct _NwkRejoinResp_t
{
  ExtAddr_t  extendedAddr;
  ShortAddr_t  newNetworkAddr;
  ShortAddr_t  oldNetworkAddr;
  NwkCommandReq_t  commandReq;
  uint8_t  status;
  bool  secureJoin;
} NwkRejoinResp_t;

/* States of join indication object */
typedef enum _NwkJoinIndObjState_t
{
  JOIN_IND_FREE_STATE  = 0x00,
  JOIN_IND_ASSOC_INDICATE_STATE = 0x01,
  JOIN_IND_REJOIN_INDICATE_STATE = 0x02,
  JOIN_IND_SEND_REJOIN_RESPONSE_STATE = 0x03,
  JOIN_IND_SEND_ASSOC_RESPONSE_STATE = 0x04
} NwkJoinIndObjState_t;

/* Join indication object */
typedef struct _NwkJoinIndObj_t
{
  NwkJoinIndObjState_t  state;
  MAC_CapabilityInf_t  capabilityInformation;
  union
  {
    MAC_AssociateResp_t  assocResp;
    NwkRejoinResp_t  rejoinResp;      
  };
} NwkJoinIndObj_t;

/* Array of join indication objects */
typedef struct _NwkJoinInd_t
{
  NwkCommandReq_t  *cmd;
  uint8_t  totalObjects;  
  NwkJoinIndObj_t  *objects;     
} NwkJoinInd_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) || defined(_COORDINATOR_)
/**************************************************************************//**
  \brief Rejoin request has been received.
  \param  payload - command payload pointer
  \param  header  - command parameters
  \param  parse   - source and destination extended address pointers
  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
bool nwkRejoinRequestFrameInd(const uint8_t *const payload, 
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Reporting of end device address conflict.
  \param child - pointer to child's entry in the neighbor table.
 ******************************************************************************/
void  nwkChangeEndDeviceAddress(NwkNeighbor_t *const child);

/**************************************************************************//**
  \brief Task handler of join indication component
 ******************************************************************************/
void nwkJoinIndTaskHandler(void);

/**************************************************************************//**
  \brief Reset the join indication component.
 ******************************************************************************/
void nwkResetJoinInd(void);

#else
#define  nwkRejoinRequestFrameInd  NULL
#define  nwkJoinIndTaskHandler  NULL
#define  nwkResetJoinInd  NULL
#endif /* _ROUTER_ or _COORDINATOR_ */
#endif /* _NWK_JOININD_H */
/* eof nwkJoinInd.h */
