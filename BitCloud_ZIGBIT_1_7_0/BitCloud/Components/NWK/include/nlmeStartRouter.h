/**************************************************************************//**
  \file  nlmeStartRouter.h

  \brief NLME-START-ROUTER interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    11/04/2009  Max Gekk - Created.
 ******************************************************************************/
#if !defined _NLME_START_ROUTER_H
#define _NLME_START_ROUTER_H

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
 * \brief NLME-START-ROUTER confirm primitive's parameters structure declaration.
 * ZigBee Specification r17, 3.2.2.7 NLME-START-ROUTER.confirm
 */
typedef struct _NWK_StartRouterConf_t
{
  /* The result of the attempt to initialize a ZigBee router. 
   * Valid range: NWK_INVALID_REQUEST_STATUS or any status value returned from 
   * the MAC_StartConf callback.*/
  NWK_Status_t status;
} NWK_StartRouterConf_t;

/**//**
 * \brief NLME-START-ROUTER request primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.8 NLME-START-ROUTER.request.
 */
typedef struct _NWK_StartRouterReq_t
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;
    MAC_StartReq_t  macStart;  
  } service;
  /* The beacon order of the network that the higher layers wish to form. */
  //uint8_t   beaconOrder;
  /* The superframe order of the network that the higher layers wish to form. */
  //uint8_t   superFrameOrder;
  /* Supporting battery life extension mode. This parameter is ignored if the
   * BeaconOrder parameter has a value of 15. */
  //bool      batteryLifeExtention;
  /* NLME-START-ROUTER confirm callback function's pointer. */
  void  (*NWK_StartRouterConf)(NWK_StartRouterConf_t *conf);
  /* NLME-START-ROUTER confirm primitive's parameters */
  NWK_StartRouterConf_t   confirm;
} NWK_StartRouterReq_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief NLME-START-ROUTER request primitive's prototype.
  \param req - NLME-START-ROUTER request parameters' structure pointer.
  \return none.
 ******************************************************************************/
void NWK_StartRouterReq(NWK_StartRouterReq_t *const req);

#endif  /* _NLME_START_ROUTER_H */
/* eof nlmeStartRouter.h */

