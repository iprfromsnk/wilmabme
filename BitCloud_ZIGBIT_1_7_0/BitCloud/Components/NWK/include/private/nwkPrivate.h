/**************************************************************************//**
  \file nwkPrivate.h

  \brief Private headers files' union.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    01/05/2009 Max Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_PRIVATE_H
#define _NWK_PRIVATE_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include  <types.h>
#include  <mnUtils.h>
#include  <queue.h>
#include  <configServer.h>
#include  <appTimer.h>
#include  <taskManager.h>

#include  <nwkConfig.h>
#include  <nwkSystem.h>
#include  <nwkDbg.h>
#include  <nwkTaskManager.h>
#include  <nwkStateMachine.h>
#include  <nwkMem.h>
#include  <nwkFrame.h>
#include  <nwkAge.h>
#include  <nwkCommands.h>
#include  <nwkIB.h>
#include  <nwkNeighborTable.h>
#include  <nwkReset.h>
#include  <nwkAddress.h>
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
#include  <nwkDataReq.h>
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
#include  <nwkTxSecurity.h>
#include  <nwkConcentrator.h>

#endif  /* _NWK_PRIVATE_H */
/* eof nwkPrivate.h */
