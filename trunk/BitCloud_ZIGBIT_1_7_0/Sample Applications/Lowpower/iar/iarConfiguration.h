#define APP_USE_USART
//#define APP_USE_NONE
//#define APP_USE_VCP

//#define APP_USART_CHANNEL USART_CHANNEL_0
#define APP_USART_CHANNEL USART_CHANNEL_1
//#define APP_USART_CHANNEL USART_CHANNEL_VCP

#define APP_NWK_NODE_ADDRESS 0x0001

#define CS_NWK_UNIQUE_ADDR true
#define CS_EXT_PANID 0xAAAAAAAAAAAAAAAALL
#define CS_NEIB_TABLE_SIZE 8
#define CS_MAX_CHILDREN_AMOUNT 7
#define CS_MAX_CHILDREN_ROUTER_AMOUNT 0
#define CS_ROUTE_TABLE_SIZE 8
#define CS_END_DEVICE_SLEEP_PERIOD 10000
#define CS_CHANNEL_MASK (1l<<0x0f)
#define CS_CHANNEL_PAGE 0

//-------------------------------------------------------------------------------
// Settings for the platforms without UID
//-------------------------------------------------------------------------------
//Please note: this value must be unique for every device.
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

