/************************************************************************//**
  \file zdoSecurityManager.h
  
  \brief The header file describes the constants, types and internal interface
  of ZDO security manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef ZDOSECURITYMANAGER_H_
#define ZDOSECURITYMANAGER_H_

#include <appTimer.h>
#include <zdo.h>

typedef enum
{
  ZDO_IDLE_SECURITY_STATE,
  ZDO_NORMAL_OPERATING_SECURITY_STATE,
  ZDO_WAITING_ESTABLISH_KEY_SECURITY_STATE,
  ZDO_WAITING_TRANSPORT_KEY_SECURITY_STATE,
  ZDO_WAITING_PARENT_AUTHENTICATION_SECURITY_STATE,
  ZDO_APP_KEY_ESTABLISH_RESPONDER_SECURITY_STATE,
  ZDO_APP_KEY_ESTABLISH_INITIATOR_SECURITY_STATE,
  ZDO_STARTING_NORMAL_OPERATING_SECURITY_STATE,
  ZDO_FAIL_CONFIRM_SECURITY_STATE,
  ZDO_CONFIRM_APP_KEY_SECURITY_STATE,
  ZDO_WAITING_APP_KEY_SECURITY_STATE,
} ZdoSecurityManagerState_t;

typedef struct
{
  ZdoSecurityManagerState_t state;
#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
  ZDO_EndToEndAppKeyReq_t   *appKeyReq;
#endif // _HIGH_SECURITY_  
#endif // _SECURITY_  
  
#ifdef _SECURITY_
  HAL_AppTimer_t             waitTimer;
  HAL_AppTimer_t             delayTimer;
  uint8_t                    newKeySeqNum;
#ifdef _HIGH_SECURITY_
  APS_EstablishKeyResp_t     apsEstablishKeyResp;
  union
  {
    APS_AuthenticateReq_t    apsAuthenticateReq;
    APS_EstablishKeyReq_t    apsEstablishKeyReq;
    APS_RequestKeyReq_t      apsRequestKeyReq;
  };
#endif // _HIGH_SECURITY_  
#endif // _SECURITY_  

} ZdoSecurityManager_t; 

void zdoResetSecurityManager();
void zdoAuthenticationStart(void);
void zdoAuthenticationConf(ZDO_Status_t status);
uint8_t zdoGetPreconfiredStatus(void);
void zdoAuthenticateChild(ExtAddr_t *childAddr);

#endif /*ZDOSECURITYMANAGER_H_*/
