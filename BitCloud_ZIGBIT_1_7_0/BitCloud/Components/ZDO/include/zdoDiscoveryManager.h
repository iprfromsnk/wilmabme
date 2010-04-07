/************************************************************************//**
  \file zdoDiscoveryManager.h

  \brief The header file describes the constants and types of
  ZDO discovery manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef ZDODISCOVERYMANAGER_H_
#define ZDODISCOVERYMANAGER_H_

#define DEVICE_ANNCE_REQ_LEN 11
#define NWK_ADDR_REQ_LEN 10
#define IEEE_ADDR_REQ_LEN 4
#define SYSTEM_SERVER_DISCOVERY_REQ_LEN 2
#define NODE_DESCRIPTOR_REQ_LEN 2
#define POWER_DESCRIPTOR_REQ_LEN 2
#define MATCH_DESCRIPTOR_REQ_LEN 6
#define SIMPLE_DESCRIPTOR_REQ_LEN 3
#define COMPLEX_DESCRIPTOR_REQ_LEN 2
#define USER_DESCRIPTOR_REQ_LEN 2
#define USER_DESCRIPTOR_CONF_REQ_LEN 19
#define ACTIVE_EP_REQ_LEN 2

#define NWK_ADDR_RESP_LEN 11
#define IEEE_ADDR_RESP_LEN 11
#define SYSTEM_SERVER_DISCOVERY_RESP_LEN 3
#define NODE_DESCRIPTOR_RESP_LEN 16
#define POWER_DESCRIPTOR_RESP_LEN 5
#define MATCH_DESCRIPTOR_RESP_LEN 4
#define USER_DESCRIPTOR_RESP_LEN 20
#define USER_DESCRIPTOR_CONF_RESP_LEN 3

void zdoZdpDiscoveryRequestCreate(void);
void zdoZdpDiscoveryMessageInd(void);

#endif /*ZDODISCOVERYMANAGER_H_*/
