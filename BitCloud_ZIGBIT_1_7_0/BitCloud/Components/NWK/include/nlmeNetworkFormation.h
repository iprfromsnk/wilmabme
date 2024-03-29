/**************************************************************************//**
  \file  nlmeNetworkFormation.h

  \brief NLME-NETWORK-FORMATION interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    11/04/2009  Max Gekk - Created.
 ******************************************************************************/
#if !defined _NLME_NETWORK_FORMATION_H
#define _NLME_NETWORK_FORMATION_H

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
 * \brief NLME-NETWORK-FORMATION confirm primitive's parameters structure declaration.
 * ZigBee Specification r17, 3.2.2.3, NLME-NETWORK-FORMATION.confirm
 */
typedef struct _NWK_NetworkFormationConf_t
{
  /* The status of the request. */
  NWK_Status_t  status;
} NWK_NetworkFormationConf_t;

/**//**
 * \brief NLME-NETWORK-FORMATION request primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.3 NLME-NETWORK-FORMATION.request.
 */
typedef struct _NWK_NetworkFormationReq_t
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;
    union
    {
      struct {
        MAC_ScanReq_t       macScan;
        PHY_EnergyLevel_t   energyList[MAX_EDSCAN_CHANNEL_AMOUNT];
      };
      MAC_SetReq_t        macSet;
      MAC_StartReq_t      macStart;
      MAC_RxEnableReq_t   macRxEnable;
    };
  } service;
  /* Channels are to be scanned in preparation for starting a network. */
  uint32_t    scanChannels;
  /* The time spent scanning each channel is (aBaseSuperframeDuration * (2n + 1))
   * symbols, where n is the value of the ScanDuration parameter. */
  uint8_t     scanDuration;
  /* The beacon order of the network that the higher layers wish to form. */
  //uint8_t     beaconOrder;
  /* The superframe order of the network that the higher layers wish to form. */
  //uint8_t     superFrameOrder;
  /* Support battery life extension mode. This parameter is ignored if the
   * BeaconOrder parameter has a value of 15. */
  //bool        batteryLifeExtention;
  /* NLME-NETWORK-FORMATION confirm callback function's pointer. */
  void  (*NWK_NetworkFormationConf)(NWK_NetworkFormationConf_t *conf);
  NWK_NetworkFormationConf_t  confirm;
} NWK_NetworkFormationReq_t;

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief NLME-NETWORK-FORMATION request primitive's prototype.
  \param req - NLME-NETWORK-FORMATION request parameters' structure pointer.
  \return none.
 ******************************************************************************/
void NWK_NetworkFormationReq(NWK_NetworkFormationReq_t *const req);

#endif  /* _NLME_NETWORK_FORMATION_H */
/* eof nlmeNetworkFormation.h */

