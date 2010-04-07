/**************************************************************************//**
  \file nwkIB.h

  \brief Network information base.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    01/05/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined  _NWK_IB_H
#define  _NWK_IB_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include  <types.h>
#include  <configServer.h>
#include  <mac.h>
#include  <nwk.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
typedef struct _NIB_t
{
  /* The type of the device:
   *   - 0x00 - zigbee coordinator
   *   - 0x01 - zigbee router
   *   - 0x02 - zigbee end device */
  uint8_t  deviceType   :2;
  /* A value that determines the method used to assign addresses:
   *  - 0x00 = use distributed address allocation
   *  - 0x01 = reserved
   *  - 0x02 = use stochastic address allocation. */
  uint8_t  addrAlloc    :2;
  /* The current route symmetry setting. 1 means that routes are considered to be
   * comprised of symmetric links. Backward and forward routes are created during one-route
   * discovery and they are identical. 0 indicates that routes are not consider to
   * be comprised of symmetric links. Only the forward route is stored during route discovery.*/
  uint8_t  symLink      :1;
  /* Determines whether or not the static addressing mode will be used.
   * If set to '0' then the device must use a static network address
   * otherwise, the stochastic addressing mode will be employed. */
  uint8_t  uniqueAddr   :1;
  uint8_t  reserved     :2;
  /* The identifier of the ZigBee stack profile in use for this device. */
  uint8_t  stackProfile     :4;
  /* The version of the ZigBee NWK protocol in the device. */
  uint8_t  protocolVersion  :4;
  /* The tree depth of the neighbor device. A value of 0x00 indicates that
   * the device is the ZigBee coordinator for the network. */
  uint8_t  depth            :4;
  /* The depth a device can have. */
  uint8_t  maxDepth         :4;
  /* A sequence number used to identify outgoing frames */
  uint8_t  sequenceNumber;
  /* RF channel page */
  uint8_t  channelPage;
  /* Number of RF channel */
  uint8_t  logicalChannel;
  /* The 16-bit address that the device uses to communicate with the PAN. */
  ShortAddr_t  networkAddress;
  /* The short (16-bit) pan identificator of a zigbee network. */
  PanId_t  panId;
  /* 64-bit IEEE address that is unique to every device. */
  ExtAddr_t  extendedAddress;
  /* The Extended PAN Identifier for the PAN of which the device is a member.
   * The value 0x0000000000000000 means the Extended PAN Identifier is unknown. */
  ExtPanId_t  extendedPanId;
  /* A network address of parent node. */
  ShortAddr_t  parentNetworkAddress;
  /* The address of the designated network channel manager function. */
  ShortAddr_t  managerAddr;
  /* The number of routers any one device is allowed to have as children. */
  uint8_t  maxRouters;
  /* The number of end devices any one device is allowed to have as children. */
  uint8_t  maxEndDevices;
  /* The total delivery time for a broadcast transmission, i.e. the time required for a
   * broadcast to be delivered to every device in the network. */
  uint8_t  networkBroadcastDeliveryTime;
  /* Duration in ms of maximum length frame transferring. */
  uint8_t  maxFrameTransmissionTime;
  /* This field shall contain the device capability information established at
   * network joining time. */
  MAC_CapabilityInf_t  capabilityInformation;
  /* The value identifying a snapshot of the network settings with which this
   * node is operating with. */
  uint8_t  updateId;
  uint16_t  cSkipChildren;
  uint16_t  cSkipSibling;
  /**/
  struct {
    /* This field is used by MAC layer. */
    uint8_t  macBeaconPayloadHeader[MAC_MAX_BEACON_HEADER_LENGTH];
    /* The beacon payload contain the information which enables the NWK layer to provide
     * additional information to new devices that are performing network discovery
     * and allows these new devices to more efficiently select a network and
     * a particular neighbor to join. */
    NwkBeaconPayload_t  beaconPayload;
  };
#ifdef _SECURITY_
  /* Pointer to the security information base. */
  NWK_SecurityIB_t    *securityIB;
#endif
} NIB_t;

/******************************************************************************
                           Definitions section
 ******************************************************************************/
/* Maximum time of frame transmission in ms. */
#define  NWK_MAX_FRAME_TRANSMISSION_TIME  (nwkMemNib()->maxFrameTransmissionTime)

/******************************************************************************
                            Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the network information base
 ******************************************************************************/
void nwkResetNib(const bool powerFailure);

/**************************************************************************//**
  \brief Update beacon payload depending on nib values
 ******************************************************************************/
void nwkUpdateBeaconPayload(void);

/**************************************************************************//**
  \brief Set depth in NIB and update cSkips
 ******************************************************************************/
void nwkSetDepth(uint8_t depth);

/**************************************************************************//**
  \brief Reload parameters from config server.
 ******************************************************************************/
void nwkReloadNibFromConfigServer(void);

/**************************************************************************//**
  \brief Set a network address of parent device
 ******************************************************************************/
void nwkSetParentShortAddr(ShortAddr_t addr);

#endif  /* _NWK_IB_H */
/*  eof nwkIB.h */
