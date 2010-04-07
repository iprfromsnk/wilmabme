/**************************************************************************//**
  \file  nlmeNetworkDiscovery.h

  \brief NLME-NETWORK-DISCOVERY interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    11/04/2009  Max Gekk - Created
 ******************************************************************************/
#if !defined _NLME_NETWORK_DISCOVERY_H
#define _NLME_NETWORK_DISCOVERY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <mac.h>
#include <nwkCommon.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/**//**
 * \brief  Network Descriptor Information Fields.
 * */
typedef struct _NWK_NetworkDescriptor_t
{
  /* The 64-bit PAN identifier of the network. */
  ExtPanId_t  extendedPANId;
  /* The current logical channel occupied by the network. */
  uint8_t     logicalChannel;
  /* A ZigBee stack profile identifier indicating the stack profile in use in
   * the discovered network. */
  unsigned    stackProfile  : 4;
  /* The version of the ZigBee protocol in use in the discovered network. */
  unsigned    zigBeeVersion : 4;
  /* This specifies how often the MAC sub-layer beacon is to be transmitted by 
   * a given device on the network. */
  unsigned    beaconOrder   : 4;
  /* For beacon-oriented networks, that is, beacon order < 15, this specifies
   * the length of the active period of the superframe. */
  unsigned    superframeOrder : 4;
  /* A value of '1' indicates that at least one ZigBee router on the network currently 
   * permits joining, i.e. its NWK has been issued an NLME-PERMIT-JOINING primitive and, 
   * the time limit if given, has not yet expired. */
  unsigned    permitJoining : 1;
  /* This value is set to '1' if the device s capable of accepting join requests
   * from router-capable devices and set to '0' otherwise. */
  unsigned    routerCapacity    : 1;
  /* This value is set to '1' if the device is capable of accepting join requests
   * from end devices and set to '0' otherwise. */
  unsigned    endDeviceCapacity : 1;
  unsigned    reserved  : 5;
} NWK_NetworkDescriptor_t;

/**//**
 * \brief NLME-NETWORK-DISCOVERY confirm primitive's parameters structure declaration.
 * ZigBee Specification r17, 3.2.2.2, NLME-NETWORK-DISCOVERY.confirm
 */
typedef struct _NWK_NetworkDiscoveryConf_t
{
  /* The status of the request. Any status values returned with MLME-SCAN.confirm 
   * primitive or NWK_INVALID_REQUEST_STATUS, NWK_SUCCESS_STATUS.  */
  NWK_Status_t  status;
  /* The number of networks discovered by the search.*/
  uint8_t  networkCount;
  /* Size of networkDescriptors array. It must be initialized by user. 
   * Zero value is admissible.*/
  uint8_t  maxNetworkDescr; 
  /* The array of descriptors, one for each of the networks discovered. It must be 
   * initialized by user. NULL pointer is admissible. */
  NWK_NetworkDescriptor_t       *networkDescriptors;
} NWK_NetworkDiscoveryConf_t;

/**//**
 * \brief NLME-NETWORK-DISCOVERY request primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.1 NLME-NETWORK-DISCOVERY.request.
 */
typedef struct _NWK_NetworkDiscoveryReq_t
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;
    MAC_ScanReq_t  macScan;
  } service;
  /* A value used to calculate the length of time to spend scanning each channel:*/
  uint8_t       scanDuration;
  /* The mask of channels that must be scanned. */
  uint32_t      scanChannels;
  /* NLME-NETWORK-DISCOVERY confirm callback function's pointer. */
  void (*NWK_NetworkDiscoveryConf)(NWK_NetworkDiscoveryConf_t *conf);
  NWK_NetworkDiscoveryConf_t confirm;
} NWK_NetworkDiscoveryReq_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief NLME-NETWORK-DISCOVERY request primitive's prototype.
  \param req - NLME-NETWORK-DISCOVERY request parameters' structure pointer.
  \return none.
 ******************************************************************************/
void NWK_NetworkDiscoveryReq(NWK_NetworkDiscoveryReq_t *const req);

#endif /* _NLME_NETWORK_DISCOVERY_H */
/* eof nlmeNetworkDiscovery.h */

