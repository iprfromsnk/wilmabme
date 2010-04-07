/**************************************************************************//**
  \file  nwkMem.h

  \brief NWK Memory header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 S. Vladykin - Created.
    30/04/09 M. Gekk     - Refactoring
 ******************************************************************************/
#if !defined _NWK_MEM_H
#define _NWK_MEM_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include  <nwk.h>

#include  <nwkTaskManager.h>
#include  <nwkFrame.h>
#include  <nwkAge.h>
#include  <nwkCommands.h>
#include  <nwkIB.h>
#include  <nwkReset.h>
#include  <nwkGroup.h>
#include  <nwkBTT.h>
#include  <nwkAddrMap.h>
#include  <nwkDiscovery.h>
#include  <nwkEDScan.h>
#include  <nwkFormation.h>
#include  <nwkStartRouter.h>
#include  <nwkPermitJoining.h>
#include  <nwkJoinInd.h>
#include  <nwkJoinReq.h>
#include  <nwkLeave.h>
#include  <nwkPacket.h>
#include  <nwkRx.h>
#include  <nwkTx.h>
#include  <nwkRouteDiscovery.h>
#include  <nwkRouteTable.h>
#include  <nwkRouting.h>
#include  <nwkRouteRecord.h>
#include  <nwkRouteReply.h>
#include  <nwkRouteRequest.h>
#include  <nwkLinkStatus.h>
#include  <nwkReportCommand.h>
#include  <nwkStatusReq.h>
#include  <nwkStatusInd.h>
#include  <nwkAddrConflict.h>
#include  <nwkUpdateCommand.h>
#include  <nwkSync.h>
#include  <nwkSyncLoss.h>
#include  <nwkManager.h>
#include  <nwkConcentrator.h>

/******************************************************************************
                                  Types section
 ******************************************************************************/
/* Internal variables of NWK layer. */ 
typedef struct _NwkMem_t
{
  /* Global NWK state. */
  NwkState_t               state;
  /* Network information base. */
  NIB_t                    nib;
  /* State of task manager. */
  NwkTaskManager_t         taskManager;
  /* Internal variables of NLME-RESET component. */
  NwkReset_t               reset;
  /* Internal variables of NLME-DISCOVERY component. */
  NwkDiscovery_t           discovery;
  /* States and parameters of NLDE-DATA component. */
  NwkDataReq_t             dataReq;
  NwkDataConf_t            dataConf;
  NwkPacketManager_t       packetManager;
  /* Internal variables of NLME-LEAVE component. */
  NwkLeave_t               leave;
  /* Internal variables of NLME-ED-SCAN component. */
  NwkEDScan_t              edScan;
  /* Broadcast transaction table. Only pointer to configServer and a size of table. */
  NwkBTT_t                 BTT;
  /* Address map table. */
  NwkAddressMap_t     addressTable;
  /* State of age component. */
  NwkAge_t                 age;
  /* Neighbor table */
  NwkNeighborTable_t       neighborTable;
  /* Address conflict resolver. */
  NwkAddrConflict_t  addrConflict;
  /* Requests to send command packets. */
  NwkCommands_t  commands;
#if defined(_COORDINATOR_)
  /* Internal variables of NLME-FORMATION component. */
  NwkFormation_t           formation;
#endif
#if defined(_ROUTER_)
  /* Internal variables of NLME-START-ROUTER component. */
  NwkStartRouter_t         startRouter;
#endif
#if defined(_ROUTER_) || defined(_ENDDEVICE_)
  /* Internal state of NLME-JOIN.request primitive. */
  NwkJoinReq_t             joinReq;
#endif
#if defined(_ROUTER_) || defined(_COORDINATOR_)
  /* Internal state of NLME-JOIN.indication primitive. */
  NwkJoinInd_t             joinInd;
  /* Internal variables of NLME-PERMIT-JOINING component. */
  NwkPermitJoining_t       permitJoining;
  /* Internal state of handler of a link status command. */
  NwkLinkStatus_t          linkStatus;
  /* Status and internals variables of a routing components. */
  NwkRouteDiscovery_t      routeDiscovery;
  NwkRouteDiscoveryTable_t routeDiscoveryTable;
  NwkRouteTable_t          routeTable;
  #if defined(_NWK_MANY_TO_ONE_)
 /* Internal state of handler of a route record command. */
  NwkRouteRecord_t         routeRecord;
  #endif
  /* Variables of network status receiver. */
  NwkStatusReceiver_t  statusReceiver;
  /* Variables of network status sender. */
  NwkStatusSender_t  statusSender;
#endif
#if defined(_ENDDEVICE_)
  /* Internal variables of NLME-SYNC component. */
  NwkSync_t                sync;
#endif
#if defined(_ROUTER_) && defined(NWK_COORD_REALIGNMENT)  
  /* Internal variables of NLME-SYNC-LOSS component. */
  NwkSyncLoss_t            syncLoss;
#endif
#if defined(_RESOLVE_PANID_CONFLICT_)
  /* Internal state of handler of a report command. */
  NwkReportCommand_t       nwkReportCommand;
  /* Internal state of handler of a update command. */
  NwkUpdateCommand_t       nwkUpdateCommand;
  #if defined(_NETWORK_MANAGER_)
  NwkManager_t  manager;
  #endif
#endif
#if defined(NWK_IS_CONCENTRATOR) && (0 < NWK_CONCENTRATOR_DISCOVERY_TIME)
  NwkConcentrator_t  concentrator;
#endif  
} NwkMem_t;

/* nwkMem is defined in nwkMem.c */
extern NwkMem_t nwkMem;

/******************************************************************************
                           Inline functions section
 ******************************************************************************/
INLINE NIB_t*  nwkMemNib(void)
{
  return &nwkMem.nib;
}

INLINE NwkTaskManager_t*  nwkMemTaskManager(void)
{
  return &nwkMem.taskManager;
}

INLINE NwkReset_t*  nwkMemReset(void)
{
  return &nwkMem.reset;
}

INLINE NwkDiscovery_t*  nwkMemDiscovery(void)
{
  return &nwkMem.discovery;
}

INLINE NwkDataReq_t*  nwkMemDataReq(void)
{
  return &nwkMem.dataReq;
}

INLINE NwkDataConf_t*  nwkMemDataConf(void)
{
  return &nwkMem.dataConf;
}

INLINE NwkPacketManager_t*  nwkMemPacketManager(void)
{
  return &nwkMem.packetManager;
}

INLINE NwkLeave_t*  nwkMemLeave(void)
{
  return &nwkMem.leave;
}

INLINE NwkEDScan_t*  nwkMemEDScan(void)
{
  return &nwkMem.edScan;
}

INLINE NwkBTT_t*  nwkMemBTT(void)
{
  return &nwkMem.BTT;
}

INLINE NwkAddressMap_t*  nwkMemAddressMap(void)
{
  return &nwkMem.addressTable;
}

INLINE NwkAge_t*  nwkMemAge(void)
{
  return &nwkMem.age;
}

INLINE NwkAddrConflict_t*  nwkMemAddrConflict(void)
{
  return &nwkMem.addrConflict;
}

INLINE NwkCommands_t*  nwkMemCommands(void)
{
  return &nwkMem.commands;
}

#if defined(_COORDINATOR_)
INLINE NwkFormation_t*  nwkMemFormation(void)
{
  return &nwkMem.formation;
}
#endif
#if defined(_ROUTER_)
INLINE NwkStartRouter_t*  nwkMemStartRouter(void)
{
  return &nwkMem.startRouter;
}
#endif
#if defined(_ROUTER_)||defined(_ENDDEVICE_)
INLINE NwkJoinReq_t*  nwkMemJoinReq(void)
{
  return &nwkMem.joinReq;
}
#endif
#if defined(_ROUTER_)||defined(_COORDINATOR_)
INLINE NwkJoinInd_t*  nwkMemJoinInd(void)
{
  return &nwkMem.joinInd;
}

INLINE NwkPermitJoining_t*  nwkMemPermitJoining(void)
{
  return &nwkMem.permitJoining;
}

INLINE NwkLinkStatus_t*  nwkMemLinkStatus(void)
{
  return &nwkMem.linkStatus;
}

INLINE NwkRouteDiscovery_t*  nwkMemRouteDiscovery(void)
{
  return &nwkMem.routeDiscovery;
}

INLINE NwkRouteDiscoveryTable_t*  nwkMemRouteDiscoveryTable(void)
{
  return &nwkMem.routeDiscoveryTable;
}

INLINE NwkRouteTable_t*  nwkMemRouteTable(void)
{
  return &nwkMem.routeTable;
}
#if defined(_NWK_MANY_TO_ONE_)
INLINE NwkRouteRecord_t*  nwkMemRouteRecord(void)
{
  return &nwkMem.routeRecord;
}
#endif

INLINE NwkStatusReceiver_t*  nwkMemStatusReceiver(void)
{
  return &nwkMem.statusReceiver;
}

INLINE NwkStatusSender_t*  nwkMemStatusSender(void)
{
  return &nwkMem.statusSender;
}

#endif

#if defined(_ENDDEVICE_)
INLINE NwkSync_t*  nwkMemSync(void)
{
  return &nwkMem.sync;
}
#endif
#if defined(_ROUTER_) && defined(NWK_COORD_REALIGNMENT)  
INLINE NwkSyncLoss_t*  nwkMemSyncLoss(void)
{
  return &nwkMem.syncLoss;
}
#endif

INLINE NwkNeighborTable_t*  nwkMemNeighborTable(void)
{
  return &nwkMem.neighborTable;
}

#if defined(_RESOLVE_PANID_CONFLICT_)
INLINE NwkReportCommand_t*  nwkMemReportCommand(void)
{
  return &nwkMem.nwkReportCommand;
}

INLINE NwkUpdateCommand_t*  nwkMemUpdateCommand(void)
{
  return &nwkMem.nwkUpdateCommand;
}
#if defined(_NETWORK_MANAGER_)
INLINE NwkManager_t*  nwkMemManager()
{
  return &nwkMem.manager;
}
#endif
#endif
#if defined(NWK_IS_CONCENTRATOR) && (0 < NWK_CONCENTRATOR_DISCOVERY_TIME)
INLINE NwkConcentrator_t*  nwkMemConcentrator()
{
  return &nwkMem.concentrator;
}
#endif  
#endif /* _NWK_MEM_H */
/* eof nwkMem.h */
