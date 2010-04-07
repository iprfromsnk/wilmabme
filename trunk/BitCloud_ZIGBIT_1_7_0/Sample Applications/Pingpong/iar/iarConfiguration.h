//------------------------------------------------------------------------------
// Application parameters.
//------------------------------------------------------------------------------
// PingPong application usses static network addressing.
// For the platforms without DIP switches:
// 0 - coordinator
// 1-3 - routers
#define APP_DEVICE_NWK_ADDRESS 0x0000

// Device which is the last in the cycle - sends data to the coordinator (for the 
// platforms without DIP switches):
#define APP_FINAL_DEVICE false

// LED blinking interval during network start, ms
#define TIMER_STARTING_NETWORK  500

// Packet forwarding delay, ms
#define TIMER_FW_DELAY  0

//Device search through binding or by static addresses
#define APP_USE_BINDING 0
//#define APP_USE_BINDING 1

//------------------------------------------------------------------------------
// Stack parameters being set to Config Server.
//------------------------------------------------------------------------------
#define CS_NEIB_TABLE_SIZE                5
#define CS_MAX_CHILDREN_AMOUNT            4
#define CS_MAX_CHILDREN_ROUTER_AMOUNT     4
#define CS_CHANNEL_MASK                   (1l<<0x0f)
#define CS_CHANNEL_PAGE                   0
#define CS_EXT_PANID                      0xAAAAAAAAAAAAAAAALL
#if APP_USE_BINDING == 1
  #define CS_APS_BINDING_TABLE_ENTRIES_AMOUNT  5
#endif

//-------------------------------------------------------------------------------
// Settings for the platforms without UID
//-------------------------------------------------------------------------------
//Please note: CS_UID must be unique for every particular device
//#define CS_UID 0x2222333344448888LL

//------------------------------------------------------------------------------
// End of user-configurable part
//------------------------------------------------------------------------------
#include <MakerulesSelector.h>
#include <BoardConfig.h>
