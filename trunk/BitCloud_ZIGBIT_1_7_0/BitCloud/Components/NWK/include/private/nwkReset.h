/**************************************************************************//**
  \file  nwkReset.h

  \brief NWK reset header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:     
    20/06/07 V. Panov - Created.
    07/03/09 M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_RESET_H
#define _NWK_RESET_H
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwk.h>
#include <queue.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
/* List of reset handlers. */
#define  NWK_RESET_FUNCTIONS \
{                            \
  nwkResetDataReq,           \
  nwkResetDataConf,          \
  nwkResetPacketManager,     \
  nwkResetJoinReq,           \
  nwkResetFormation,         \
  nwkResetDiscovery,         \
  nwkResetStartRouter,       \
  nwkResetSyncLoss,          \
  nwkResetBTT,               \
  nwkResetLeave,             \
  nwkResetSync,              \
  nwkResetAge,               \
  nwkResetAddressMap,        \
  nwkResetRouteDiscovery,    \
  nwkResetLinkStatus,        \
  nwkResetPermitJoining,     \
  nwkResetJoinInd,           \
  nwkResetEDScan,            \
  nwkResetUpdateCommand,     \
  nwkResetReportCommand,     \
  nwkResetNetworkManager,    \
  nwkResetStatusSender,      \
  nwkResetStatusReceiver,    \
  nwkResetAddrConflict,      \
  nwkResetCommands,          \
  nwkResetConcentrator       \
}

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Internal states of the NLME-RESET component. */
typedef enum _NwkResetState_t
{
  NWK_RESET_IDLE_STATE = 0x19,
  NWK_RESET_FIRST_STATE = 0xC1,
  NWK_RESET_BEGIN_STATE = NWK_RESET_FIRST_STATE,
  NWK_RESET_CONFIRM_STATE = 0xC2,
  NWK_RESET_MAC_STATE = 0xC3,
  NWK_RESET_RX_ENABLE_STATE = 0xC4,
  NWK_RESET_SET_SHORT_ADDRESS_STATE = 0xC5,
  NWK_RESET_SET_COORD_SHORT_ADDR_STATE = 0xC6,
  NWK_RESET_SET_PANID_STATE = 0xC7,
  NWK_RESET_SET_COORD_EXT_ADDR_STATE = 0xC8,
  NWK_RESET_SET_ASSOC_PAN_COORD_STATE = 0xC9,
  NWK_RESET_SET_CHANNEL_STATE = 0xCA,
  NWK_RESET_SET_RX_ON_WHEN_IDLE_STATE = 0xCB,
  NWK_RESET_SET_BEACON_PAYLOAD_STATE = 0xCC,
  NWK_RESET_SET_BEACON_PAYLOAD_LEN_STATE = 0xCD,
  NWK_RESET_SET_ASSOC_PERMIT_STATE = 0xCE,
  NWK_RESET_MAC_START_STATE = 0xCF,
  NWK_RESET_LAST_STATE
} NwkResetState_t;

/* Internal parameters of NLME-RESET component. */
typedef struct _NwkReset_t
{
  /* finite-state machine */
  NwkResetState_t  state;
  /* Queue of requests from upper layer */
  QueueDescriptor_t  queue;
  union 
  {
    MAC_ResetReq_t  macReset;
    MAC_SetReq_t  macSet;
    MAC_RxEnableReq_t  macRxEnable;
    MAC_StartReq_t  macStart;
  };
} NwkReset_t;

/* Type of reset function. */
typedef void  (* nwkResetFunction_t)(void);

/******************************************************************************
                            Prototypes section
 *****************************************************************************/
/**************************************************************************//**
  \brief Task handler of reset component.
 *****************************************************************************/
void nwkResetTaskHandler(void);

#endif /* _NWK_RESET_H */
/* eof nwkReset.h */
