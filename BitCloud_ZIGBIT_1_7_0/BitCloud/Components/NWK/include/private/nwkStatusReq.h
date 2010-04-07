/**************************************************************************//**
  \file nwkStatusReq.h

  \brief Interface of the network status sender.
   
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    23/06/2009  Max Gekk - Created
 ******************************************************************************/
#if  !defined  _NWK_STATUS_REQ_H
#define  _NWK_STATUS_REQ_H
/******************************************************************************
                              Includes section
 ******************************************************************************/
#include <nwk.h>
#include <nwkCommands.h>

/******************************************************************************
                            Definitions section
 ******************************************************************************/
/* Size of NWK status command payload: 
 * - command id - 1 octet
 * - status code - 1 octet
 * - destination address - 2 octet */
#define  NWK_STATUS_CMD_PAYLOAD_SIZE  4

/******************************************************************************
                               Types section
 ******************************************************************************/
/* Confirmation paramters of NWK status command sending. */
typedef  struct  _NwkStatusConf_t
{
  /* Status of NWK status command sending.*/
  NWK_Status_t  status;
}  NwkStatusConf_t;

/* Type of NWK status request parameters. */
typedef  struct  _NwkStatusReq_t
{
  /* Service field - for internal needs. */
  struct
  {
    void  *next;
  }  service;
  /* Value of status code field in network status frame. */
  NWK_StatusIndErrorCodes_t  statusCode;
  /* Target address for this network status command. */
  ShortAddr_t  targetAddr;
  /* Destination address for this network status command. */
  ShortAddr_t  dstAddr;
  /* Callback for request to send of the NWK status command.*/
  void  (* nwkStatusConf)(NwkStatusConf_t  *conf);
  NwkStatusConf_t  confirm;
}  NwkStatusReq_t;

/* Network status command frame format. ZigBee spec r17, figure 3.15. */
BEGIN_PACK
typedef  struct PACK  _NwkStatusCommandPayload_t
{
  /* Command frame identifier. */
  uint8_t  commandId;
  /* Status code field. This field shall be set to one of the non-reserved 
   * values shown in ZigBee spec r17, Table 3.42. */
  uint8_t  statusCode;
  /* The destination address field is 2 octets in length and shall be present if, 
   * and only if, the network status command frame is being sent in response to 
   * a routing failure. In this case, it shall contain the destination address from 
   * the data frame that encountered the failure. ZigBee spec r17, 3.4.3.3.2, page 324. */
  uint16_t  dstAddr;
}  NwkStatusCommandPayload_t;
END_PACK

/* Internal states of NWK status command sender. */
typedef  enum  _NwkStateOfStatusSender_t
{
  NWK_STATUS_SENDER_IDLE_STATE = 0x78,
  NWK_STATUS_SENDER_FIRST_STATE = 0x20,
  NWK_STATUS_SENDER_PREPARE_MAC_DATA_STATE = NWK_STATUS_SENDER_FIRST_STATE,
  NWK_STATUS_SENDER_PREPARE_MAC_REQ_STATE = 0x21,
  NWK_STATUS_SENDER_SEND_STATE = 0x22,
  NWK_STATUS_SENDER_LAST_STATE
}  NwkStateOfStatusSender_t;

/* Internal variables of the NWK status command sender. */
typedef  struct  _NwkStatusSender_t
{
  /* Current state of NWK status sender. */
  NwkStateOfStatusSender_t  state;
  /* Queue of requests to send NWK status command. */
  QueueDescriptor_t  queue;
  /* Request to send any command. */
  NwkCommandReq_t  commandReq;
  /* Total size of NWK status command - payload size and header size.*/
  uint8_t  sizeOfStatusCmd;
  /* Route error command is sent. */
  bool  routeErrorBusy;
  /* The request to send the route error status command. */
  NwkStatusReq_t  routeError;
}  NwkStatusSender_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) || defined(_COORDINATOR_)
/**************************************************************************//**
  \brief Request to send a network status command.
  \param req - request information: statusCode, destination address and etc.
 ******************************************************************************/
void  nwkStatusReq(NwkStatusReq_t  *req);

/**************************************************************************//**
  \brief Reset NWK status sender.
 ******************************************************************************/
void  nwkResetStatusSender(void);

/**************************************************************************//**
  \brief Send the status command with status code NWK_NO_ROUTE_AVAILABLE.
  \param srcAddr - source address of route path.
  \param dstAddr - distination address of route path.
 ******************************************************************************/
void  nwkSendRouteErrorStatus(const ShortAddr_t srcAddr, const ShortAddr_t dstAddr);

#else
#define  nwkResetStatusSender  NULL
#endif  /* _ROUTER_ or _COORDINATOR_ */
#endif  /* _NWK_STATUS_REQ_H */
/* nwkStatusReq.h */

