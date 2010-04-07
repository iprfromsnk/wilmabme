#ifndef _NWK_CONFIG_H_
#define _NWK_CONFIG_H_


#define DATA_ENDPOINT   1      // End-point for data transmission
#define COMMAND_ENDPOINT   2      // End-point for command transmission


#define START_CLUSTER  0x2000
#define WILMA_PROFILE 0x3000
#define BROADCAST_SHORT_ADDRESS 0xffff


#define COORDINATOR

void initNwkParams(void);

#endif
