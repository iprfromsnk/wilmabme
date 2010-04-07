/**************************************************************************//**
  \file  nwkLinkStatus.h

  \brief The data structures concerning processing of LinkStatus command

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    01/08/07 V. Panov - Created.
    10/04/09 M. Gekk  - Refactoring
 ******************************************************************************/
/* The link status command frame allows neighboring routers to communicate their
 * incoming link costs to each other as described in sub-clause 3.6.3.4. Link 
 * status frames are transmitted as one-hop broadcasts without retries.
 * ZigBee spec r17, 3.4.8, page 330.
 * */
#if !defined _NWK_LINK_STATUS_H
#define _NWK_LINK_STATUS_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <appTimer.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Internal states of the link status component. */
typedef enum _NwkLinkStatusState_t
{
  NWK_LINK_STATUS_IDLE_STATE  = 0x00,
  NWK_LINK_STATUS_WAIT_STATE  = 0x01,
  NWK_LINK_STATUS_SEND_STATE  = 0x02
} NwkLinkStatusState_t;

/* Internal parameters of the link status component. */
typedef struct _NwkLinkStatus_t
{
  NwkLinkStatusState_t state; /* finite-state machine */
  NwkCommandReq_t commandReq; /* request to send the link status command packet. */
  HAL_AppTimer_t  timer; /* The timer of counting of the link status period. */
} NwkLinkStatus_t;

BEGIN_PACK
/* Command Options Field*/
typedef struct PACK _NwkLinkStatusOptions_t
{
  /* This field indicates the number of link status entries */
  uint8_t  entryCount : 5;   
  /* The first frame sub-field is set to 1 if this is the first frame of 
   * the sender’s link status.*/
  uint8_t  firstFrame : 1;   
  /* The last frame sub-field is set to 1 if this is the last frame of 
   * the sender’s link status. */
  uint8_t  lastFrame  : 1;
  uint8_t  reserved   : 1;
} NwkLinkStatusOptions_t;

/* Link Status Entry. ZigBee spec r17, 3.4.8.3.2 */
typedef struct PACK _NwkLinkStatusEntry_t
{
  /* The incoming cost field contains the device’s estimate of the link cost 
   * for the neighbor, which is a value between 1 and 7.*/
  uint8_t incomingCost : 3;
  uint8_t reserved1    : 1;
  /* The outgoing cost field contains the value of the outgoing cost field 
   * from the neighbor table.*/
  uint8_t outgoingCost : 3;
  uint8_t reserved2    : 1;
} NwkLinkStatusEntry_t;

/* Link status item. ZigBee spec r17, figure 3.23. */
typedef struct PACK _NwkLinkStatusItem_t
{
  /* Each link status entry contains the network address of a router neighbor. */
  ShortAddr_t           addr;
  /* Link Status Entry. */
  NwkLinkStatusEntry_t  linkStatus;
} NwkLinkStatusItem_t;

/* The NWK command payload of the link status command. ZigBee spec r17, figure 3.21. */
typedef struct PACK _NwkLinkPayload_t
{
  NwkLinkStatusOptions_t options;
  NwkLinkStatusItem_t    table[1];
} NwkLinkStatusPayload_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) || defined(_COORDINATOR_)
/**************************************************************************//**
  \brief Reset the link status component
 ******************************************************************************/
void nwkResetLinkStatus(void);

/**************************************************************************//**
  \brief Action when link status command received
  \param payload - command payload
  \param header  - nwk header
  \param parse   - parsed header fields
  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
bool nwkLinkStatusInd(const uint8_t *const payload, const NwkFrameHeader_t *const header, 
  const NwkParseHeader_t *const parse);

#else
#define  nwkResetLinkStatus  NULL
#define  nwkLinkStatusInd  NULL
#endif  /* _ROUTER_ or _COORDINATOR_ */
#endif  /* _NWK_LINK_STATUS_H */
/* eof nwkLinkStatus.h */
