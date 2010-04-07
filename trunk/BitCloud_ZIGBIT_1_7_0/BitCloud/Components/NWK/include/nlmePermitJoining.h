/**************************************************************************//**
  \file  nlmePermitJoining.h

  \brief NLME-PERMIT-JOINING interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    12/04/2009  Max Gekk - Created.
 ******************************************************************************/
#if !defined _NLME_PERMIT_JOINING_H
#define _NLME_PERMIT_JOINING_H

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
 * \brief NLME-PERMIT-JOINING confirm primitive's parameters structure declaration.
 * ZigBee Specification r17, 3.2.2.6 NLME-PERMIT-JOINING.confirm, page 276.
 */
typedef struct _NWK_PermitJoiningConf_t
{
  /* The status of the corresponding request. Valid Range: NWK_SUCCESS_STATUS or
   * or any status returned from the MLME-SET.confirm primitive. */
  NWK_Status_t  status;
} NWK_PermitJoiningConf_t;

/**//**
 * \brief NLME-PERMIT-JOINING request primitive's parameters structure declaration.
 * Zigbee Specification r17, 3.2.2.5 NLME-PERMIT-JOINING.request, page 274.
 */
typedef struct _NWK_PermitJoiningReq_t
{
 /* Service fields - for internal needs. */
  struct
  {
    void  *next;
  } service;
  /* The length of time in seconds during which the ZigBee coordinator or router
   * will allow associations. The value 0x00 and 0xff indicate that permission is
   * disabled or enabled, respectively, without a specified time limit. */
  uint8_t    permitDuration;
  /* NLME-PERMIT-JOINING confirm callback function's pointer. */
  void       (*NWK_PermitJoiningConf)(NWK_PermitJoiningConf_t *conf);
  NWK_PermitJoiningConf_t confirm;
} NWK_PermitJoiningReq_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief NLME-PERMIT-JOINING request primitive's prototype.
  \param req - NLME-PERMIT-JOINING request parameters' structure pointer.
  \return none.
******************************************************************************/
void NWK_PermitJoiningReq(NWK_PermitJoiningReq_t *const req);

#endif  /* _NLME_PERMIT_JOINING_H */
/* eof nlmePermitJoining.h */

