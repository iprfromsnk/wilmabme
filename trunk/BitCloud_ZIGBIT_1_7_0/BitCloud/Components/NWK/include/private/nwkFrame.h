/**************************************************************************//**
  \file nwkFrame.h

  \brief Nwk frames header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    01/07/07 S. Vladykin - Created.
    12/06/09 M. Gekk     - Refactoring
 ******************************************************************************/
#if  !defined  _NWK_FRAME_H
#define _NWK_FRAME_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwk.h>
#include <types.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Values of the Frame Type Sub-Field. ZigBee spec r17, Table 3.37. */
typedef enum _NwkFrameTypeFlag_t
{
  NWK_FRAMETYPE_DATA  = 0,
  NWK_FRAMETYPE_COMMAND = 1
} NwkFrameTypeFlag_t;

/* Values of the Discover Route Sub-Field. ZigBee spec r17, Table 3.38. */
typedef enum _NwkDiscoverRouteFlag_t
{
  NWK_DISCOVER_ROUTE_SUPPRESS = 0,
  NWK_DISCOVER_ROUTE_ENABLE = 1,
} NwkDiscoverRouteFlag_t;

/* Values of the Multicast Mode Sub-Field. ZigBee spec r17, Table 3.39. */
typedef enum _NwkMulticastMode_t
{
  NWK_FRAME_MULTICAST_NON_MEMBER_MODE = 0,
  NWK_FRAME_MULTICAST_MEMBER_MODE = 1,
} NwkMulticastMode_t;

/* NWK command frame identifiers. ZigBee spec r17, Table 3.40. */
typedef enum _NwkCmdIdentifier_t 
{
  NWK_CMD_ROUTE_REQUEST   = 0x01, /* ZigBee spec r17, 3.4.1 */
  NWK_CMD_ROUTE_REPLY     = 0x02, /* ZigBee spec r17, 3.4.2 */
  NWK_CMD_NETWORK_STATUS  = 0x03, /* ZigBee spec r17, 3.4.3 */
  NWK_CMD_LEAVE           = 0x04, /* ZigBee spec r17, 3.4.4 */
  NWK_CMD_ROUTE_RECORD    = 0x05, /* ZigBee spec r17, 3.4.5 */
  NWK_CMD_REJOIN_REQUEST  = 0x06, /* ZigBee spec r17, 3.4.6 */
  NWK_CMD_REJOIN_RESPONSE = 0x07, /* ZigBee spec r17, 3.4.7 */
  NWK_CMD_LINK_STATUS     = 0x08, /* ZigBee spec r17, 3.4.8 */
  NWK_CMD_NETWORK_REPORT  = 0x09, /* ZigBee spec r17, 3.4.9 */
  NWK_CMD_NETWORK_UPDATE  = 0x0a, /* ZigBee spec r17, 3.4.10 */
} NwkCmdIdentifier_t;

/* Frame Control Field. ZigBee spec r17, 3.3.1.1, page 308. */
/* The frame control field is 16 bits in length and contains information defining 
 * the frame type, addressing and sequencing fields and other control flags.*/
BEGIN_PACK
typedef struct PACK _NwkFrameControl_t
{
  /* The frame type sub-field is 2 bits in length and shall be set to one of 
   * the nonreserved values: NWK_FRAMETYPE_DATA or NWK_FRAMETYPE_COMMAND. */
  uint16_t frameType       : 2;
  /* The protocol version sub-field shall be set to a number reflecting the ZigBee 
   * NWK protocol version in use. The protocol version in use on a particular device 
   * shall be made available as the value of the NWK constant nwkcProtocolVersion. */
  uint16_t protocolVersion : 4;
  /* The discover route sub-field may be used to control route discovery operations 
   * for the transit of this frame. */
  uint16_t discoverRoute   : 2;
  /* The multicast flag sub-field is 1 bit in length and has the value 0 if the frame 
   * is a unicast or broadcast frame and the value 1 if it is a multicast frame. 
   * The multicast control field of the NWK header shall be present only if the multicast 
   * flag has the value 1. ZigBee spec r17, 3.3.1.1.4, page 309. */
  uint16_t multicastFlag   : 1;
  /* The security sub-field shall have a value of 1 if, and only if, the frame is 
   * to have NWK security operations enabled. If security for this frame is implemented 
   * at another layer or disabled entirely, it shall have a value of 0. */
  uint16_t security        : 1;
  /* The source route sub-field shall have a value of 1 if and only if a source route
   * subframe is present in the NWK header. ZigBee spec r17, 3.3.1.1.6, page 308. */
  uint16_t sourceRoute     : 1;
  /* The destination IEEE address sub-field shall have a value of 1 if, and only if, 
   * the NWK header is to include the full IEEE address of the destination. */
  uint16_t dstExtAddr      : 1;
  /* The source IEEE address sub-field shall have a value of 1 if, and only if, the NWK
   * header is to include the full IEEE address of the source device. */
  uint16_t srcExtAddr      : 1;
  uint16_t reserved        : 3;
} NwkFrameControl_t;
END_PACK

/* Type of unaligned extended IEEE address. */
BEGIN_PACK
typedef union PACK _NwkFrameExtAddr_t
{
  ExtAddr_t value;
  uint8_t   raw[sizeof(ExtAddr_t)];
} NwkFrameExtAddr_t;
END_PACK

/* The multicast control sub-field is 1 octet in length and shall only be present 
 * if the multicast flag sub-field has a value of 1. It is divided into three sub-fields 
 * as illustrated in ZigBee spec r17, Figure 3.7. */
BEGIN_PACK
typedef struct PACK _NwkFrameMulticastField_t
{
  /* The multicast mode sub-field indicates whether the frame is to be transmitted
   * using member or non-member mode. Member mode is used to propagate multicasts 
   * between the devices that are members of the destination group. Nonmember mode 
   * is used to transmit a multicast frame from a device that is not a member of 
   * the multicast group to a device that is a member of the multicast group. */
  uint8_t multicastMode      : 2;
  /* The nonmemberradius sub-field indicates the range of a member mode multicast
   * when relayed by devices that are not members of the destination group. */
  uint8_t nonMemberRadius    : 3;
  /* The maximum value of the NonmemberRadius sub-field for this frame.
   * ZigBee spec r17, 3.3.1.8.3, page 312. */
  uint8_t maxNonMemberRadius : 3;
} NwkFrameMulticastField_t;
END_PACK

/* Source route subframe field. ZigBee spec r17, 3.3.1.9, page 312. */
BEGIN_PACK
typedef struct PACK _NwkSourceRouteSubframe_t
{
  /* The relay count sub-field indicates the number of relays contained in the relay 
   * list sub-field of the source route subframe. */
  uint8_t     relayCount;
  /* The relay index sub-field indicates the index of the next relay in the relay list 
   * subfield to which the packet will be transmitted. This field is initialized to 1 
   * less than the relay count by the originator of the packet, and is decremented by 1 
   * by each receiving relay. ZigBee spec r17, 3.3.1.9.2, page 312. */
  uint8_t     relayIndex;
  /* The relay list sub-field shall contain the list of relay addresses. The relay closest 
   * to the destination shall be listed first. The relay closest to the originator shall be
   * listed last. ZigBee spec r17, 3.3.1.9.3, page 312. */
  ShortAddr_t relayList[1];
} NwkSourceRouteSubframe_t;
END_PACK

/* Type of parsed NWK header. */
typedef struct _NwkParseHeader_t
{
  /* Pointer to a destination extended address in a original NWK header. */
  NwkFrameExtAddr_t  *dstExt;
  /* Pointer to a source extended address in a original NWK header. */
  NwkFrameExtAddr_t  *srcExt;
  /* Pointer to a multicast field. */
  NwkFrameMulticastField_t  *multicast;
  /* Pointer to a source route subframe. */
  NwkSourceRouteSubframe_t  *sourceRouteSubframe;
  /* Pointer to first octet of NWK payload. */
  uint8_t  *payload;
  /* Size of NWK header in octets. */
  uint8_t  headerSize;
  /* Size of NWK payload in octets. */
  uint8_t  payloadSize;
  /* Source MAC short address. */
  ShortAddr_t  macSrcAddr;
  /* Link quality indicator of received frame. */
  uint8_t  lqi;
  /* Received signal strength indication. */
  int8_t  rssi;
} NwkParseHeader_t;

/* Type of a NWK header, which comprises frame control, addressing 
 * and sequencing information. */
BEGIN_PACK
typedef struct PACK _NwkFrameHeader_t
{
  /* The frame control field shall be formatted as illustrated in 
   * ZigBee spec r17, Figure 3.6. */
  NwkFrameControl_t  frameControl;
  /* The destination address field shall always be present and shall be 2 octets in
   * length. If the multicast flag sub-field of the frame control field has the value 0, 
   * the destination address field shall hold the 16-bit network address of the destination
   * device or a broadcast address (see Table 3.54). If the multicast flag sub-field has
   * the value 1, the destination address field shall hold the 16-bit Group ID of the
   * destination multicast group. ZigBee spec r17, 3.3.1.2, page 310. */
  ShortAddr_t  dstAddr;
  /* The source address field shall always be present. It shall always be 2 octets in
   * length and shall hold the network address of the source device of the frame.
   * ZigBee spec r17, 3.3.1.3, page 310. */
  ShortAddr_t  srcAddr;
  /* The radius field shall always be present. It will be 1 octet in length and specifies
   * the range of a radius-limited transmission. The field shall be decremented by 1 by
   * each receiving device. ZigBee spec r17, 3.3.1.4, page 310. */
  uint8_t  radius;
  /* The sequence number field is present in every frame and is 1 octet in length. The
   * sequence number value shall be incremented by 1 with each new frame transmitted */
  uint8_t  sequenceNumber;
  union PACK 
  {
    struct PACK
    {
      /* The destination IEEE address field, if present, contains the 64-bit IEEE address
      * corresponding to the 16-bit network address contained in the destination address
      * field of the NWK header. ZigBee spec r17, 3.3.1.6, page 310. */
      NwkFrameExtAddr_t  dstExt;
      /* The source IEEE address field, if present, contains the 64-bit IEEE address
       * corresponding to the 16-bit network address contained in the source address field. */
      NwkFrameExtAddr_t  srcExt;
      uint8_t  payload[1];
    } dst_src;
    struct PACK
    {
      NwkFrameExtAddr_t  srcExt;
      uint8_t  payload[1];
    } src;
    struct PACK
    {
      /* The multicast control sub-field is 1 octet in length and shall only be present 
       * if the multicast flag sub-field has a value of 1. It is divided into three sub-fields 
       * as illustrated in ZigBee spec r17, Figure 3.7. */
      NwkFrameMulticastField_t  multicast;
      uint8_t  payload[1];
    } multicast;
    struct PACK
    {
      NwkFrameExtAddr_t  dstExt;
      NwkFrameExtAddr_t  srcExt;
      NwkFrameMulticastField_t  multicast;
      uint8_t  payload[1];
    } dst_src_multicast;
    /* First octet of NWK payload. */
    uint8_t  payload[1];
  };
}  NwkFrameHeader_t;
END_PACK

/* The beacon payload shall contain the information shown in ZigBee spec r17, Table 3.56.*/
/* This enables the NWK layer to provide additional information to new devices that are
 * performing network discovery and allows these new devices to more efficiently select 
 * a network and a particular neighbor to join. */
BEGIN_PACK
typedef  struct PACK _NwkBeaconPayload_t
{
  /* This field identifies the network layer protocols in use and, for purposes of 
   * this specification, shall always be set to 0, indicating the ZigBee protocols. */
  uint8_t  protocolId;
  struct PACK 
  {
    /* A ZigBee stack profile identifier. */
    uint8_t  stackProfile       :4;
    /* The version of the ZigBee protocol. */
    uint8_t  nwkProtocolVersion :4;
    uint8_t  reserved           :2;
    /* This value is set to 1 if this device is capable of accepting join requests 
     * from routercapable devices and is set to 0 otherwise. */
    uint8_t  routerCapacity     :1;
    /* The network depth of this device. A value of 0x00 indicates that this device 
     * is the ZigBee coordinator for the network. */
    uint8_t  deviceDepth        :4;
    /* This value is set to 1 if the device is capable of accepting join requests from 
     * end devices seeking to join the network and is set to 0 otherwise. */
    uint8_t  endDeviceCapacity  :1;
  };
  /* The globally unique ID for the PAN of which the beaconing device is a member. */
  uint64_t  nwkExtendedPanid;
  /* This value indicates the difference in time, measured in symbols, between the beacon
   * transmission time of the device and the beacon transmission time of its parent. */
  uint8_t  txOffset[3];
  /* This field reflects the value of nwkUpdateId from the NIB. */
  uint8_t  updateId;
}  NwkBeaconPayload_t;
END_PACK

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief Clear frame, then fill it with commonly used fields.
  \param nwkHeader - pointer to header.
 ******************************************************************************/
void nwkPrepareCommonFrame(NwkFrameHeader_t *const nwkHeader);

/******************************************************************************
  \brief Parse floating fields of frame.
  \param nwkHeader - header to parse.
  \param parse - structure with pointer to frame fields, NULL - if field is not present, 
     correct pointer otherwise.
 ******************************************************************************/
void nwkParseHeader(const NwkFrameHeader_t *const nwkHeader, NwkParseHeader_t *const parse);

#endif  /* _NWK_FRAME_H */
/* eof nwkFrame.h */
