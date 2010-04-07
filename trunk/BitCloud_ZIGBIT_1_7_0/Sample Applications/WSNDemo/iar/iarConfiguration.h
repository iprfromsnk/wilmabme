#ifndef _IARCONFIGURATION_H_
#define _IARCONFIGURATION_H_ 

//------------------------------------------------------------------------------
// Application parameters.
//------------------------------------------------------------------------------
// Selects UART as serial interface.
//#define APP_USE_VCP
//#define APP_USE_NONE
#define APP_USE_USART

// UART channel to be used on the particular board.
//#define APP_USART_CHANNEL USART_CHANNEL_VCP
#define APP_USART_CHANNEL USART_CHANNEL_1

// Application device type declaration.
#define APP_DEV_TYPE_COORDINATOR
//#define APP_DEV_TYPE_ROUTER
//#define APP_DEV_TYPE_ENDDEVICE

// Data sending period
#define APP_TIMER_SENDING_PERIOD 5000

// After this amount of failed transmission in a row the rejoin network 
//procedure is done.
#define APP_THRESHOLD_FAILED_TRANSMISSION 10

// Coordinator extended PAN ID.
#define APP_COORDINATOR_EXT_PANID 0xAAAAAAAAAAAAAAAALL


//------------------------------------------------------------------------------
// Stack parameters being set to Config Server.
//------------------------------------------------------------------------------
// Take a look into configServer.h for the params description.
// Please pay attention: CS_UID value must be unique for every particular device
#define CS_EXT_PANID                      0xAAAAAAAAAAAAAAAALL
#define CS_RF_TX_POWER                    3
#define CS_END_DEVICE_SLEEP_PERIOD        5000
#define CS_NEIB_TABLE_SIZE                5
#define CS_MAX_CHILDREN_AMOUNT            4
#define CS_MAX_CHILDREN_ROUTER_AMOUNT     2
#define CS_ROUTE_TABLE_SIZE               10
#define CS_ADDRESS_MAP_TABLE_SIZE         2
#define CS_ROUTE_DISCOVERY_TABLE_SIZE     3
#define CS_APS_DATA_REQ_BUFFER_SIZE       2
#define CS_APS_ACK_FRAME_BUFFER_SIZE      2
#define CS_DUPLICATE_REJECTION_TABLE_SIZE 5
#define CS_NWK_DATA_REQ_BUFFER_SIZE       4
#define CS_NWK_DATA_IND_BUFFER_SIZE       3
#define CS_CHANNEL_MASK                   (1l<<0x0f)
#define CS_CHANNEL_PAGE                   0

//-------------------------------------------------------------------------------
// Settings for the platforms without UID
//-------------------------------------------------------------------------------
//Please note: CS_UID must be unique for every particular device
//#define CS_UID 0x2222333344448888LL


//-------------------------------------------------------------------------------
// Settings for security
//-------------------------------------------------------------------------------
// Preconfigured key which is used by NWK
// If it is not Trust Center and CS_ZDO_SECURITY_STATUS=3 then key is cleared by ZDO
#define CS_NETWORK_KEY {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC}

// 0 - preconfigured network key
// 1 - preconfigured trust center link key
// 2 - preconfigured trust center master key
// 3 - not preconfigured
#define CS_ZDO_SECURITY_STATUS         0
#define CS_APS_TRUST_CENTER_ADDRESS    0xAAAAAAAAAAAAAAAALL
#define CS_APS_SECURITY_TIMEOUT_PERIOD 10000

//------------------------------------------------------------------------------
// End of user-configurable part
//------------------------------------------------------------------------------
#include <MakerulesSelector.h>
#include <BoardConfig.h>

#endif // _IARCONFIGURATION_H_

//eof iarConfiguration.h
