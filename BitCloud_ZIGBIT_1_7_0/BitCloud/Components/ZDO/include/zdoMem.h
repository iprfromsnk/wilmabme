/************************************************************************//**
  \file zdoMem.h

  \brief The header file describes the internal ZDO memory

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _ZDOMEM_H
#define _ZDOMEM_H

#include <zdoNodeManager.h>
#include <zdoNwkManager.h>
#include <zdoPowerManager.h>
#include <zdoStateMachines.h>
#include <zdoZdpManager.h>
#include <zdoZdpFrameProcessor.h>
#include <zdoSecurityManager.h>
#include <zdo.h>
#ifdef _ZSE_SECURITY_
#include <zseSecurityManager.h>
#endif // _ZSE_SECURITY_

/* typedef union ZdoStackReq_t_ */ // workaround for kill NWK_JoinReq perfetch abort
typedef union ZdoStackReq_t_
{
  /* msg from ZDO to NLME */
#if defined(_COORDINATOR_)
  NWK_NetworkFormationReq_t nwkFormationReq;
#endif
#if defined(_ROUTER_) || defined(_ENDDEVICE_)
  NWK_NetworkDiscoveryReq_t nwkDiscoveryReq;
  NWK_JoinReq_t             nwkJoinReq;
#endif
#if defined(_COORDINATOR_) || defined(_ROUTER_)
  NWK_PermitJoiningReq_t    nwkPermitJoiningReq;
#endif
#if defined(_ROUTER_)
  NWK_StartRouterReq_t      nwkStartRouterReq;
#endif
  NWK_LeaveReq_t            nwkLeaveReq;

  /* msg from ZDO to APSME */
  APS_ResetReq_t            apsResetReq;
  APS_StartReq_t            apsStartReq;
  APS_StopReq_t             apsStopReq;

#ifdef _ZSE_SECURITY_
  ZSE_StartSecurityReq_t    zseStartSecurityReq;
#endif // _ZSE_SECURITY_

  RF_RandomReq_t            randReq;
} ZdoStackReq_t;

typedef struct ZdoMem_t_
{
  ZdoStackReq_t               stackReq;
  ZdoStateMachine_t           stateMachine;
  ZdoPowerManager_t           powerManager;
  ZdoNodeManager_t            nodeManager;
  ZdoNwkManager_t             nwkManager;
  ZdoZdpManager_t             zdoZdpManager;
  ZdoFrameProc_t              zdpFrameProcessor;
#ifdef _SECURITY_
  ZdoSecurityManager_t        zdoSecurityManager;
#endif
} ZdoMem_t;

extern ZdoMem_t zdoMem;

static inline ZdoStackReq_t * zdoMemStackRequest()
{
  return ((ZdoStackReq_t *)&zdoMem.stackReq);
}

static inline ZdoStateMachine_t * zdoMemStateMachine()
{
  return (&zdoMem.stateMachine);

}

static inline ZdoPowerManager_t * zdoMemPowerManager()
{
  return (&zdoMem.powerManager);

}

static inline ZdoNodeManager_t * zdoMemNodeManager()
{
  return (&zdoMem.nodeManager);
}

static inline ZdoNwkManager_t * zdoMemNwkManager()
{
  return (&zdoMem.nwkManager);
}

static inline ZdoZdpManager_t * zdoMemZdpManager()
{
  return (&zdoMem.zdoZdpManager);
}

static inline ZdoFrameProc_t * zdoMemZdpFrameProcessor()
{
  return (&zdoMem.zdpFrameProcessor);
}
#ifdef _SECURITY_
static inline ZdoSecurityManager_t * zdoMemSecurityManager()
{
  return (&zdoMem.zdoSecurityManager);
}
#endif
#endif /*ZDOMEM_H_*/
