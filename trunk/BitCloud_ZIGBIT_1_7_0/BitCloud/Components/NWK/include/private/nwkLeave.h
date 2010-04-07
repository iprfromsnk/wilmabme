/**************************************************************************//**
  \file nwkLeave.h

  \brief Network leave header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    27/06/07 V. Panov - Created.
    26/05/09 M. Gekk  - Refactoring
******************************************************************************/
#if !defined _NWK_LEAVE_H
#define _NWK_LEAVE_H
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <types.h>
#include <queue.h>
#include <nwkFrame.h>
#include <nwkConfig.h>

/******************************************************************************
                                Definitions section
 ******************************************************************************/
/* Size of NWK leave cmd payload. */
#define  NWK_LEAVE_CMD_PAYLOAD_SIZE  2
/* Total size of self leave cmd - NWK header + payload */
#define  NWK_LEAVE_ITSELF_CMD_SIZE  18
/* Total size of child leave cmd - NWK header + payload */
#define  NWK_LEAVE_CHILD_CMD_SIZE  26

/******************************************************************************
                                  Types section
 ******************************************************************************/
/* Internal states of NLME-LEAVE component */
typedef enum _NwkLeaveState_t
{
  NWK_LEAVE_IDLE_STATE = 0xE6,
  NWK_LEAVE_FIRST_STATE = 0x11,
  NWK_LEAVE_BEGIN_STATE = NWK_LEAVE_FIRST_STATE,
  NWK_LEAVE_SELF_SEND_CMD_STATE = 0x12,
  NWK_LEAVE_SELF_WAIT_CONFIRM_STATE = 0x13,
  NWK_LEAVE_SELF_RESET_MAC_STATE = 0x14,
  NWK_LEAVE_CHILD_SEND_CMD_STATE = 0x15,
  NWK_LEAVE_CHILD_WAIT_CONFIRM_STATE = 0x16,
  NWK_LEAVE_SELF_PREPARE_MAC_REQ_STATE = 0x17,
  NWK_LEAVE_CHILD_PREPARE_MAC_REQ_STATE = 0x18,
  NWK_LEAVE_CONFIRM_STATE = 0x19,
  NWK_LEAVE_LAST_STATE
} NwkLeaveState_t;

/* Leave Command Options Field */
typedef enum _NwkLeaveCommandOptionsField_t
{
  /* The Rejoin sub-field is a single-bit field. If the value of this 
   * sub-field is 1, the device that is leaving from its current parent 
   * will rejoin the network. If the value of this sub-field is 0, the device 
   * will not rejoin the network. ZigBee spec r17, 3.4.4.3.1.1, page 325. */
  NWK_LEAVE_REJOIN          = 0x20,
  /* The request sub-field is a single-bit field. If the value of this sub-field is 1, 
   * then the leave command frame is a request for another device to leave the network. 
   * If the value of this sub-field is 0, then the leave command frame is an indication 
   * that the sending device plans to leave the network.
   * ZigBee spec r17, 3.4.4.3.1.2, page 326. */
  NWK_LEAVE_REQUEST         = 0x40,
  /* The remove children sub-field is a single-bit field. If this sub-field has a value 
   * of 1, then the children of the device that is leaving the network will also be 
   * removed. If this sub-field has a value of 0, then the children of the device leaving 
   * the network will not be removed. ZigBee spec r17, 3.4.4.3.1.3, page 326. */
  NWK_LEAVE_REMOVE_CHILDREN = 0x80,
} NwkLeaveCommandOptionsField_t;

/* Internal variables of NLME-LEAVE component. */
typedef struct _NwkLeave_t
{
  /* finite-state machine */
  NwkLeaveState_t state;
  /* Queue of requests from upper layer */
  QueueDescriptor_t queue;
  /* Number of children which has been excluded from a network. */
  NwkSizeOfNeighborTable_t leaveChildCount;
  union 
  {
    /* MLME-RESET request primitive's parameters. */
    MAC_ResetReq_t  macReset;
    struct 
    {
      /* The short address of the leaved child. */
      ShortAddr_t  shortAddrOfChild;
      /* The extended address of the leaved child. */
      ExtAddr_t  extAddrOfChild;
      /* Parameters of send command request. */
      NwkCommandReq_t  commandReq;
    };
  };
#if defined(_ROUTER_) && defined(NWK_LEAVE_CHILD_ROUTER)
  /* The leave indication component is busy or not. */
  bool  leaveIndBusy;
  /* Leave request which is used by the leave indication component. */
  NWK_LeaveReq_t  leaveReq;
#endif
} NwkLeave_t;

/******************************************************************************
                            Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Main task handler of NLME-LEAVE component
 ******************************************************************************/
void nwkLeaveTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-LEAVE component
 ******************************************************************************/
void nwkResetLeave(void);

/**************************************************************************//**
  \brief Action when a leave command is received.
  \param payload - pointer to NPDU of NWK leave command.
  \param header  - nwk header.
  \param parse   - parsed header fields.
  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
bool nwkLeaveFrameInd(const uint8_t *const payload, const NwkFrameHeader_t *const header, 
    const NwkParseHeader_t *const parse);

#endif /* _NWK_LEAVE_H */
/* eof nwkLeave.h */
