/**************************************************************************//**
  \file  nldeData.h

  \brief NLDE-DATA interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13/04/2009  Max Gekk - Created.
 ******************************************************************************/
#if !defined _NLDE_DATA_H
#define _NLDE_DATA_H

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
 * \brief NLDE-DATA confirm primitive's parameters structure declaration.
 * ZigBee Specification r17, 3.2.2.2 NLDE-DATA.confirm, page 264.
 */
typedef struct _NWK_DataConf_t 
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;
  } service;
  /* The status of the corresponding request. */
  NWK_Status_t  status;
  /* The handle associated with the NSDU being confirmed. */
  uint8_t  nsduHandle;
  /* A time indication for the transmitted packet based on the local clock. */
  uint32_t  txTime;
} NWK_DataConf_t;

/**//**
 * \brief NLDE-DATA request primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.1 NLDE-DATA.request, page 261.
 */
typedef struct _NWK_DataReq_t
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;  /* pointer used for queuing */
    uint8_t  headerLength;
  } service;
  /* The type of destination address supplied by the DstAddr parameter. */
  NWK_DstAddrMode_t  dstAddrMode;
  /* Destination address. */
  uint16_t  dstAddr;
  /* The number of octets comprising the NSDU to be transferred. */
  uint8_t  nsduLength;
  /* The set of octets comprising the NSDU to be transferred. */
  uint8_t  *nsdu;
  /* The handle associated with the NSDU to be transmitted by the NWK layer entity. */
  uint8_t  nsduHandle;
  /* The distance, in hops, that a frame will be allowed to travel through the network. */
  uint8_t  radius;
  /* The distance, in hops, that a multicast frame will be relayed by nodes not a
   * member of the group. A value of 0x07 is treated as infinity.*/
  uint8_t  nonmemberRadius;
  /* The DiscoverRoute parameter may be used to control route discovery operations for 
   * the transit of this frame: false = suppress route discovery, true = enable route discovery */
  bool  discoverRoute;
  /* encrypt packet */
  bool  securityEnable;
  /* NLDE-DATA confirm callback function's pointer. */
  void  (*NWK_DataConf)(NWK_DataConf_t *conf);
  NWK_DataConf_t     confirm;
} NWK_DataReq_t;

/* Nonstandard NLDE-DATA.response */
typedef struct _NWK_DataResp_t 
{
  uint8_t status;
} NWK_DataResp_t;

/**//**
 * \brief NLDE-DATA indication primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.3 NLDE-DATA.indication, page 266.
 */
typedef struct _NWK_DataInd_t 
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;  /* pointer used for queuing */
  } service;
  /* The type of destination address supplied by the DstAddr parameter. 
   * This may have one of the following  two values:
   * - 0x01 = 16-bit multicast group address,
   * - 0x02 = 16-bit network address of a  device or a 16-bit broadcast address. */
  NWK_DstAddrMode_t  dstAddrMode;
  /* The destination address to which the NSDU was sent. */
  uint16_t  dstAddr;
  /* The individual device address from which the NSDU originated. */
  ShortAddr_t  srcAddr;
  /* The number of octets comprising the NSDU being indicated. */
  uint8_t  nsduLength;
  /* The set of octets comprising the NSDU being indicated. */
  uint8_t  *nsdu;
  /* The link quality indication delivered by the MAC on receipt of this frame 
   * as a parameter of the MCPS-DATA.indication primitive. */
  uint8_t  linkQuality;
  /* RSSI delivered by the MAC on receipt of this frame as a parameter of 
   * the MCPS-DATA.indication primitive.*/
  int8_t  rssi;
  /* A time indication for the received packet based on the local clock. */
  uint32_t  rxTime;
  /* An indication of whether the received data frame is using security. */
  bool  securityUse;
  /* NLDE-DATA response callback function's pointer. */
  void  (*NWK_DataResp)(NWK_DataResp_t *resp);
  NWK_DataResp_t        response;
} NWK_DataInd_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief NLDE-DATA request primitive's prototype.
  \param req - NLDE-DATA request parameters' structure pointer.
  \return none.
 ******************************************************************************/
void NWK_DataReq(NWK_DataReq_t *const req);

/**************************************************************************//**
  \brief NLDE-DATA indication primitive's prototype.
  \param ind - NLDE-DATA indication parameters' structure pointer.
  \return none.
 ******************************************************************************/
extern  void NWK_DataInd(NWK_DataInd_t *ind);

#endif  /* _NLDE_DATA_H */
/* eof nldeData.h */

