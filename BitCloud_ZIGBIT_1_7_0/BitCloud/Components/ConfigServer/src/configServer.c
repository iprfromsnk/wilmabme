/***************************************************************************//**
  \file configServer.c

  \brief Config Server implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    04/07/07 A. Potashov - Created
*****************************************************************************/

#include <configServer.h>
#include <macAddr.h>
#include <macBuffers.h>
#include <pdsDataServer.h>

#ifndef _MAC2_
#include <appFramework.h>
#include <aps.h>
#include <apsDataManager.h>
#include <apsBindManager.h>
#include <apsGroupManager.h>
#include <apsSecurityManager.h>
#include <apsMemoryManager.h>
#include <dbg.h>
#include <zdo.h>
#include <nwkConfigServer.h>

#if defined(_SECURITY_)
#include <tcAuthentic.h>
#ifdef _HIGH_SECURITY_
#include <tcKeyEstablish.h>
#endif
#endif
#endif // _MAC2_

/*****************************************************************************
  Allocated memory
*****************************************************************************/
#ifndef _MAC2_

static Neib_t      csNeibTable[CS_NEIB_TABLE_SIZE];

static MutableNeib_t  csMutableNeibTable[CS_NEIB_TABLE_SIZE];

static ExtAddr_t    csUId = CS_UID;

static ExtPanId_t   csExtPANID = CS_EXT_PANID;

static ExtPanId_t   csNwkExtPANID = CS_NWK_EXT_PANID;

static ShortAddr_t csNwkAddr = CS_NWK_ADDR;

static ShortAddr_t csNwkParentAddr = 0xFFFF;

static uint8_t     csNwkDepth = 0;

static uint32_t    csChannelMask = CS_CHANNEL_MASK;

static uint32_t    csEndDeviceSleepPeriod = CS_END_DEVICE_SLEEP_PERIOD;

static NwkDataReqObj_t csNwkDataReqBuffer[CS_NWK_DATA_REQ_BUFFER_SIZE];

static NwkPacket_t csNwkDataIndBuffer[CS_NWK_DATA_IND_BUFFER_SIZE];

static ApsBuffer_t csApsDataReqBuffer[CS_APS_DATA_REQ_BUFFER_SIZE];

static ApsAcknowledgementEntry_t csApsAckFrameBuffer[CS_APS_ACK_FRAME_BUFFER_SIZE];

static uint32_t csIndirectPollRate = CS_INDIRECT_POLL_RATE;

static NwkJoinIndObj_t csJoinIndObjects[CS_JOIN_IND_OBJ_AMOUNT];

static MAC_PanDescriptor_t csMacPanDescriptorBuffer[CS_NEIB_TABLE_SIZE];

static ApsDuplicateRejectionTableElement_t csDuplicateRejectionTable[CS_DUPLICATE_REJECTION_TABLE_SIZE];

static uint8_t csMacFrameRxBuffer[CS_MAC_FRAME_RX_BUFFER_SIZE];

static uint8_t csApsGroupTable[CS_APS_GROUP_TABLE_SIZEOF];

static uint8_t csSoftResetReason = CS_SOFT_RESET_REASON;

//Stack profile identifier
static StackProfile_t csStackProfileId = CS_STACK_PROFILE;

//Protocol version identifier
static uint8_t csProtocolVersionId = CS_PROTOCOL_VERSION;

static NwkRouteItem_t csRouteTable[CS_ROUTE_TABLE_SIZE];
static NwkAddressMapEntry_t csAddressMapTable[CS_ADDRESS_MAP_TABLE_SIZE];
static NwkRouteDiscoveryItem_t csRouteDiscoveryTable[CS_ROUTE_DISCOVERY_TABLE_SIZE];
static NwkRouteDiscoveryObj_t csRouteDiscoveryObj[CS_NWK_ROUTE_DISCOVERY_OBJ_SIZE];
static NwkBTR_t csBTR[CS_NWK_BTT_SIZE];

static uint8_t csNwkMaxLinkStatusFailures = CS_NWK_MAX_LINK_STATUS_FAILURES;
static uint8_t csNwkEndDeviceMaxFailures = CS_NWK_END_DEVICE_MAX_FAILURES;

static uint8_t csNwkLogicalChannel = 0;
static PanId_t csNwkPanid = CS_NWK_PANID;

#ifdef _BINDING_
static uint8_t apsBindingTable[CS_APS_BINDING_TABLE_SIZE];
#endif //_BINDING_

#ifdef _APS_FRAGMENTATION_
// It allocates memory for array of blocks and array of its length
#if 0 < CS_APS_MAX_BLOCKS_AMOUNT
#define CS_FRAGMENTATION_MEMORY_POOL_SIZE CS_APS_MAX_BLOCKS_AMOUNT * APS_MAX_ASDU_SIZE + CS_APS_MAX_BLOCKS_AMOUNT
static uint8_t csFragmentationMemoryPool[CS_FRAGMENTATION_MEMORY_POOL_SIZE];
#else
#define CS_FRAGMENTATION_MEMORY_POOL_SIZE 0
#endif

#endif
/*****************************************************************************
 The Permit duration parameter affect directly to asscociation permit in
 MAC layer.
 0xff - always on
 0x00 - always off
*****************************************************************************/
static uint8_t csPermitDuration = CS_PERMIT_DURATION;
//============================================================================

static uint32_t csMacTransactionTime = CS_MAC_TRANSACTION_TIME;

static UserDescriptor_t   csUserDescriptor;
static uint16_t   csManufacturerCode = CS_MANUFACTURER_CODE;

#if defined(_SECURITY_)
static NWK_SecurityIB_t  csNwkSecurityIb;
PROGMEM_DECLARE(static const uint32_t  csApsSecurityTimeoutPeriod) = CS_APS_SECURITY_TIMEOUT_PERIOD;
static ExtAddr_t csApsTrustCenterAddress = CS_APS_TRUST_CENTER_ADDRESS;
static uint8_t csNetworkKey[SECURITY_KEY_SIZE] = CS_NETWORK_KEY;
static ApsBuffer_t csApsSecurityBuffers[CS_APS_SECURITY_BUFFERS_AMOUNT];
static TC_AuthenticObj_t csTcAuthenticProcessBuffer[CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT];
#ifdef _TC_PERMISSION_TABLE_
  static ExtAddr_t csTcDevicePermissionTable[CS_MAX_TC_ALLOWED_DEVICES_AMOUNT];
#endif
#ifdef _HIGH_SECURITY_
static ApsKeyPairDescriptor_t csApsKeyPairDescriptors[CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT];
PROGMEM_DECLARE(static const uint8_t csLinkKey[16]) = CS_LINK_KEY;
PROGMEM_DECLARE(static const uint8_t csMasterKey[16]) = CS_MASTER_KEY;
static TC_KeyEstablishObj_t csTcEstablishKeyBuffer[CS_MAX_TC_ESTABLISH_KEY_AMOUNT];
#endif
#endif

#else   // _MAC2_

// variables. Memory was not allocate for CS_MAC_TRANSACTION_TIME.
static uint64_t    csUId                      = CS_UID;
// buffers
static uint8_t csMacFrameRxBuffer[CS_MAC_FRAME_RX_BUFFER_SIZE];
static uint32_t csMacTransactionTime = CS_MAC_TRANSACTION_TIME;

#endif  // _MAC2_

/*****************************************************************************
The definitions of bit fields
*****************************************************************************/

typedef struct
{
#ifndef _MAC2_
  bool          rxOnWhenIdle : 1;
  bool          dtrWakeup : 1;
  bool          nwkPredefinedPanid : 1;
  bool          nwkUniqueAddr : 1;
  bool          nwkUseMulticast : 1;
  bool          complexDescriptorAvailable  : 1;
  bool          userDescriptorAvailable : 1;
#ifdef _POWER_FAILURE_
  bool          powerFailure : 1;
#endif
#ifdef _SECURITY_
  bool          securityOn   : 1;
  uint8_t       zdoSecurityStatus : 2;
#endif // _SECURITY_
  uint8_t       channelPage : 3;
  DeviceType_t  deviceType : 2;
  int8_t        rfTxPower : 7;
  uint8_t       maxFrameTransmissionTime : CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE;
  bool          autoPoll  : 1;
#else   // _MAC2_
  int8_t        rfTxPower : 7;
  uint8_t       maxFrameTransmissionTime : CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE;
#endif  // _MAC2_
} csBitFields_t;

/*****************************************************************************
The values of bit fields
*****************************************************************************/
csBitFields_t  csBitFields =
{
#ifndef _MAC2_
#ifdef CS_RX_ON_WHEN_IDLE
  CS_RX_ON_WHEN_IDLE, // rxOnWhenIdle
#else
  (CS_DEVICE_TYPE == DEVICE_TYPE_END_DEVICE) ? false : true, // rxOnWhenIdle
#endif
  CS_DTR_WAKEUP,
  CS_NWK_PREDEFINED_PANID,
  CS_NWK_UNIQUE_ADDR,
  CS_NWK_USE_MULTICAST,
  CS_COMPLEX_DESCRIPTOR_AVAILABLE,
  CS_USER_DESCRIPTOR_AVAILABLE,
#ifdef _POWER_FAILURE_
  CS_POWER_FAILURE,
#endif
#ifdef _SECURITY_
  CS_SECURITY_ON,
  CS_ZDO_SECURITY_STATUS,
#endif // _SECURITY_
  CS_CHANNEL_PAGE,
  CS_DEVICE_TYPE,
  CS_RF_TX_POWER,
  CS_MAX_FRAME_TRANSMISSION_TIME,
  CS_AUTO_POLL,
#else   // _MAC2_
  CS_RF_TX_POWER, // rfTxPower
  CS_MAX_FRAME_TRANSMISSION_TIME,
#endif  // _MAC2_
};

/*****************************************************************************
Read parameter value specified by parameter identifier
Parameters:
  parameterId     - parameter Id
  parameterValue  - parameter value pointer will be read to
Returns:
  None
*****************************************************************************/
void CS_ReadParameter(CS_ParameterId_t parameterId, void *parameterValue)
{
  if (parameterValue)
  {
    switch (parameterId)
    {
#ifndef _MAC2_
      case CS_DEVICE_TYPE_ID:
        *((DeviceType_t *) parameterValue) = csBitFields.deviceType;
        break;
      case CS_NWK_ADDR_ID:
        *((ShortAddr_t *) parameterValue) = csNwkAddr;
        break;
      case CS_NWK_PARENT_ADDR_ID:
        *((ShortAddr_t *) parameterValue) = csNwkParentAddr;
        break;
      case CS_NWK_DEPTH_ID:
        *((uint8_t *) parameterValue) = csNwkDepth;
        break;
      case CS_RX_ON_WHEN_IDLE_ID:
        *((bool *) parameterValue) = csBitFields.rxOnWhenIdle;
        break;
      case CS_INDIRECT_POLL_RATE_ID:
        *((uint32_t *) parameterValue) = csIndirectPollRate;
        break;
      case CS_NEIB_TABLE_SIZE_ID:
        *((NwkSizeOfNeighborTable_t *) parameterValue) = CS_NEIB_TABLE_SIZE;
        break;
      case CS_MAC_PAN_DESCRIPTOR_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_NEIB_TABLE_SIZE;
        break;
      case CS_MAX_CHILDREN_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_CHILDREN_AMOUNT;
        break;
      case CS_MAX_CHILDREN_ROUTER_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_CHILDREN_ROUTER_AMOUNT;
        break;
      case CS_MAX_NETWORK_DEPTH_ID:
        *((uint8_t *) parameterValue) = CS_MAX_NETWORK_DEPTH;
        break;
      case CS_END_DEVICE_SLEEP_PERIOD_ID:
        *((uint32_t *) parameterValue) = csEndDeviceSleepPeriod;
        break;
      case CS_ADDRESS_ASSIGNMENT_METHOD_ID:
        *((uint8_t *) parameterValue) = CS_ADDRESS_ASSIGNMENT_METHOD;
        break;
      case CS_NWK_DATA_IND_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_DATA_IND_BUFFER_SIZE;
        break;
      case CS_NWK_DATA_REQ_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_DATA_REQ_BUFFER_SIZE;
        break;
      case CS_APS_DATA_REQ_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_APS_DATA_REQ_BUFFER_SIZE;
        break;
      case CS_JOIN_IND_OBJ_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_JOIN_IND_OBJ_AMOUNT;
        break;
      case CS_APS_ACK_FRAME_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_APS_ACK_FRAME_BUFFER_SIZE;
        break;
      case CS_PROTOCOL_VERSION_ID:
        *((uint8_t *) parameterValue) = csProtocolVersionId;
        break;
      case CS_STACK_PROFILE_ID:
        *((StackProfile_t *) parameterValue) = csStackProfileId;
        break;
      case CS_SCAN_DURATION_ID:
        *((uint8_t *) parameterValue) = CS_SCAN_DURATION;
        break;
      case CS_PERMIT_DURATION_ID:
        *((uint8_t *) parameterValue) = csPermitDuration;
        break;
      case CS_NWK_EXT_PANID_ID:
        *((ExtPanId_t *) parameterValue) = csNwkExtPANID;
        break;
      case CS_EXT_PANID_ID:
        *((ExtPanId_t *) parameterValue) = csExtPANID;
        break;
      case CS_CHANNEL_MASK_ID:
        *((uint32_t *) parameterValue) = csChannelMask;
        break;
      case CS_CHANNEL_PAGE_ID:
        *((uint8_t *) parameterValue) = csBitFields.channelPage;
        break;
#endif // _MAC2_
      case CS_UID_ID:
        //*((uint64_t *) parameterValue) = csUId;
        memcpy(parameterValue, &csUId, sizeof(ExtAddr_t));
        break;
#ifndef _MAC2_
      case CS_DUPLICATE_REJECTION_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_DUPLICATE_REJECTION_TABLE_SIZE;
        break;
#endif // _MAC2_
      case CS_MAC_FRAME_RX_BUFFER_SIZE_ID:
        *((uint16_t *) parameterValue) = CS_MAC_FRAME_RX_BUFFER_SIZE;
        break;
#ifndef _MAC2_
      case CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT;
        break;
      case CS_APS_GROUP_TABLE_GROUPS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_GROUP_TABLE_GROUPS_AMOUNT;
        break;
#endif // _MAC2_
      case CS_RF_TX_POWER_ID:
        *((int8_t *) parameterValue) = csBitFields.rfTxPower;
        break;
#ifndef _MAC2_
      case CS_SOFT_RESET_REASON_ID:
        *((uint8_t *) parameterValue) = csSoftResetReason;
        break;
      case CS_NWK_USE_MULTICAST_ID:
        *((bool *) parameterValue) = csBitFields.nwkUseMulticast;
        break;
      case CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID:
        *((bool *) parameterValue) = csBitFields.complexDescriptorAvailable;
        break;
      case CS_USER_DESCRIPTOR_AVAILABLE_ID:
        *((bool *) parameterValue) = csBitFields.userDescriptorAvailable;
        break;
      case CS_MANUFACTURER_CODE_ID:
        *((uint16_t *) parameterValue) = csManufacturerCode;
        break;
#ifdef _POWER_FAILURE_
      case CS_POWER_FAILURE_ID:
        *((bool *) parameterValue) = csBitFields.powerFailure;
        break;
#endif
      case CS_ROUTE_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ROUTE_TABLE_SIZE;
        break;
      case CS_ADDRESS_MAP_TABLE_SIZE_ID:
        *((NwkSizeOfAddressMap_t *) parameterValue) = CS_ADDRESS_MAP_TABLE_SIZE;
        break;
      case CS_ROUTE_DISCOVERY_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ROUTE_DISCOVERY_TABLE_SIZE;
        break;
      case CS_ROUTE_DISCOVERY_OBJ_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_ROUTE_DISCOVERY_OBJ_SIZE;
        break;
      case CS_BTT_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_BTT_SIZE;
        break;
      case CS_NWK_MAX_LINK_STATUS_FAILURES_ID:
        *((uint8_t *) parameterValue) = csNwkMaxLinkStatusFailures;
        break;
      case CS_NWK_END_DEVICE_MAX_FAILURES_ID:
        *((uint8_t *) parameterValue) = csNwkEndDeviceMaxFailures;
        break;
#endif //_MAC2_
      case CS_MAC_TRANSACTION_TIME_ID:
        *((uint32_t *) parameterValue) = csMacTransactionTime;
        break;
#ifndef _MAC2_
      case CS_NWK_UNIQUE_ADDR_ID:
        *((bool *) parameterValue) = csBitFields.nwkUniqueAddr;
        break;
      case CS_DTR_WAKEUP_ID:
        *((bool *) parameterValue) = csBitFields.dtrWakeup;
        break;
      case CS_NWK_LOGICAL_CHANNEL_ID:
        *((uint8_t *) parameterValue) = csNwkLogicalChannel;
        break;
      case CS_NWK_PANID_ID:
        *((PanId_t *) parameterValue) = csNwkPanid;
        break;
      case CS_ZDP_USER_DESCRIPTOR_ID:
        memcpy(parameterValue, &csUserDescriptor, sizeof(csUserDescriptor));
        break;
      case CS_NWK_PREDEFINED_PANID_ID:
         *((bool *) parameterValue) = csBitFields.nwkPredefinedPanid;
        break;
      case CS_AUTO_POLL_ID:
         *((bool *) parameterValue) = csBitFields.autoPoll;
        break;
#ifdef _BINDING_
      case CS_APS_BINDING_TABLE_ENTRIES_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_BINDING_TABLE_ENTRIES_AMOUNT;
        break;
      case CS_APS_BINDING_TABLE_ENTRY_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_APS_BINDING_TABLE_ENTRY_SIZE;
        break;
#endif //_BINDING_
#ifdef _APS_FRAGMENTATION_
      case CS_APS_MAX_BLOCKS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_MAX_BLOCKS_AMOUNT;
        break;
#endif
#endif // _MAC2_
      case CS_MAX_FRAME_TRANSMISSION_TIME_ID:
        *((uint8_t *) parameterValue) = csBitFields.maxFrameTransmissionTime;
        break;
#ifndef _MAC2_
/***********************************************************************
 Security related action's
***********************************************************************/
#ifdef _SECURITY_
    case CS_SECURITY_ON_ID:
        *(bool *)parameterValue = csBitFields.securityOn;
        break;
      case CS_APS_SECURITY_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_SECURITY_BUFFERS_AMOUNT;
        break;
      case CS_APS_SECURITY_TIMEOUT_PERIOD_ID:
        memcpy_P(parameterValue, &csApsSecurityTimeoutPeriod, sizeof(uint32_t));
        break;
      case CS_APS_TRUST_CENTER_ADDRESS_ID:
        memcpy(parameterValue, &csApsTrustCenterAddress, sizeof(ExtAddr_t));
        break;
#ifdef _SECURITY_
      case CS_ZDO_SECURITY_STATUS_ID:
        *((uint8_t *) parameterValue) = csBitFields.zdoSecurityStatus;
        break;
#endif // _SECURITY_
      case CS_SECURITY_LEVEL_ID:
        *((uint8_t *) parameterValue) = CS_SECURITY_LEVEL;
        break;
      case CS_SECURITY_ALL_FRAMES_ID:
        *((bool *) parameterValue) = CS_SECURITY_ALL_FRAMES;
        break;
      case CS_NETWORK_KEY_ID:
        memcpy(parameterValue, csNetworkKey, sizeof(csNetworkKey));
        break;
      case CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT_ID:
          *((uint8_t *) parameterValue) = CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT;
      break;
#ifdef _TC_PERMISSION_TABLE_
      case CS_MAX_TC_ALLOWED_DEVICES_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_ALLOWED_DEVICES_AMOUNT;
      break;
#endif
#ifdef _HIGH_SECURITY_
      case CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT;
        break;
      case CS_LINK_KEY_ID:
        memcpy_P(parameterValue, csLinkKey, sizeof(csLinkKey));
        break;
      case CS_MASTER_KEY_ID:
        memcpy_P(parameterValue, csMasterKey, sizeof(csMasterKey));
        break;
      case CS_MAX_TC_ESTABLISH_KEY_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_ESTABLISH_KEY_AMOUNT;
      break;
#endif // _SECURITY_
#endif // _HIGH_SECURITY_
#endif // _MAC2_
      default:
        break;
    }
  }
}


/*****************************************************************************
Allocate memory area specified by memory identifier
Parameters:
  memoryId        - memory area Id
  memoryPtr       - pointer to pointer wich will be modified
Returns:
  None
*****************************************************************************/
void CS_GetMemory(CS_MemoryId_t memoryId, void **memoryPtr)
{
  switch (memoryId)
  {
#ifndef _MAC2_
    case CS_NEIB_TABLE_ID:
      *memoryPtr = csNeibTable;
      break;
    case CS_NWK_DATA_REQ_BUFFER_ID:
      *memoryPtr = csNwkDataReqBuffer;
      break;
    case CS_NWK_DATA_IND_BUFFER_ID:
      *memoryPtr = csNwkDataIndBuffer;
      break;
    case CS_APS_DATA_REQ_BUFFER_ID:
      *memoryPtr = csApsDataReqBuffer;
      break;
    case CS_APS_ACK_FRAME_BUFFER_ID:
      *memoryPtr = csApsAckFrameBuffer;
      break;
    case CS_JOIN_IND_OBJ_ID:
      *memoryPtr = csJoinIndObjects;
      break;
    case CS_MAC_PAN_DESCRIPTOR_BUFFER_ID:
      *memoryPtr = csMacPanDescriptorBuffer;
      break;
    case CS_DUPLICATE_REJECTION_TABLE_ID:
      *memoryPtr = csDuplicateRejectionTable;
      break;
#endif //_MAC2_
    case CS_MAC_FRAME_RX_BUFFER_ID:
      *memoryPtr = csMacFrameRxBuffer;
      break;
#ifndef _MAC2_
    case CS_APS_GROUP_TABLE_ID:
      *memoryPtr = csApsGroupTable;
      break;
    case CS_ROUTE_TABLE_ID:
      *memoryPtr = csRouteTable;
      break;
    case CS_ADDRESS_MAP_TABLE_ID:
      *memoryPtr = csAddressMapTable;
      break;
    case CS_ROUTE_DISCOVERY_TABLE_ID:
      *memoryPtr = csRouteDiscoveryTable;
      break;
    case CS_ROUTE_DISCOVERY_OBJ_ID:
      *memoryPtr = csRouteDiscoveryObj;
      break;
    case CS_BTT_ID:
      *memoryPtr = csBTR;
      break;
    case CS_MUTABLE_NEIB_TABLE_ID:
       *memoryPtr = csMutableNeibTable;
      break;
   case CS_EXT_ADDR_ID:
       *memoryPtr = &csUId;
      break;
#ifdef _BINDING_
   case CS_APS_BINDING_TABLE_ID:
     *memoryPtr = apsBindingTable;
     break;
#endif //_BINDING_
#ifdef _APS_FRAGMENTATION_
    case CS_APS_FRAGMENTATION_MEMORY_POOL_ID:
#if 0 == CS_FRAGMENTATION_MEMORY_POOL_SIZE
      *memoryPtr = 0;
#else
      *memoryPtr = csFragmentationMemoryPool;
#endif
      break;
#endif
/***********************************************************************
  Security related action's
***********************************************************************/
#if defined(_SECURITY_)
    case CS_NWK_SECURITY_IB_ID:
      *memoryPtr = &csNwkSecurityIb;
      break;
    case CS_APS_SECURITY_BUFFERS_ID:
      *memoryPtr = csApsSecurityBuffers;
      break;
    case CS_TC_AUTHENTIC_PROCESS_BUFFER_ID:
      *memoryPtr = csTcAuthenticProcessBuffer;
      break;
#ifdef _TC_PERMISSION_TABLE_
    case CS_TC_PERMISSION_TABLE_ID:
      *memoryPtr = csTcDevicePermissionTable;
      break;
#endif
#ifdef _HIGH_SECURITY_
    case CS_APS_KEY_PAIR_DESCRIPTORS_ID:
      *memoryPtr = csApsKeyPairDescriptors;
      break;
    case CS_TC_ESTABLISH_KEY_BUFFER_ID:
      *memoryPtr = csTcEstablishKeyBuffer;
      break;
#endif
#endif
#endif //_MAC2_
    default:
      *memoryPtr = NULL;
      break;
  }
}


/*****************************************************************************
Write parameter value specified by parameter identifier and parameter value
pointer
Parameters:
  parameterId     - parameter Id
  parameterValue  - parameter value pointer will be write from
Returns:
  None
*****************************************************************************/
extern void CS_WriteParameter(CS_ParameterId_t parameterId, void *parameterValue)
{
  switch (parameterId)
  {
#ifndef _MAC2_
    case CS_NWK_ADDR_ID:
      csNwkAddr = *(ShortAddr_t *) parameterValue;
      break;
    case CS_NWK_PARENT_ADDR_ID:
      csNwkParentAddr = *((ShortAddr_t *) parameterValue);
      break;
    case CS_NWK_DEPTH_ID:
      csNwkDepth = *((uint8_t *) parameterValue);
      break;
    case CS_NWK_UNIQUE_ADDR_ID:
      csBitFields.nwkUniqueAddr = *(bool *) parameterValue;
      break;
    case CS_DEVICE_TYPE_ID:
      csBitFields.deviceType = *(DeviceType_t *) parameterValue;
      break;
#endif // _MAC2_
    case CS_UID_ID:
      csUId = *(ExtAddr_t *) parameterValue;
      break;
#ifndef _MAC2_
    case CS_EXT_PANID_ID:
      csExtPANID = *(ExtPanId_t *) parameterValue;
      break;
    case CS_NWK_EXT_PANID_ID:
      csNwkExtPANID = *(ExtPanId_t *) parameterValue;
      break;
    case CS_RX_ON_WHEN_IDLE_ID:
      csBitFields.rxOnWhenIdle = *(bool *) parameterValue;
      break;
    case CS_CHANNEL_MASK_ID:
      csChannelMask = *(uint32_t *) parameterValue;
      break;
    case CS_CHANNEL_PAGE_ID:
      csBitFields.channelPage = *(uint8_t *) parameterValue;
      break;
#endif //_MAC2_
    case CS_RF_TX_POWER_ID:
      csBitFields.rfTxPower = *(int8_t *) parameterValue;
      break;
#ifndef _MAC2_
    case CS_NWK_MAX_LINK_STATUS_FAILURES_ID:
      csNwkMaxLinkStatusFailures = *((uint8_t *) parameterValue);
      break;
    case CS_NWK_END_DEVICE_MAX_FAILURES_ID:
      csNwkEndDeviceMaxFailures = *((uint8_t *) parameterValue);
      break;
    case CS_SOFT_RESET_REASON_ID:
      csSoftResetReason = *(uint8_t *) parameterValue;
      break;
    case CS_STACK_PROFILE_ID:
      csStackProfileId = *(StackProfile_t *) parameterValue;
      break;
    case CS_PROTOCOL_VERSION_ID:
      csProtocolVersionId = *(uint8_t *) parameterValue;
      break;
    case CS_PERMIT_DURATION_ID:
      csPermitDuration = *(uint8_t *) parameterValue;
      break;
    case CS_INDIRECT_POLL_RATE_ID:
      csIndirectPollRate = *(uint32_t *) parameterValue;
      break;
    case CS_END_DEVICE_SLEEP_PERIOD_ID:
      csEndDeviceSleepPeriod = *(uint32_t *) parameterValue;
      break;
    case CS_NWK_USE_MULTICAST_ID:
      csBitFields.nwkUseMulticast = *(bool *) parameterValue;
      break;
    case CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID:
      csBitFields.complexDescriptorAvailable = *((bool *) parameterValue);
      break;
    case CS_USER_DESCRIPTOR_AVAILABLE_ID:
      csBitFields.userDescriptorAvailable = *((bool *) parameterValue);
      break;
    case CS_MANUFACTURER_CODE_ID:
      csManufacturerCode = *((uint16_t *) parameterValue);
      break;
#ifdef _POWER_FAILURE_
    case CS_POWER_FAILURE_ID:
      csBitFields.powerFailure = *((bool *) parameterValue);
      break;
#endif
    case CS_DTR_WAKEUP_ID:
      csBitFields.dtrWakeup = *(bool *) parameterValue;
      break;
    case CS_NWK_LOGICAL_CHANNEL_ID:
      csNwkLogicalChannel = *(uint8_t *) parameterValue;
      break;
    case CS_NWK_PANID_ID:
      csNwkPanid = *(PanId_t *) parameterValue;
      break;
    case CS_ZDP_USER_DESCRIPTOR_ID:
      memcpy(&csUserDescriptor, parameterValue, sizeof(csUserDescriptor));
      break;
    case CS_NWK_PREDEFINED_PANID_ID:
      csBitFields.nwkPredefinedPanid = *((bool *) parameterValue);
      break;
    case CS_AUTO_POLL_ID:
      csBitFields.autoPoll = *((bool *) parameterValue);
      break;
#endif //_MAC2_
    case CS_MAX_FRAME_TRANSMISSION_TIME_ID:
      csBitFields.maxFrameTransmissionTime = *(uint8_t *) parameterValue;
      break;
    case CS_MAC_TRANSACTION_TIME_ID:
      csMacTransactionTime = *(uint32_t *) parameterValue;
      break;
#ifndef _MAC2_
#ifdef _SECURITY_
    case CS_SECURITY_ON_ID:
      csBitFields.securityOn = *(bool *) parameterValue;
      break;
    case CS_ZDO_SECURITY_STATUS_ID:
      csBitFields.zdoSecurityStatus = *(uint8_t *) parameterValue;
      break;
    case CS_NETWORK_KEY_ID:
      memcpy(&csNetworkKey, parameterValue, sizeof(csNetworkKey));
      break;
    case CS_APS_TRUST_CENTER_ADDRESS_ID:
      memcpy(&csApsTrustCenterAddress, parameterValue, sizeof(ExtAddr_t));
      break;
#endif
#endif //_MAC2_
    default:
      break;
  }
}



/*****************************************************************************
Init the Config Server
Parameters:
  None
Returns:
  None
*****************************************************************************/
void CS_Init(void)
{
  PDS_Init();
}

/*****************************************************************************
Set PDS default
Parameters:
  None
Returns:
  None
*****************************************************************************/
void CS_PdsDefaultValue(void)
{
#ifndef _MAC2_
  csNwkExtPANID = CS_NWK_EXT_PANID;
  csExtPANID = CS_EXT_PANID;
  csNwkAddr = CS_NWK_ADDR;
  csChannelMask = CS_CHANNEL_MASK;
  csBitFields.channelPage = CS_CHANNEL_PAGE;
#endif //_MAC2_
  csUId = CS_UID;
#ifndef _MAC2_
  csBitFields.deviceType = CS_DEVICE_TYPE;
  #ifdef CS_RX_ON_WHEN_IDLE
    csBitFields.rxOnWhenIdle = CS_RX_ON_WHEN_IDLE;
  #else
    csBitFields.rxOnWhenIdle = (CS_DEVICE_TYPE == DEVICE_TYPE_END_DEVICE) ? false : true;
  #endif
#endif //_MAC2_
  csBitFields.rfTxPower = CS_RF_TX_POWER;
#ifndef _MAC2_
  csSoftResetReason = CS_SOFT_RESET_REASON;
  csBitFields.nwkUniqueAddr = CS_NWK_UNIQUE_ADDR;
  csBitFields.dtrWakeup = CS_DTR_WAKEUP;
  csBitFields.complexDescriptorAvailable = CS_COMPLEX_DESCRIPTOR_AVAILABLE;
  csBitFields.userDescriptorAvailable = CS_USER_DESCRIPTOR_AVAILABLE;
  csBitFields.autoPoll = CS_AUTO_POLL;

  csNwkLogicalChannel = 0;
  csNwkPanid = CS_NWK_PANID;
  csManufacturerCode = CS_MANUFACTURER_CODE;
  csNwkMaxLinkStatusFailures = CS_NWK_MAX_LINK_STATUS_FAILURES;
  csNwkEndDeviceMaxFailures = CS_NWK_END_DEVICE_MAX_FAILURES;

#if defined(_SECURITY_)
  csBitFields.securityOn = CS_SECURITY_ON;
  csBitFields.zdoSecurityStatus = CS_ZDO_SECURITY_STATUS;
  {const uint8_t csDefaultNetworkKey[16] = CS_NETWORK_KEY;
   uint8_t i = 0;
   for (; i < 16; i++)
     csNetworkKey[i] = csDefaultNetworkKey[i];
  }
#endif // _SECURITY_
#endif //_MAC2_
}

