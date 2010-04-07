/**************************************************************************//**
  \file nwkConfig.h

  \brief Constant definition header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    20/06/07 V. Panov - Created.
    29/09/08 M. Gekk  - Values of constants for a network from 60 
                        nodes are increased.
******************************************************************************/
#if !defined  _NWK_CONFIG_H
#define  _NWK_CONFIG_H

/******************************************************************************
                             Definitions section
 ******************************************************************************/
/* A Boolean flag indicating whether the device is capable of becoming 
 * the ZigBee coordinator. ZigBee spec r17, page 338, table 3.43.
 * */
#if defined(_COORDINATOR_)
#define NWKC_COORDINATOR_CAPABLE                true
#else
#define NWKC_COORDINATOR_CAPABLE                false
#endif

/* Define for coordinator address */
#define NWKC_COORD_ADDR                         0x0000

/* North America */
/* #define NWK_NO_WIFI_CHANNELS_MASK               0x610800 */
/* Europe */
#define NWK_NO_WIFI_CHANNELS_MASK               0x618000

#define NWK_FAVOURITE_CHANNELS_MASK             (NWK_NO_WIFI_CHANNELS_MASK)

#define NWKC_PROTOCOL_ID                        0

#define NWKC_INITIAL_LINK_STATUS_PERIOD         15000UL /* msec*/

/* Max package transmission time * this const */
#define NWKC_BROADCAST_DELIVERY_PACKAGES        400

#define NWK_MAX_CHANNEL 26

#define NWK_MAX_LINK_STATUS_FAILURES            3
#define NWK_END_DEVICE_MAX_FAILURES             3

#define NWK_DATA_RETRANSMISSION_AMOUNT          3
#define NWK_FAILURES_TO_REMOVE_FROM_ROUTE_TABE  4
#define NWK_ROUTE_DISCOVERY_ITEM_TTL            1200

/* #define NWK_PJ_TIMER_SUPPORT */
/* #define NWK_PJ_SUPERSEDE_ALL_PREVIOUS_REQUESTS */

#define NWK_MAX_ED_LEVEL      0xCC /* 255 * 0.8 */

/* Support network realignment */
/* #define NWK_COORD_REALIGNMENT */

/* Turn on/off nonstandard beacon filtering */
#define NWK_NONSTANDARD_BEACON_FILTER

#if defined(NWK_NONSTANDARD_BEACON_FILTER)
/* Filter by extended pan id */
#define  NWK_BEACON_FILTER_EXTENDED_PANID
/* If predefined short pan id then discard beacons with other pan id. */
#define  NWK_BEACON_FILTER_PREDEFINED_PANID
/* Beacons with the end device capacity bit equal zero will discard. */
#define  NWK_BEACON_FILTER_END_DEVICE_CAPACITY
/* Beacons with the router capacity bit equal zero will discard. */
#define  NWK_BEACON_FILTER_ROUTER_CAPACITY
#endif

/* Update the neighbor table only if our network address is presented in the received 
 * link status command. */
/* #define NWK_LINK_STATUS_ONLY_IN_LIST */

/* To leave a child with device type equal DEVICE_TYPE_RUTER */
/* #define NWK_LEAVE_CHILD_ROUTER */

/* Duration of searching other networks on same channel.
 * It is ~(2^NWK_REPORT_SCAN_DURATION)*960*16 (usec) - for 2.4MHz */
#define  NWK_SEARCH_NETWORKS_DURATION  8 /* ~4sec - 2.4MHz */

#define  NWK_SELECT_RANDOM_PARENT
#define  NWK_DELTA_LQI  (255/10)

/* Type of routing. */
#define _MESH_ROUTING_
//#define _TREE_ROUTING_

//#define NWK_IS_CONCENTRATOR
/* The hop count radius for concentrator route discoveries.
 * ZigBee spec r18, Table 3.44, page 348. */
#define NWK_CONCENTRATOR_RADIUS  8  /* hop */
/* The time in seconds between concentrator route discoveries.
 * ZigBee spec r18, Table 3.44, page 348. */
#define NWK_CONCENTRATOR_DISCOVERY_TIME  60 /* sec. */

#if defined NWK_IS_CONCENTRATOR
#define NWKC_NO_ROUTE_CACHE false
#else
#define NWKC_NO_ROUTE_CACHE  true
#endif /* NWK_IS_CONCENTRATOR */
#define NWKC_ROUTE_RECORD_ITEM_SIZE  5
#define NWKC_ROUTE_RECORD_TABLE_SIZE  3

#endif /* _NWK_CONFIG_H */
/* eof nwkConfig.h */
