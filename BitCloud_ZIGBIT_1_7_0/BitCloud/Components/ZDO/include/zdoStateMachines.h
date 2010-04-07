/************************************************************************//**
  \file zdoStateMachines.h

  \brief The header file describes the constants, types and internal interface
  of ZDO state machine component

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    27.07.09 A. Taradov - Refactoring
******************************************************************************/

#ifndef _ZDO_STATEMACHINE_H_
#define _ZDO_STATEMACHINE_H_

#include <nwk.h>
#include <aps.h>
#include <zdo.h>
#include <appTimer.h>

#define MAX_DISCOVERED_NETWORKS_NUMBER 3

/******************************************************************************
* Type Definitions
******************************************************************************/

/* Possible states which the ZDO state machine can stay for */
typedef enum
{
  ZDO_INITIAL_STATE,
  ZDO_RANDOM_CONF_STATE,
  ZDO_READY_STATE,
  ZDO_START_NETWORK_STATE,
  ZDO_START_APS_STATE,
  ZDO_APS_STARTED_STATE,
  ZDO_APS_RESET_CONF_STATE,
  ZDO_JOIN_NETWORK_STATE,
  ZDO_NETWORK_DISCOVERY_STATE,
  ZDO_JOINED_STATE,
  ZDO_PERMIT_JOIN_STATE,
  ZDO_START_ROUTER_STATE,
  ZDO_CONFIRM_STATE,
  ZDO_RUNNING_STATE,
  ZDO_LEAVE_STATE,
  ZDO_LEAVING_STATE,
  ZDO_REJOIN_STATE,
  ZDO_RESETTING_STATE
} ZdoStateMachineState_t;

/* STARTUP ATTRIBUTES SET                                           */

/* startUp control attribute */
typedef enum {
/* Indicates that the device should start "from scratch"
   and join the network using association.                          */
    SEARCH_NET       = 0,
/* Indicates that the device should rejoin the network with
   extended PAN ID given by the ExtendedPANId attribute.            */
    REJOIN_NET       = 1,
} NetworkStartType_t;

/* criteria bit mask for Network Choose */
#define CHOOSENET_EXTPANID          ( 1<<0 )
#define CHOOSENET_STACKPROFILE      ( 1<<1 )
#define CHOOSENET_ZBVERSION         ( 1<<2 )
#define CHOOSENET_CT_EPID           ( 1<<7 )

/*
 * State machine variables
 * */
typedef struct ZdoStateMachine_t_
{
  // states for State Machine
  ZdoStateMachineState_t  zdoState;
  // start network type: first start or rejoin
  NetworkStartType_t      networkStartType;
#if defined(_ROUTER_) || defined(_ENDDEVICE_)
  // network discovery variables
  NWK_NetworkDescriptor_t networkList[MAX_DISCOVERED_NETWORKS_NUMBER];
  // selected network descriptor
  NWK_NetworkDescriptor_t *networkDescriptor;
  // scanning/joining attempts counter
  uint8_t                 attempts;
  // timers
  HAL_AppTimer_t          timer;
#endif
  // ZDO_StartNetworkReq    ptr
  ZDO_StartNetworkReq_t   *startNetworkReqParams;
  // ZDO_ResetNetworkReq    ptr
  ZDO_ResetNetworkReq_t   *resetNetworkReqParams;
  //
  bool                    powerFailure;
  // Last status
  ZDO_Status_t            status;
} ZdoStateMachine_t;

void zdoStateMachineLeave(bool rejoin);
void zdoDeviceAnnceConf(ZDO_Status_t status);

#endif /*_ZDO_STATEMACHINE_H_*/
