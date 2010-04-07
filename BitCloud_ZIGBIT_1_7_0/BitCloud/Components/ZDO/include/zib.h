/************************************************************************//**
  \file zib.h

  \brief The header file describes the ZDO information base

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef ZIB_H_
#define ZIB_H_

#include <appFramework.h>
#include <nwkCommon.h>

#define LUXOFT_MANUFACTURER_CODE	    0x100c
#define CT_EPID_MASK                    0xFFFFFFFFFFFF0000 // ???
#define COMMISSIONING_EPID              0x0050C27710000000 // ???
#define NUM_ACTIVE_EP		            1 //FIXME
#define MAX_DISCOVERED_NETWORKS_NUMBER  3
#define NETWORK_SELECT_CRITERIES        (CHOOSENET_EXTPANID | CHOOSENET_STACKPROFILE | CHOOSENET_ZBVERSION)
#define BEACON_ORDER                    0x0f
#define SUPER_FRAME_ORDER               0x0f
#define BATTERY_LIFE_EXTENTION          true

typedef struct
{
  //scannig channel mask
  uint32_t             channelMask;
  //extended PAN ID
  ExtPanId_t           extPanId;
  //short address
  ShortAddr_t          shortAddr;
  //current channel
  uint8_t              channel;
  //mac address
  ExtAddr_t             uid;
  //parent extended address
  ExtAddr_t            parentExtAddress;
  //parent short address
  ShortAddr_t          parentNetworkAddress;
  //current PAN ID
  PanId_t              panID;
  //sync timer rate in milliseconds
  uint32_t             indirectPollRate;
  //node descriptor
  NodeDescriptor_t     nodeDescriptor;
  //node power descriptor
  PowerDescriptor_t    powerDescriptor;
  //simple descriptor
  //SimpleDescriptor_t   configSimpleDescriptors[NUM_ACTIVE_EP];
  //scanning duration in seconds
  uint8_t              scanDuration;
  //number of failure parent sync retries
  uint8_t              parentLinkRetryThreshold;
  //
  uint8_t              permitJoinDuration;
  //stack profile id
  ProfileId_t          stackProfile;
  //protocol version id
  uint8_t              protocolVersion;
  //sleeping period in milliseconds
  uint32_t             sleepPeriod;
} ZIB_t;

void zdoInitZIB(void);

extern ZIB_t zdoZIB;

#endif /*ZIB_H_*/
