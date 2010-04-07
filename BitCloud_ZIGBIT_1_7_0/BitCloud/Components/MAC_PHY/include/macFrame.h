/**************************************************************************//**
  \file macFrame.h
  
  \brief MAC frame fields' declarations.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).
  
  \internal
    History:     
      19/06/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _MACFRAME_H
#define _MACFRAME_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <macBeacon.h>
#include <macAssociate.h>
#include <macDisassociate.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
//! Beacon frame type. IEEE 802.15.4-2006 Table 79.
#define MAC_BEACON_FRAME_CODE   0x00
//! Data frame type. IEEE 802.15.4-2006 Table 79.
#define MAC_DATA_FRAME_CODE     0x01
//! Ack frame type. IEEE 802.15.4-2006 Table 79.
#define MAC_ACK_FRAME_CODE      0x02
//! Command frame type. IEEE 802.15.4-2006 Table 79.
#define MAC_CMD_FRAME_CODE      0x03

//! IEEE 802.15.4-2003 standart frames.
#define FRAME_VERSION_2003 0x00
//! IEEE 802.15.4-2006 standart frames.
#define FRAME_VERSION_2006 0x01

#ifdef _MAC_IEEE_STD_2003_
#define FRAME_VERSION FRAME_VERSION_2003
#else
#define FRAME_VERSION FRAME_VERSION_2006
#endif

#define MAC_FRAME_CONTROL_FIELD_SIZE 2
#define MAC_SUPERFRAME_SPEC_FIELD_SIZE 2
#define MAC_GTS_LIST_FIELD_SIZE 3 ///< See IEEE 802.15.4-2006 chart 7.2.2.1.5
#define MAC_GTS_SPEC_FIELD_SIZE 1
#define MAC_PEND_ADDR_SPEC_FIELD_SIZE 1
#define MAC_CAPABILITY_INF_FIELD_SIZE 1

/******************************************************************************
                        Types section
******************************************************************************/
//! Set of possible frame types and commands. 
typedef enum
{
  MAC_UNKNOWN_FRAME_TYPE,
  MAC_BEACON_FRAME_TYPE,
  MAC_DATA_FRAME_TYPE,
  MAC_ACK_FRAME_TYPE,
  MAC_ASSOCIATE_REQ_CMD_FRAME_TYPE,
  MAC_ASSOCIATE_RESP_CMD_FRAME_TYPE,
  MAC_DISASSOCIATE_NOTIF_CMD_FRAME_TYPE,
  MAC_DATA_REQ_CMD_FRAME_TYPE,
  MAC_PANID_CONFLICT_NOTIF_CMD_FRAME_TYPE,
  MAC_ORPHAN_NOTIF_CMD_FRAME_TYPE,
  MAC_BEACON_REQ_CMD_FRAME_TYPE,
  MAC_COORD_REALIG_CMD_FRAME_TYPE,
  //MAC_GTS_REQ_CMD_FRAME_TYPE,
}  MAC_Frame_t;

//! Frame contol field. IEEE 802.15.4-2006, Figure 42.
typedef struct // Frame control.
{
  uint16_t type         : 3;
  uint16_t security     : 1;
  uint16_t framePending : 1;
  uint16_t ack          : 1;
  uint16_t intraPAN     : 1;
  uint16_t reserved1    : 3;
  uint16_t dstAddrMode  : 2;
  uint16_t frameVersion : 2;
  uint16_t srcAddrMode  : 2;
}  MAC_FrameCtrl_t;

//! Associate request payload description.
typedef struct
{
  //! See IEEE 802.15.4-2006, Figure 56.
  MAC_CapabilityInf_t capability;
}  MAC_AssociateReqPldDescr_t;

//! Beacon description.
typedef struct
{
  //uint32_t              timeStamp;
  //! Channel on which beacon was received.
  uint8_t               channel;
  //! Superframe specification field, IEEE 802.15.4-2006 Figure 47.
  MAC_SuperframeSpec_t  superframeSpec;
  //! GTS specification field, IEEE 802.15.4-2006 Figure 48.
  MAC_GtsSpec_t         gtsSpec;
  //! GTS direction field,  IEEE 802.15.4-2006 Figure 49.
  MAC_GtsDirection_t    gtsDirection;
  //! IEEE 802.15.4-2006, 7.2.2.1.5 GTS List field.
  MAC_GtsDescr_t        *gtsList[MAC_GTS_MAX];
  //! IEEE 802.15.4-2006, 7.2.2.1.6 Pending Address Specification field
  MAC_PendingAddrSpec_t pendAddrSpec;
  //! Short addresses list pointer.
  ShortAddr_t           (*shortPendAddrList)[];
  //! Extended addresses list pointer.
  ExtAddr_t             (*extPendAddrList)[];
}  MAC_BeaconPldDescr_t;

//! Description of associate response command MAC payload.
typedef struct
{
  //! Allocated short address (in case of successfull association).
  ShortAddr_t  shortAddr;
  //! Result of association.
  uint8_t      status;
}  MAC_AssociateRespPldDescr_t;

//! Description of diassociate notification command MAC payload.
typedef struct
{
  //! Disassociation reason.
  MAC_DeassociateReason_t reason;
}  MAC_DisassociateNotifPldDescr_t;

//! Coordinator realignment command MAC payload. IEEE 802.15.4-2006, 7.3.8
typedef struct
{
  //! PAN identifier that the coordinator intends to use for all future communications.
  PanId_t     panId;
  //! The coordinator short address field shall contain the value of macShortAddress.
  ShortAddr_t coordShortAddr;
  //! The logical channel that the coordinator intends to use for all future communications.
  uint8_t     channel;
  //! Short address allocated for the device in case of orphan scan procedure, 0xffff otherwise.
  ShortAddr_t shortAddr;
  uint8_t     page;
}  MAC_CoordinatorRealignmentPldDescr_t;

//! Frame descriptor.
typedef struct
{
  //! Frame type.
  MAC_Frame_t        type;
  //! Frame control field,  IEEE 802.15.4-2006 Figure 42.
  MAC_FrameCtrl_t    frameControl;
  //! Data sequense number field.
  uint8_t            dsn;
  //! Frame's destination PAN identifire.
  PanId_t            dstPANId;

  //! Frame's destination address.
  MAC_Addr_t         dstAddr;
  //! Frame's source PAN identifire.
  PanId_t            srcPANId;
  //! Frame's source address.
  MAC_Addr_t         srcAddr;
  union
  {
    //! Beacon payload description.
    MAC_BeaconPldDescr_t                 beacon;
    //! Associate request command payload description.
    MAC_AssociateReqPldDescr_t           associateReq;
    //! Associate response command payload description.
    MAC_AssociateRespPldDescr_t          associateResp;
    //! Disassociate nofification command payload description.
    MAC_DisassociateNotifPldDescr_t      disassociateNotif;
    //! Coordinator realignment command payload description.
    MAC_CoordinatorRealignmentPldDescr_t coordRealig;
    //! GTS characteristics.
    MAC_GtsCharacteristics_t             gtsCharacteristics;
  } payload;
  //! MSDU pointer.
  uint8_t         *msdu;
  //! MSDU length.
  uint8_t         msduLength;
  //! Incoming frame's link quality.
  uint8_t         quality;
  //! Incoming frame's RSSI.
  int8_t          rssi;
}  MAC_FrameDescr_t;

#endif // _MACFRAME_H

// eof macFrame.h
