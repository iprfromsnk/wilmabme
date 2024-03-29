/**************************************************************************//**
  \file  nlmeLeave.h

  \brief NLME-LEAVE interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13/04/2009  Max Gekk - Created.
 ******************************************************************************/
#if !defined _NLME_LEAVE_H
#define _NLME_LEAVE_H

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
 * \brief NLME-LEAVE confirm primitive's parameters structure declaration.
 * ZigBee Specification r17, 3.2.2.18 NLME-LEAVE.confirm, page 291.
 */
typedef struct _NWK_LeaveConf_t
{
  /* The status of the corresponding request.*/
  NWK_Status_t  status;
} NWK_LeaveConf_t;

/**//**
 * \brief NLME-LEAVE request primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.16 NLME-LEAVE.request, page 288.
 */
typedef struct _NWK_LeaveReq_t
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;
  }  service;
  /* The 64-bit IEEE address of the entity to be removed from the network or NULL
   * if the device removes itself from the network. */
  ExtAddr_t  deviceAddress;
  /* This parameter has a value of TRUE if the device being asked to leave the
   * network is also being asked to remove its child devices, if any. Otherwise, it
   * has a value of FALSE. */
  bool  removeChildren;
  /* This parameter has a value of TRUE if the device being asked to leave from
   * the current parent is requested to rejoin the network. Otherwise, the parameter
   * has a value of FALSE.*/
  bool  rejoin;
  /* NLME-LEAVE confirm callback function's pointer. */
  void (*NWK_LeaveConf)(NWK_LeaveConf_t *conf);
  NWK_LeaveConf_t confirm;
} NWK_LeaveReq_t;
 
/**//**
 * \brief NLME-LEAVE indication primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.17 NLME-LEAVE.indication, page 290.
 */
 typedef struct _NWK_LeaveInd_t
{
  /* The 64-bit IEEE address of an entity that has removed itself from the network 
   * or NULL in the case that the device issuing the primitive has been removed from 
   * the network by its parent. */
  ExtAddr_t  deviceAddress;
  /* This parameter has a value of TRUE if the device being asked to leave the
   * current parent is requested to rejoin the network. Otherwise, this parameter 
   * has a value of FALSE. */
  bool  rejoin;
} NWK_LeaveInd_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief NLME-LEAVE request primitive's prototype.
  \param req - NLME-LEAVE request parameters' structure pointer.
  \return none.
 ******************************************************************************/
void NWK_LeaveReq(NWK_LeaveReq_t *const req);

/**************************************************************************//**
  \brief NLME-LEAVE indication primitive's prototype.
  \param ind - NLME-LEAVE indication parameters' structure pointer.
  \return none.
 ******************************************************************************/
extern void NWK_LeaveInd(NWK_LeaveInd_t *ind);

#endif  /* _NLME_LEAVE_H */
/* eof nlmeLeave.h */

