/**************************************************************************//**
  \file  nwkPacket.h

  \brief Interface of the network packet manager.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    06/07/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_PACKET_H
#define  _NWK_PACKET_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include  <nwk.h>
#include  <nwkSystem.h>
#include  <nwkRx.h>
#include  <nwkTx.h>
#if defined _SECURITY_
#include  <sspSfp.h>
#endif /* _SECURITY_ */

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Type of network packet. */
typedef enum _NwkPacketType_t
{
  NWK_UNKNOWN_PACKET = 0x0,
  /* Command packet from NWK component. */
  NWK_OUTPUT_COMMAND_PACKET = 0x1,
  /* Command packet from MAC-layer. */
  NWK_INPUT_COMMAND_PACKET = 0x2,
  /* Data packet from MAC-layer. */
  NWK_INPUT_DATA_PACKET = 0x3,
  /* Transit packet from MAC-layer. */
  NWK_TRANSIT_PACKET = 0x4,
  NWK_BUFFER_TYPE_LAST
}  NwkPacketType_t;

/* Network packet type. */
typedef struct _NwkPacket_t
{
  /* Network packet type. */
  NwkPacketType_t  type;
#if defined _SECURITY_
  uint8_t  macHeader[MAC_MAX_DATA_FRAME_HEADER_LENGTH + NWK_SECURITY_HEADER_SIZE];
#else
  uint8_t  macHeader[MAC_MAX_DATA_FRAME_HEADER_LENGTH];
#endif
  uint8_t  macPayload[MAC_MAX_MSDU_SIZE];
  union
  {
    NwkInputPacket_t  inPkt;
    NwkOutputPacket_t  outPkt;
  };
}  NwkPacket_t;

/* Internal variables of the network packet manager. */
typedef struct _NwkPacketManager_t
{
  /* Array of network packets. */
  NwkPacket_t  *pkt;
  /* Total amount of network packets. */
  uint8_t  amount;
  /* Queue of command requests. */
  QueueDescriptor_t  commandQueue;
}  NwkPacketManager_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Allocate a free memory space for an input packet with type.
  \param type - type of packet.
  \return Pointer to input packet or NULL.
 ******************************************************************************/
NwkInputPacket_t*  nwkAllocInputPacket(const NwkPacketType_t type);

/**************************************************************************//**
  \brief Free an input packet.
  \param inPkt - pointer to an input packet.
 ******************************************************************************/
void  nwkFreeInputPacket(NwkInputPacket_t *const inPkt);

/**************************************************************************//**
  \brief Allocate a free memory space for an output.
  \param type - type of output packet.
  \return Pointer to output packet or NULL.
 ******************************************************************************/
NwkOutputPacket_t*  nwkAllocOutputPacket(const NwkPacketType_t type);

/**************************************************************************//**
  \brief Free an output packet.
  \param outPkt - pointer to an output packet.
 ******************************************************************************/
void  nwkFreeOutputPacket(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief The packet has been released.
 ******************************************************************************/
void  nwkFreePacketInd(void);

/**************************************************************************//**
  \brief To transform an input packet to the output packet.
 ******************************************************************************/
NwkOutputPacket_t*  nwkTransformInToOutPacket(NwkInputPacket_t *inPkt);

/**************************************************************************//**
  \brief Reset the network packet manager.
 ******************************************************************************/
void  nwkResetPacketManager(void);

#endif /* _NWK_PACKET_H */ 
/* eof nwkPacket.h */ 
