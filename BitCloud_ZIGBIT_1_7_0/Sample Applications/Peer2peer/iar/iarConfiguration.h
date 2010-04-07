#ifndef _IARCONFIGURATION_H_
#define _IARCONFIGURATION_H_ 

//------------------------------------------------------------------------------
// Application parameters.
//------------------------------------------------------------------------------
// Selects USART as serial interface.
//#define APP_USE_VCP
#define APP_USE_USART

// USART channel to be used on the particular board.
//#define APP_USART_CHANNEL USART_CHANNEL_VCP
#define APP_USART_CHANNEL USART_CHANNEL_1

// Peer2Peer application usses static network addressing.
// 0 - coordinator
// 1-7 - routers
// Application device network address declaration.
#define APP_DEVICE_NWK_ADDRESS 0x0000
//#define APP_DEVICE_NWK_ADDRESS 0x0001

// Segmentation and reassembly of messages longer than the payload of a single NWK layer frame.
//#define APP_FRAGMENTATION

//------------------------------------------------------------------------------
// Stack parameters being set to Config Server.
//------------------------------------------------------------------------------
#define CS_EXT_PANID                      0xAAAAAAAAAAAAAAAALL
#define CS_NWK_UNIQUE_ADDR                true
#define CS_NWK_ADDR                       APP_DEVICE_NWK_ADDRESS
#define CS_RX_ON_WHEN_IDLE                true
#define CS_RF_TX_POWER                    3
#define CS_MAX_NETWORK_DEPTH              3
#define CS_NEIB_TABLE_SIZE                5
#define CS_MAX_CHILDREN_AMOUNT            4
#define CS_MAX_CHILDREN_ROUTER_AMOUNT     4
#define CS_ROUTE_TABLE_SIZE               8
#define CS_CHANNEL_MASK                   (1l<<0x0f)
#define CS_CHANNEL_PAGE                   0
#ifdef APP_FRAGMENTATION
  #define CS_APS_MAX_BLOCKS_AMOUNT        4
#endif

//-------------------------------------------------------------------------------
// Settings for the platforms without UID
//-------------------------------------------------------------------------------
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

