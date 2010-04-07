/************************************************************************//**
  \file zdo.h

  \brief The header file describes the public ZDO interface and ZDO types

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _ZDO_H
#define _ZDO_H

#include <macAddr.h>
#include <appFramework.h>
#include <aps.h>
#include <configServer.h>

// \cond internal
#define ZDP_REQUEST_MASK  0x7FFF
#define ZDP_RESPONSE_MASK 0x8000

#ifdef _SECURITY_
#define PRECONFIGURED_NETWORK_KEY NWK_PRECONFIGURED_NETWORK_KEY
#define PRECONFIGURED_TRUST_CENTER_LINK_KEY 1
#define PRECONFIGURED_TRUST_CENTER_MASTER_KEY 2
#define NOT_PRECONFIGURED 3

#ifndef ZDO_SECURITY_STATUS
#define ZDO_SECURITY_STATUS NOT_PRECONFIGURED
#endif //ZDO_SECURITY_STATUS


#define ZDO_NONE_SECURITY_MODE     0
#define ZDO_STANDARD_SECURITY_MODE 1
#define ZDO_HIGH_SECURITY_MODE     2
#endif//_SECURITY_

#define MAX_REQUESTED_CLUSTER_NUMBER 9
#define MAX_ACTIVE_EP_NUMBER 3

#define ZDP_NEIGBOR_TABLE_LIST_SIZE  3
#define ZDP_ADDR_LIST_SIZE  10
// \endcond
/********************************************************************************//**
\brief Reasons of device leaving
***********************************************************************************/
typedef enum
{
  LEAVED_BY_PARENT,
  LINK_FAIL,
  LEAVE_REQ
} NetLostReason_t;

/*!
\brief ZDO result status primitives.
*/
typedef enum
{
  //! The primitive has finished successfully
  ZDO_SUCCESS_STATUS                = 0x00,
  //! Wrong parameters were put into the primitive
  ZDO_INVALID_PARAMETERS_STATUS     = 0x01,
  //! Calling the primitive is not permitted
  ZDO_NOT_PERMITTED_STATUS          = 0x03,
  //! ZDO layer is busy and cannot execute the primitive
  ZDO_BUSY_STATUS                   = 0x04,
  //! No network was found
  ZDO_NO_NETWORKS_STATUS            = 0x05,
  //! There is a network with the same extended PANID
  ZDO_EXTPANID_ALREADY_EXIST_STATUS = 0x06,
  //! Unknown error
  ZDO_FAIL_STATUS                   = 0x07,
  ZDO_AUTHENTICATION_SUCCESS_STATUS = 0x08,
  ZDO_AUTHENTICATION_FAIL_STATUS    = 0x09,
  ZDO_SECURITY_SUCCESS_STATUS       = 0x0A,
  ZDO_SECURITY_FAIL_STATUS          = 0x0B,
  ZDO_SECURITY_NOT_SUPPORTED_STATUS = 0x0C,
  ZDO_CMD_COMPLETED_STATUS          = 0x0D,
  //! ZDP request is invalid
  ZDO_INVALID_REQUEST_STATUS        = 0x80,
  //! Requested device was not found
  ZDO_DEVICE_NOT_FOUND_STATUS       = 0x81,
  //! Unsupported endpoint of 0x00 or between 0xF1 and 0xFF was requested
  ZDO_INVALID_EP_STATUS             = 0x82,
  //! Requested endpoint has not been registered
  ZDO_NOT_ACTIVE_STATUS             = 0x83,
  //! Requested optional feature is not supported
  ZDO_NOT_SUPPORTED_STATUS          = 0x84,
  //! Timeout occured during the requested operation
  ZDO_TIMEOUT_STATUS                = 0x85,
  //! End device bind request is unsuccessful due to a failure to match any suitable clusters
  ZDO_NO_MATCH_STATUS               = 0x86,
  //! Unbind request is unsuccessful
  ZDO_NO_ENTRY_STATUS               = 0x88,
  //! Child descriptor is not available
  ZDO_NO_DESCRIPTOR_STATUS          = 0x89,
  //! Device does not have enough storage space
  ZDO_INSUFFICIENT_SPACE_STATUS     = 0x8A,
  ZDO_RESPONSE_WAIT_TIMEOUT_STATUS  = 0x8B,
  //! Device does not have enough table space
  ZDO_TABLE_FULL_STATUS             = 0x8C,
  //! Request is not authorized from this device
  ZDO_NOT_AUTHORIZED_STATUS         = 0x8D,
  //! Network parameters have been updated (channel, PanId, shortAddr...)
  ZDO_NWK_UPDATE_STATUS             = 0x8E,
  //! Device has joined/rejoined a network and data can be transmitted
  ZDO_NETWORK_STARTED_STATUS        = 0x8F,
  //! Device has lost connection with a parent and the stack tries rejoin by itself. In this case transmission should be stopped.
  ZDO_NETWORK_LOST_STATUS           = 0x90,
  //! Device has left a network. If autonetwork option is on, the stack will rejoin a network. Otherwise, an application should rejoin.
  ZDO_NETWORK_LEFT_STATUS           = 0x91,
  //! New device has joined a network as a child of this device
  ZDO_CHILD_JOINED_STATUS           = 0x92,
  //! Child has been removed from children list
  ZDO_CHILD_REMOVED_STATUS          = 0x93,
  //! User descriptor is changed event
  ZDO_USER_DESCRIPTOR_UPDATE_STATUS = 0x94,
  //! On the device with static addressing the conflict of network addresses has been detected
  ZDO_STATIC_ADDRESS_CONFLICT_STATUS = 0x95
} ZDO_Status_t;

/********************************************************************************//**
\brief Types of response to address request
***********************************************************************************/
enum
{
  SINGLE_RESPONSE_REQUESTTYPE   = 0x00,
  EXTENDED_RESPONSE_REQUESTTYPE = 0x01
};

/*!
\brief The ZDP clusters ID list.

The ZDP cluster ID determines the type of ZDP request/confirm
*/
enum
{
// Device and Service Discovery commands
  NWK_ADDR_CLID                = 0x0000,//!< Request for the 16-bit address of a remote device based on its known IEEE address.
  IEEE_ADDR_CLID               = 0x0001,//!< Request for the 64-bit IEEE address of a remote device based on its known 16-bit address.
  NODE_DESCRIPTOR_CLID         = 0x0002,//!< Request for the node descriptor of a remote device.
  POWER_DESCRIPTOR_CLID        = 0x0003,//!< Request for the power descriptor of a remote device.
  SIMPLE_DESCRIPTOR_CLID       = 0x0004,//!< Request for the simple descriptor of a remote device on the specified endpoint.
  ACTIVE_ENDPOINTS_CLID        = 0x0005,//!< Request for the list of endpoints on a remote device with simple descriptors.
  MATCH_DESCRIPTOR_CLID        = 0x0006,//!< Request for remote devices supporting a specific simple descriptor match criterion.
  COMPLEX_DESCRIPTOR_CLID      = 0x0010,//!< Request for the complex descriptor of a remote device.
  USER_DESCRIPTOR_CLID         = 0x0011,//!< Request for the user descriptor of a remote device.
  DISCOVERY_CASH_CLID          = 0x0012,//!< Request to locate a Primary Discovery Cache device on the network.
  DEVICE_ANNCE_CLID            = 0x0013,//!< Request to notify other ZigBee devices on the network that the device has joined or re-joined the network.
  USER_DESC_CONF_CLID          = 0x0014,//!< Command to configure the user descriptor on a remote device.
  SYSTEM_SERVER_DISCOVERY_CLID = 0x0015,//!< Request for the location of a particular system server or servers.
  DISCOVERY_STORE_CLID         = 0x0016,//!< Request for the storage of the device's discovery cache information on a Primary Discovery Cache device.
  NODE_DESC_STORE_CLID         = 0x0017,//!< Request for the storage of the device's Node Descriptor on a Primary Discovery Cache device.
  POWER_DESC_STORE_CLID        = 0x0018,//!< Request for the storage of the device's Descriptor on a Primary Discovery Cache device.
  ACTIVE_EP_STORE_CLID         = 0x0019,//!< Request for the storage of the device's list of Active Endpoints on a Primary Discovery Cache device.
  SIMPLE_DESC_STORE_CLID       = 0x001A,//!< Request for the storage of the device's list of Simple Descriptors on a Primary Discovery Cache device.
  REMOVE_NODE_CACHE_CLID       = 0x001B,//!< Command for removal of discovery cache information for a specified ZigBee end device from a Primary Discovery Cache device.
  FIND_NODE_CACHE_CLID         = 0x001C,//!< Request for a device on the network that holds discovery information for the device of interest.
  EXTENDED_SIMPLE_DESC_CLID    = 0x001D,//!< Request for the simple descriptor of a remote device on the specified endpoint, to be used with devices which support more active endpoints than can be returned by a single ::SIMPLE_DESCRIPTOR_CLID request.
  EXTENDED_ACTIVE_EP_CLID      = 0x001E,//!< Request for the list of endpoints on a remote device with simple descriptors, to be used with devices which support more active endpoints than can be returned by a single ::ACTIVE_ENDPOINTS_CLID request.
// Bind client manager commands
  END_DEVICE_BIND_CLID         = 0x0020,//!< Request generated from a Local Device wishing to perform End Device Bind with a Remote Device.
  BIND_CLID                    = 0x0021,//!< Request generated from a Local Device wishing to create a Binding Table entry for the source and destination addresses contained as parameters.
  UNBIND_CLID                  = 0x0022,//!< Request generated from a Local Device wishing to remove a Binding Table entry for the source and destination addresses contained as parameters.
  BIND_REGISTER_CLID           = 0x0023,//!< Request generated from a Local Device and sent to a primary binding table cache device to register that the local device wishes to hold its own binding table entries.
  REPLACE_DEVICE_CLID          = 0x0024,//!< Request sent to a primary binding table cache device to change all binding table entries which match OldAddress and OldEndpoint as specified.
  STORE_BCKUP_BIND_ENTRY_CLID  = 0x0025,//!< Request generated from a local primary binding table cache and sent to a remote backup binding table cache device to request backup storage of the entry.
  REMOVE_BCKUP_BIND_ENTRY_CLID = 0x0026,//!< Request generated from a local primary binding table cache and sent to a remote backup binding table cache device to request removal of the entry from backup storage.
  BACKUP_BIND_TABLE_CLID       = 0x0027,//!< Request generated from a local primary binding table cache and sent to the remote backup binding table cache device to request backup storage of its entire binding table.
  RECOVER_BIND_TABLE_CLID      = 0x0028,//!< Request generated from a local primary binding table cache and sent to a remote backup binding table cache device when it wants a complete restore of the binding table.
  BACKUP_SOURCE_BIND_CLID      = 0x0029,//!< Request generated from a local primary binding table cache and sent to a remote backup binding table cache device to request backup storage of its entire source table.
  RECOVER_SOURCE_BIND_CLID     = 0x002A,//!< Request generated from a local primary binding table cache and sent to the remote backup binding table cache device when it wants a complete restore of the source binding table.
// Network Management Client Services commands
  MGMT_NWK_DISC_CLID           = 0x0030,//!< Request generated from a Local Device requesting that the Remote Device execute a Scan to report back networks in the vicinity of the Local Device.
  MGMT_LQI_CLID                = 0x0031,//!< Request generated from a Local Device wishing to obtain a neighbor list for the Remote Device along with associated LQI values to each neighbor.
  MGMT_RTG_CLID                = 0x0032,//!< Request generated from a Local Device wishing to retrieve the contents of the Routing Table from the Remote Device.
  MGMT_BIND_CLID               = 0x0033,//!< Request generated from a Local Device wishing to retrieve the contents of the Binding Table from the Remote Device.
  MGMT_LEAVE_CLID              = 0x0034,//!< Request generated from a Local Device requesting that a Remote Device leave the network or to request that another device leave the network.
  MGMT_DIRECT_JOIN_CLID        = 0x0035,//!< Request generated from a Local Device requesting that a Remote Device permit a device designated by DeviceAddress to join the network directly.
  MGMT_PERMIT_JOINING_CLID     = 0x0036,//!< Request generated from a Local Device requesting that a remote device or devices allow or disallow association.
  MGMT_CACHE_CLID              = 0x0037,//!< Request The Mgmt_Cache_req is provided to enable ZigBee devices on the network to retrieve a list of ZigBee End Devices registered with a Primary Discovery Cache device.
  MGMT_NWK_UPDATE_CLID         = 0x0038 //!< Command provided to allow updating of network configuration parameters or to request information from devices on network conditions in the local operating environment.
};

/********************************************************************************//**
\brief Possible address modes
***********************************************************************************/
typedef enum
{
  SHORT_ADDR_MODE, //!< Short address
  EXT_ADDR_MODE //!< Extended address
} AddrMode_t;

#define  ZDO_MGMT_ED_SCAN_DUR_0  0x00     //!< Used as a value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_ED_SCAN_DUR_1  0x01     //!< Used as a value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_ED_SCAN_DUR_2  0x02     //!< Used as a value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_ED_SCAN_DUR_3  0x03     //!< Used as a value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_ED_SCAN_DUR_4  0x04     //!< Used as a value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_ED_SCAN_DUR_5  0x05     //!< Used as a value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_CHANNEL_CHANGE  0xFE    //!< Used as a special value for ZDO_MgmtNwkUpdateReq_t::scanDuration
#define  ZDO_MGMT_NWK_PARAMS_CHANGE  0xFF //!< Used as a special value for ZDO_MgmtNwkUpdateReq_t::scanDuration

/********************************************************************************//**
\brief Information about the addresses of a device.
***********************************************************************************/
typedef struct
{
  ShortAddr_t shortAddr; //!< Short address
  ExtAddr_t   extAddr; //!< Extended address
} NodeAddr_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_StartNetworkConf() function
***********************************************************************************/
typedef struct
{
  uint8_t       activeChannel; //!< Current channel the device has connected on.
  ShortAddr_t   shortAddr;     //!< Received short address.
  PanId_t       PANId;         //!< Received short PANId.
  uint64_t      extPANId;      //!< Received extended PANId if it was not determined during startup
  ShortAddr_t   parentAddr;    //!< Parent address
  ZDO_Status_t  status;        //!< Result status of network start
} ZDO_StartNetworkConf_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_StartNetworkReq() function
***********************************************************************************/
typedef struct
{
  ZDO_StartNetworkConf_t confParams;  //!< Parameters of the confirm being returned in ZDO_StartNetworkConf()
  void (*ZDO_StartNetworkConf)(ZDO_StartNetworkConf_t *conf); //!< The function called to confirm the request
} ZDO_StartNetworkReq_t;

/********************************************************************************//**
\brief Desribes the parameters of the ZDO_ResetNetworkConf() function
 ***********************************************************************************/
typedef struct
{
  ZDO_Status_t  status; //!< Result of the reset request
} ZDO_ResetNetworkConf_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_ResetNetworkReq() function
***********************************************************************************/
typedef struct
{
  ZDO_ResetNetworkConf_t confParams; //!< Parameters of the confirm being returned in ZDO_ResetNetworkConf()
  void (*ZDO_ResetNetworkConf)(ZDO_ResetNetworkConf_t *conf); //!< The function called to confirm the request
} ZDO_ResetNetworkReq_t;

/********************************************************************************//**
\brief This information is provided to enable ZigBee devices to report
the condition on local channels to a network manager. The scanned channel list is
the report of channels scanned and it is followed by a list of records, one for each
channel scanned, each record including one byte of the energy level measured
during the scan, or 0xff if there is too much interference on this channel.
***********************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  uint32_t        scannedChannels; //!< Bit mask of channels scanned by the request
  uint16_t        totalTransmissions; //!< Count of transmissions reported by the device
  uint16_t        transmissionsFailures; //!< Count of transmission failures reported by the device
  uint8_t         scannedChannelsListCount; //!< Number of records contained in the energyValues[] list
  uint8_t         energyValues[32]; /*! Results of energy measurements by channel.
Each value is within the range from 0 to 84. Actually measured input power
in dBm can be obtained by subtracting 91.*/
} EDScan_t;
END_PACK

/********************************************************************************//**
\brief This information is provided to inform an application about new network parameters
if a device rejoined a network.
***********************************************************************************/
typedef struct
{
  ShortAddr_t parentShortAddr; //!< Parent short address
  PanId_t     panId; //!< PAN ID of a network
  uint8_t     currentChannel; //!< Current channel
  ShortAddr_t shortAddr; //!< New short address
} NetworkInf_t;

/********************************************************************************//**
\brief This information is provided to notify application about network events.
***********************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  /*! The parameter shows the notification status and can be:
  ZDO_SUCCESS_STATUS,
  ZDO_INVALID_PARAMETERS_STATUS,
  ZDO_FAIL_STATUS,
  ZDO_RESPONSE_WAIT_TIMEOUT_STATUS,
  ZDO_NETWORK_STARTED_STATUS,
  ZDO_NETWORK_LEFT_STATUS,
  ZDO_NETWORK_LOST_STATUS,
  ZDO_CHILD_JOINED_STATUS,
  ZDO_CHILD_REMOVED_STATUS,
  ZDO_USER_DESCRIPTOR_UPDATE_STATUS,
  ZDO_STATIC_ADDRESS_CONFLICT_STATUS,
  ZDO_NWK_UPDATE_STATUS*/
  uint8_t status;
  union PACK
  {
    //! Conflicting address
    ShortAddr_t  conflictAddress;
    //! ED scan result
    EDScan_t     scanResult;
    //! Network information updated
    NetworkInf_t nwkUpdateInf;
    //! Address of joined/removed child
    NodeAddr_t   childAddr;
  };
} ZDO_MgmtNwkUpdateNotf_t;
END_PACK

/********************************************************************************//**
\brief Desribes the parameters of the LQI response
***********************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  uint8_t   neighborTableEntries;
  uint8_t   startIndex;
  uint8_t   neighborTableListCount;
  struct PACK
  {
    ExtPanId_t       extPanId;
    ExtAddr_t        extAddr;
    ShortAddr_t      networkAddr;
    uint8_t          deviceType : 2;
    uint8_t          rxOnWhenIdle : 2;
    uint8_t          relationship : 3;
    uint8_t          reserved1 : 1;
    uint8_t          permitJoining : 2;
    uint8_t          reserved2 : 6;
    uint8_t          depth;
    uint8_t          lqi;
  } neighborTableList[ZDP_NEIGBOR_TABLE_LIST_SIZE];
} ZDO_MgmtLqiResp_t;
END_PACK

/********************************************************************************//**
\brief Desribes the parameters of the LQI request
***********************************************************************************/
typedef struct
{
  uint8_t   startIndex;
} ZDO_MgmtLqiReq_t;

/********************************************************************************//**
\brief Desribes the parameters of the ZDO_SleepConf() function
***********************************************************************************/
typedef struct
{
  /*! Stack is ready to sleep if status is ZDO_SUCCESS_STATUS,
  stack is not ready to sleep if status is ZDO_BUSY_STATUS */
  ZDO_Status_t status;
} ZDO_SleepConf_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_SleepReq() function
***********************************************************************************/
typedef struct
{
  ZDO_SleepConf_t confirm; //!< Parameters of the confirm being returned in ZDO_SleepConf()
  void (*ZDO_SleepConf)(ZDO_SleepConf_t *conf); //!< The function called to confirm the request
} ZDO_SleepReq_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_WakeUp() function
***********************************************************************************/
typedef struct
{
  ZDO_Status_t status; //!< Result of the wakeup request
} ZDO_WakeUpConf_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_SleepReq() function
***********************************************************************************/
typedef struct
{
  ZDO_WakeUpConf_t confirm; //!< Parameters of the confirm being returned in ZDO_WakeUpConf()
  void (*ZDO_WakeUpConf)(ZDO_WakeUpConf_t *conf); //!< The function called to confirm the request
} ZDO_WakeUpReq_t;

/********************************************************************************//**
\brief This request is generated from a Local Device wishing to inquire as to the
16-bit address of the Remote Device based on its known IEEE address. The
destination addressing on this command shall be unicast or broadcast to all
devices for which macRxOnWhenIdle = TRUE.
***********************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  /*! The IEEE address to be matched by the Remote Device */
  ExtAddr_t ieeeAddrOfInterest;
  /*! Request type for this command:
  0x00  Single device response
  0x01  Extended response
  0x02-0xFF  reserved */
  uint8_t   reqType;
  /*! If the Request type for this command is
  Extended response, the StartIndex
  provides the starting index for the
  requested elements of the associated
  devices list*/
  uint8_t   startIndex;
} ZDO_NwkAddrReq_t;

/********************************************************************************//**
\brief This request is generated from a Local Device wishing to inquire as to the
64-bit IEEE address of the Remote Device based on their known 16-bit address.
The destination addressing on this command shall be unicast.
***********************************************************************************/
typedef struct PACK
{
  /*! NWK address that is used for IEEE address mapping. */
  ShortAddr_t nwkAddrOfInterest;
  /*! Request type for this command:
  0x00  Single device response
  0x01  Extended response
  0x02-0xff  reserved */
  uint8_t reqType;
  /*! If the Request type for this
  command is Extended response, the
  StartIndex provides the starting
  index for the requested elements of
  the associated devices list.*/
  uint8_t startIndex;
} ZDO_IeeeAddrReq_t;

/********************************************************************************//**
\brief This request is generated from a local device wishing to inquire
as to the node descriptor of a remote device. This command shall be unicast either
to the remote device itself or to an alternative device that contains the discovery
information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the node descriptor request
} ZDO_NodeDescReq_t;

/********************************************************************************//**
\brief This request is generated from a local device wishing to
inquire as to the power descriptor of a remote device. This command shall be
unicast either to the remote device itself or to an alternative device that contains
the discovery information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the power descriptor request
} ZDO_PowerDescReq_t;

/********************************************************************************//**
\brief This request is generated from a local device wishing to acquire
the list of endpoints on a remote device with simple descriptors. This command
shall be unicast either to the remote device itself or to an alternative device that
contains the discovery information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the active endpoints request
} ZDO_ActiveEPReq_t;

/********************************************************************************//**
\brief This request is generated from a local device wishing to
inquire as to the complex descriptor of a remote device. This command shall be
unicast either to the remote device itself or to an alternative device that contains
the discovery information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the complex descriptor request
} ZDO_ComplexDescReq_t;

/********************************************************************************//**
\brief This request is generated from a local device wishing to inquire
as to the user descriptor of a remote device. This command shall be unicast either
to the remote device itself or to an alternative device that contains the discovery
information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the user descriptor request
} ZDO_UserDescReq_t;

/********************************************************************************//**
\brief This is generated from a local device wishing to
configure the user descriptor on a remote device. This command shall be unicast
either to the remote device itself or to an alternative device that contains the
discovery information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the user descriptor setting request
  UserDescriptor_t userDescriptor; //!< The user descriptor of a device
} ZDO_UserDescSetReq_t;

/********************************************************************************//**
\brief This request is generated from a local device wishing to
inquire as to the simple descriptor of a remote device on a specified endpoint. This
command shall be unicast either to the remote device itself or to an alternative
device that contains the discovery information of the remote device.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the simple descriptor request
  Endpoint_t  endpoint; //!< The endpoint on the destination
} ZDO_SimpleDescReq_t;

/********************************************************************************//**
\brief This request is provided to enable ZigBee devices on the network to notify
other ZigBee devices that the device has joined or re-joined the network,
identifying the devices 64-bit IEEE address and new 16-bit NWK address, and
informing the Remote Devices of the capability of the ZigBee device. This
command shall be invoked for all ZigBee end devices upon join or rejoin. This
command may also be invoked by ZigBee routers upon join or rejoin as part of
NWK address conflict resolution. The destination addressing on this primitive is
broadcast to all devices for which macRxOnWhenIdle = TRUE.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrLocal; //!< NWK address for the Local Device
  ExtAddr_t   ieeeAddrLocal; //!< IEEE address for the Local Device
  MAC_CapabilityInf_t  macCapability; //!< Capability of the local device
} ZDO_DeviceAnnceReq_t;

/********************************************************************************//**
\brief This request is generated from a Local Device wishing to
discover the location of a particular system server or servers as indicated by the
ServerMask parameter. The destination addressing on this request is broadcast to
all devices for which macRxOnWhenIdle = TRUE
***********************************************************************************/
typedef struct PACK
{
  uint16_t serverMask; //!< Server mask field of the node descriptor
} ZDO_SystemServerDiscoveryReq_t;

#ifdef _BINDING_
/********************************************************************************//**
\brief ZDO Match Descriptor request primitive allows to find remote devices
 supporting a specific simple descriptor match criterion.
 ZigBee spec r17 Table 2.50 page 105.
***********************************************************************************/
typedef struct PACK
{
  /*! NWK address for the request.*/
  ShortAddr_t nwkAddrOfInterest;
  /*! Profile ID to be matched at the destination.*/
  ProfileId_t profileId;
  /*! The number of Input Clusters provided for matching within the InClusterList.*/
  uint8_t     numInClusters;
  /*! List of Input ClusterIDs to be used for matching; the InClusterList is the
  desired list to be matched by the Remote Device (the elements of the InClusterList
  are the supported output clusters of the Local Device).*/
  ClusterId_t inClusterList[MAX_REQUESTED_CLUSTER_NUMBER];
  /*! The number of Output Clusters provided for matching within OutClusterList.*/
  uint8_t     numOutClusters;
  /*! List of Output ClusterIDs to be used for matching; the OutClusterList is the
  desired list to be matched by the Remote Device (the elements of the OutClusterList
  are the supported input clusters of the Local Device).*/
  ClusterId_t outClusterList[MAX_REQUESTED_CLUSTER_NUMBER];
} ZDO_MatchDescReq_t;

/********************************************************************************//**
\brief (ClisterID = 0x0020) This request is generated from a Local Device wishing
to perform End Device with a Remote Device. The End Device Bind Request is generated,
typically based on some user action like a button press. The destination addressing
on this command shall be unicast, and the destination addressshall be that of the ZigBee
Coordinator.
***********************************************************************************/
typedef struct PACK
{
  /*! The address of the target for binding. This is a short address of the
  local device.*/
  ShortAddr_t bindingTarget;
  /*! The IEEE address of the device generating the request.*/
  ExtAddr_t   srcExtAddr;
  /*! The endpoint on the device generating the request.*/
  Endpoint_t  srcEndpoint;
  /*! ProfileID wich is to be matched between two End_Device_Bind_Req received
  at the ZigBee Coordinator within the timeout value pre-configured in the
  ZigBee Coordinator.*/
  ProfileId_t profileId;
  /*! The Number of Input Clusters provided for end device binding within the
  inClusterList.*/
  uint8_t     numInClusters;
  /*! List of Input ClusterIDs to be used for matching. The inClusterList is the
  desired list to be matched by the ZigBee Coordinator with the Remote Device's
  output clusters (the elements of the inClusterList are supported input
  clusters of the Local Device).*/
  ClusterId_t inClusterList[MAX_REQUESTED_CLUSTER_NUMBER];
  /*! The number of Output Clusters provided for matching within outClusterList.*/
  uint8_t     numOutClusters;
  /*! List of Output ClusterIDs to be used for matching. The outClusterList is
  the desired list to be matched by the ZigBee Coordinator with the Remote Device's
  input clusters (the elements of the outClusterList are supported output clusters
  of the Local Device).*/
  ClusterId_t outClusterList[MAX_REQUESTED_CLUSTER_NUMBER];
} ZDO_EndDeviceBindReq_t;

/********************************************************************************//**
\brief (ClusterID = 0x0021) This request is generated from a Local Device wishing
to create a Binding Table entry for the source and destination addresses contained
as parameters. The destination addressing on this command shall be unicast only,
and the destination address shall be SrcAddress itself.
***********************************************************************************/
typedef struct PACK
{
  /*! The IEEE address for the source.*/
  ExtAddr_t   srcAddr;
  /*! The source endpoint for the binding entry.*/
  Endpoint_t  srcEndpoint;
  /*! The identifier of the cluster on the source device that is bound to the
  destination */
  ClusterId_t clusterId;
  /*! The addressing mode for the destination address used in this command. This
  field can take one of the none-reserved values from the following list:
  0x00 = reserved
  0x01 = 16-bit group address for dstAddr and dstEndoint not present.
  0x02 = reserved
  0x03 = 64-bit extended address for dstAddr and dstEndpoint present
  0x04 - 0xff = reserved*/
  uint8_t dstAddrMode;
  /*! The destination address for the binding entry.*/
  union PACK
  {
    struct PACK
    {
      ExtAddr_t     dstExtAddr;
      /*! This field shall be present only if the dstAddrMode field has a value of
      0x03 and, if present, shall be the destination endpoint for the binding entry.*/
      Endpoint_t    dstEndpoint;
    };
    ShortAddr_t     dstGroupAddr;
  };
} ZDO_BindReq_t;

/********************************************************************************//**
\brief (ClusterID = 0x0022) This request is generated from a Local Device wishing
to remove a Binding Table entry for the source and destination addresses contained
as parameters. The destination addressing on this command shall be unicast only,
and the destination address shall be SrcAddress itself.
***********************************************************************************/
typedef struct PACK
{
  /*! The IEEE address for the source.*/
  ExtAddr_t   srcAddr;
  /*! The source endpoint for the binding entry.*/
  Endpoint_t  srcEndpoint;
  /*! The identifier of the cluster on the source device that is bound to the
  destination */
  ClusterId_t clusterId;
  /*! The addressing mode for the destination address used in this command. This
  field can take one of the none-reserved values from the following list:
  0x00 = reserved
  0x01 = 16-bit group address for dstAddr and dstEndoint not present.
  0x02 = reserved
  0x03 = 64-bit extended address for dstAddr and dstEndpoint present
  0x04 - 0xff = reserved*/
  uint8_t dstAddrMode;
  /*! The destination address for the binding entry.*/
  union PACK
  {
    struct PACK
    {
      ExtAddr_t     dstExtAddr;
      /*! This field shall be present only if the dstAddrMode field has a value of
      0x03 and, if present, shall be the destination endpoint for the binding entry.*/
      Endpoint_t    dstEndpoint;
    };
    ShortAddr_t     dstGroupAddr;
  };
} ZDO_UnbindReq_t;


#endif // _BINDING_

/********************************************************************************//**
\brief This request is generated from a Local Device requesting that a Remote
Device leave the network or to request that another device leave the network. The
Mgmt_Leave_req is generated by a management application which directs the
request to a Remote Device where the NLME-LEAVE.request is to be executed
using the parameter supplied by Mgmt_Leave_req.
***********************************************************************************/
typedef struct PACK
{
  ExtAddr_t deviceAddr; //!< IEEE address
  uint8_t   reserved : 6; //!< Reserved; can not be changed by user.
  /*! This field has a value of 1 if the
  device being asked to leave the
  network is also asked to
  remove all its child devices, if any.
  Otherwise, it has a value of 0.*/
  uint8_t   removeChildren : 1;
  /*! This field has a value of 1 if the
  device being asked to leave from the
  current parent is requested to rejoin
  the network. Otherwise, it has a
  value of 0.*/
  uint8_t   rejoin : 1;
} ZDO_MgmtLeaveReq_t;

/********************************************************************************//**
\brief This request is generated from a Local Device requesting that
a remote device or devices allow or disallow association.
***********************************************************************************/
typedef struct PACK
{
  /*! Time span in seconds during
  which the ZigBee coordinator or router
  will allow associations. The value 0x00
  or 0xff indicate that permission is, respectively,
  disabled or enabled permanently.*/
  uint8_t permitDuration;
  /*! If this is set to 0x01 and the remote device is
  the Trust Center, the command affects the
  Trust Center authentication policy as
  described in the sub-clauses below; If this is
  set to 0x00, there is no effect on the Trust
  Center.*/
  uint8_t tcSignificance;
} ZDO_MgmtPermitJoiningReq_t;

/********************************************************************************//**
\brief This command is provided to allow updating of network configuration parameters
or to request information from devices on network conditions in the local
operating environment. The destination addressing on this primitive shall be
unicast or broadcast to all devices for which macRxOnWhenIdle = TRUE.
***********************************************************************************/
typedef struct PACK
{
  /*! The five most significant bits (b27,... b31) are reserved. The 27 least
  significant bits (b0, b1,... b26) indicate which channels are to be scanned
  (1 = scan, 0 = do not scan) for each of the 27 valid channels*/
  uint32_t    scanChannels;
  /*! Possible values are:\n
::ZDO_MGMT_ED_SCAN_DUR_0 (0x00) to ::ZDO_MGMT_ED_SCAN_DUR_5 (0x05) - request
to perform an ED scan with duration depending exponentially on the parameter value;\n
::ZDO_MGMT_CHANNEL_CHANGE (0xFE) - request to change the working channel to
the one specified by the ZDO_MgmtNwkUpdateReq_t::scanChannels bitmask;\n
::ZDO_MGMT_NWK_PARAMS_CHANGE (0xFF) - request to change the device
nwkUpdateId and nwkManagerAddr values to those contained in the request.\n
Other values are invalid.*/
  uint8_t     scanDuration;
  union PACK
  {
    /*! This field represents the number of
    energy scans to be conducted and reported.
    This field shall be present only if the
    ZDO_MgmtNwkUpdateReq_t::scanDuration is within the range of
    0x00 to 0x05.*/
    uint8_t     scanCount;
    /*! The value of the nwkUpdateId
    contained in this request. This value
    is set by the Network Channel
    Manager prior to sending the message.
    This field shall only be present if the
    ZDO_MgmtNwkUpdateReq_t::scanDuration is 0xFE or 0xFF.*/
    uint8_t     nwkUpdateId;
  };
  /*! This field shall be present only if the ZDO_MgmtNwkUpdateReq_t::scanDuration
  is set to 0xFF, and, if present, indicates the NWK address
  for the device with the Network Manager bit set in its Node Descriptor.*/
  ShortAddr_t nwkManagerAddr;
} ZDO_MgmtNwkUpdateReq_t;

/********************************************************************************//**
\brief This command is generated by a Remote Device in response to a
NWK_addr_req command inquiring as to the NWK address of the Remote Device
or the NWK address of an address held in a local discovery cache.
The destination addressing on this command is unicast.
***********************************************************************************/
typedef struct PACK
{
  /*! 64-bit address for the Remote Device.*/
  ExtAddr_t   ieeeAddrRemote;
  /*! 16-bit address for the Remote Device.*/
  ShortAddr_t nwkAddrRemote;
  /*! Count of the number of 16-bit short addresses to follow.
  If the RequestType in the request is Extended Response
  and there are no associated devices on the Remote
  Device, this field shall be set to 0.
  If an error occurs or the RequestType in the request is
  for a Single Device Response, this field shall not
  be included in the frame.*/
  uint8_t     numAssocDev;
  /*! Starting index into the list of associated devices for this report.
  If the RequestType in the request is Extended Response and there are no associated
  devices on the Remote Device, this field shall not be included in the frame.
  If an error occurs or the RequestType in the request is for a Single Device
  Response, this field shall not be included in the frame.*/
  uint8_t     startIndex;
  /*! A list of 16-bit addresses, one corresponding to each
  associated device to Remote Device; The number of 16-bit
  network addresses contained in this field is specified in the
  NumAssocDev field.
  If the RequestType in the request is Extended Response
  and there are no associated devices on the Remote
  Device, this field shall not be included in the frame.
  If an error occurs or the RequestType in the request is
  for a Single Device Response, this field shall not
  be included in the frame.*/
  ShortAddr_t nwkAddrAssocDevList[ZDP_ADDR_LIST_SIZE];
} ZDO_NwkAddrResp_t;

/********************************************************************************//**
\brief This command is generated by a Remote Device in response to an
IEEE_addr_req command inquiring as to the 64-bit IEEE address of the Remote
Device or the 64-bit IEEE address of an address held in a local discovery cache.
The destination addressing on this command shall be unicast.
***********************************************************************************/
typedef struct PACK
{
  /*! 64-bit address for the Remote Device.*/
  ExtAddr_t   ieeeAddrRemote;
  /*! 16-bit address for the Remote Device.*/
  ShortAddr_t nwkAddrRemote;
  /*! Count of the number of 16-bit short addresses to follow.
  If the RequestType in the request is Extended
  Response and there are no associated devices on the
  Remote Device, this field shall be set to 0.
  If an error occurs or the RequestType in the
  request is for a Single Device Response, this
  field shall not be included in the frame.*/
  uint8_t     numAssocDev;
  /*! Starting index into the list of associated devices for this report.
  If the RequestType in the request is Extended
  Response and there are no associated devices on the
  Remote Device, this field shall not be included in the frame.
  If an error occurs or the RequestType in the request is for a Single
  Device Response, this field shall not be included in the frame.*/
  uint8_t     startIndex;
  /*! A list of 16-bit addresses, one corresponding to each
  associated device to Remote Device; The number of 16-bit network
  addresses contained in this field is specified in the NumAssocDev field.
  If the RequestType in the request is Extended Response and there are no
  associated devices on the Remote Device, this field
  shall not be included in the frame.
  If an error occurs or the RequestType in the request is for a Single
  Device Response, this field shall not be included in the frame*/
  ShortAddr_t nwkAddrAssocDevList[ZDP_ADDR_LIST_SIZE];
} ZDO_IeeeAddrResp_t;

/********************************************************************************//**
\brief This command is generated by a remote device in response to a
Node_Desc_req directed to the remote device. This command shall be unicast to
the originator of the Node_Desc_req command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t      nwkAddrOfInterest; //!< NWK address of the node descriptor request
  NodeDescriptor_t nodeDescriptor; //!< Node descriptor of the device
} ZDO_NodeDescResp_t;

/********************************************************************************//**
\brief This command is generated by a remote device in response to a
Power_Desc_req directed to the remote device. This command shall be unicast to
the originator of the Power_Desc_req command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t       nwkAddrOfInterest; //!< NWK address of the power descriptor request
  PowerDescriptor_t powerDescriptor; //!< Power descriptor of the device
} ZDO_PowerDescResp_t;

/********************************************************************************//**
\brief This command is generated by a remote device in response to a
Complex_Desc_req directed to the remote device. This command shall be unicast
to the originator of the Complex_Desc_req command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t      nwkAddrOfInterest; //!< NWK address of the complex descriptor request
} ZDO_ComplexDescResp_t;

/********************************************************************************//**
\brief The User_Desc_rsp is generated by a remote device in response to a
User_Desc_req directed to the remote device. This command shall be unicast to
the originator of the User_Desc_req command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t      nwkAddrOfInterest; //!< NWK address of the user descriptor request
  UserDescriptor_t  userDescriptor; //!< The user descriptor of a device
} ZDO_UserDescResp_t;

/********************************************************************************//**
\brief This command is generated by a remote device in response to a
User_Desc_set directed to the remote device. This command shall be unicast to
the originator of the User_Desc_set command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t      nwkAddrOfInterest; //!< NWK address of the user descriptor setting request
} ZDO_UserDescConfResp_t;

/********************************************************************************//**
\brief This command is generated by a remote device in response to an
Active_EP_req directed to the remote device. This command shall be unicast to
the originator of the Active_EP_req command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address of the active endpoints request
  uint8_t     activeEPCount; //!< Count of active endpoints on the remote device.
  uint8_t     activeEPList[MAX_ACTIVE_EP_NUMBER];//!< List of active endpoint Ids.
} ZDO_ActiveEPResp_t;

/********************************************************************************//**
\brief The simple descriptor contains information specific to each endpoint contained in
this node. The simple descriptor is mandatory for each endpoint present in the node.
***********************************************************************************/
typedef struct PACK
{
  /*! The endpoint field of the simple descriptor is eight bits in length and specifies the
  endpoint within the node to which this description refers. Applications shall only
  use endpoints 1-240.*/
  Endpoint_t   endpoint;
  /*! The application profile identifier field of the simple descriptor is sixteen bits in
  length and specifies the profile that is supported on this endpoint. Profile
  identifiers shall be obtained from the ZigBee Alliance.*/
  ProfileId_t  AppProfileId;
  /*! The application device identifier field of the simple descriptor is sixteen bits in
  length and specifies the device description supported on this endpoint. Device
  description identifiers shall be obtained from the ZigBee Alliance.*/
  uint16_t     AppDeviceId;
  /*! The application device version field of the simple descriptor is four bits in length
  and specifies the version of the device description supported on this endpoint.*/
  uint8_t      AppDeviceVersion : 4;
  uint8_t      Reserved         : 4;
  /*! The application input cluster count field of the simple descriptor is eight bits in
  length and specifies the number of input clusters, supported on this endpoint, that
  will appear in the application input cluster list field. If the value of this field is
  zero, the application input cluster list field shall not be included.*/
  uint8_t      AppInClustersCount;
  /*! The application input cluster list of the simple descriptor is 16*i bits in length,
  where i is the value of the application input cluster count field. This field specifies
  the list of input clusters supported on this endpoint, for use during the service
  discovery and binding procedures.
  The application input cluster list field shall be included only if the value of the
  application input cluster count field is greater than zero.*/
  ClusterId_t  AppInClustersList[MAX_REQUESTED_CLUSTER_NUMBER];
  /*! The application output cluster count field of the simple descriptor is eight bits in
  length and specifies the number of output clusters, supported on this endpoint, that
  will appear in the application output cluster list field. If the value of this field is
  zero, the application output cluster list field shall not be included.*/
  uint8_t      AppOutClustersCount;
  /*! The application output cluster list of the simple descriptor is 16*o bits in length,
  where o is the value of the application output cluster count field. This field
  specifies the list of output clusters supported on this endpoint, for use during the
  service discovery and binding procedures.
  The application output cluster list field shall be included only if the value of the
  application output cluster count field is greater than zero.*/
  ClusterId_t  AppOutClustersList[MAX_REQUESTED_CLUSTER_NUMBER];

} ZdpSimpleDescriptor_t;

/********************************************************************************//**
\brief This command is generated by a remote device in response to a
Simple_Desc_req directed to the remote device. This command shall be unicast to
the originator of the Simple_Desc_req command.
***********************************************************************************/
typedef struct PACK
{
  ShortAddr_t           nwkAddrOfInterest; //!< NWK address of the simple descriptor request
  uint8_t               length; //!< Length in bytes of the Simple Descriptor to follow.
  ZdpSimpleDescriptor_t simpleDescriptor; //!<The simple descriptor itself
} ZDO_SimpleDescResp_t;

/********************************************************************************//**
\brief This command is generated from Remote Devices on receipt
of a System_Server_Discovery_req primitive if the parameter matches the Server
Mask field in its node descriptor. If there is no match, the
System_Server_Discovery_req shall be ignored and no response given. Matching
is performed by masking the ServerMask parameter of the
System_Server_Discovery_req with the Server Mask field in the node descriptor.
This command shall be unicast to the device which sent
System_Server_Discovery_req with Acknowledge request set in TxOptions. The
parameter ServerMask contains the bits in the parameter of the request which
match the server mask in the node descriptor.
***********************************************************************************/
typedef struct PACK
{
  uint16_t      serverMask; //!< The server mask field of the node descriptor
} ZDO_SystemServerDiscoveryResp_t;

#ifdef _BINDING_
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest;
  uint8_t     matchLength;
  uint8_t     matchList[MAX_REQUESTED_CLUSTER_NUMBER];
} ZDO_MatchDescResp_t;

/********************************************************************************//**
\brief (ClusterID = 0x8020) This response is generated by the ZigBee Coordinator
in response to End Device Bind Request and contains the status of the request.
This command shall be unicast to each device involved in the bind attempt, using
acknowledged data sevice.
***********************************************************************************/
typedef struct PACK
{
  /*! The status of the End Device Bind Request command.*/
  uint8_t status;
} ZDO_EndDeviceBindResp_t;

/********************************************************************************//**
\brief (ClusterID = 0x8021) This response is generated in response to
Bind Request command and contains the status of the request.
***********************************************************************************/
typedef struct PACK
{
  /*! The status of the End Device Bind Request command.*/
  uint8_t status;
} ZDO_BindResp_t;

/********************************************************************************//**
\brief (ClusterID = 0x8022) This response is generated in response to
Unbind Request command and contains the status of the request.
***********************************************************************************/
typedef struct PACK
{
  /*! The status of the End Device Bind Request command.*/
  uint8_t status;
} ZDO_UnbindResp_t;
#endif // _BINDING_

/********************************************************************************//**
\brief This struct contains response to one of the ZDP requests
***********************************************************************************/
typedef struct PACK
{
  uint8_t seqNum; //!< Sequence number of a ZDP command
  // user part
  uint8_t status; //!< Result of a ZDP request. Is interpreted as ::ZDO_Status_t.
  union PACK
  {
    ZDO_NwkAddrResp_t               nwkAddrResp; //!< NWK address response
    ZDO_IeeeAddrResp_t              ieeeAddrResp; //!< IEEE address response
    ZDO_NodeDescResp_t              nodeDescResp; //!< Node descriptor response
    ZDO_PowerDescResp_t             powerDescResp; //!< Power descriptor response
    ZDO_SimpleDescResp_t            simpleDescResp; //!< Simple descriptor response
    ZDO_ComplexDescResp_t           complexDescResp; //!< Complex descriptor response
    ZDO_UserDescResp_t              userDescResp; //!< User descriptor response
    ZDO_ActiveEPResp_t              activeEPResp; //!< Active endpoint response
    ZDO_UserDescConfResp_t          userDescConfResp; //!< User descriptor setting confirmation
    ZDO_SystemServerDiscoveryResp_t systemServerDiscoveryResp; //!< System server discovery response
#ifdef _BINDING_
    ZDO_MatchDescResp_t             matchDescResp;      //!< Match descriptor response
    ZDO_EndDeviceBindResp_t         endDeviceBindResp;  //!< End Device Bind Response
    ZDO_BindResp_t                  bindResp;           //!< Bind Response
    ZDO_UnbindResp_t                unbindResp;         //!<Unbind Response
#endif // _BINDING_
    ZDO_MgmtNwkUpdateNotf_t         mgmtNwkUpdateNotf; //!< Network update notification
    ZDO_MgmtLqiResp_t               mgmtLqiResp; //!< LQI response
  };
} ZDO_ZdpRespFrame_t;

/********************************************************************************//**
\brief This struct contains one of the ZDP requests
***********************************************************************************/
typedef struct PACK
{
  uint8_t seqNum; //!< Sequence number of a ZDP command
  // user part
  union PACK
  {
    ZDO_NwkAddrReq_t               nwkAddrReq; //!< NWK address request
    ZDO_IeeeAddrReq_t              ieeeAddrReq; //!< IEEE address request
    ZDO_NodeDescReq_t              nodeDescReq; //!< Node descriptor request
    ZDO_PowerDescReq_t             powerDescReq; //!< Power descriptor request
    ZDO_SimpleDescReq_t            simpleDescReq; //!< Simple descriptor request
    ZDO_DeviceAnnceReq_t           deviceAnnce; //!< Device_annce request
    ZDO_ActiveEPReq_t              activeEPReq; //!< Active endpoint request
    ZDO_ComplexDescReq_t           complexDescReq; //!< Complex descriptor request (not supported yet)
    ZDO_UserDescReq_t              userDescReq; //!< User descriptor request (not supported yet)
    ZDO_UserDescSetReq_t           userDescSetReq; //!< User descriptor setting (not supported yet)
    ZDO_SystemServerDiscoveryReq_t systemServerDiscoveryReq; //!< System server discovery request
#ifdef _BINDING_
    ZDO_MatchDescReq_t             matchDescReq;      //!< Match descriptor request
    ZDO_EndDeviceBindReq_t         endDeviceBindReq;  //!< End Device Bind Request
    ZDO_BindReq_t                  bindReq;           //!< Bind Request
    ZDO_UnbindReq_t                unbindReq;         //!<Unbind Request
#endif // _BINDING_
    ZDO_MgmtLeaveReq_t             mgmtLeaveReq; //!< Leave request
    ZDO_MgmtPermitJoiningReq_t     mgmtPermitJoiningReq; //!< Permit joining request
    ZDO_MgmtNwkUpdateReq_t         mgmtNwkUpdateReq; //!< Network update request
    ZDO_MgmtNwkUpdateNotf_t        mgmtNwkUpdateNotf; //!< Network update notification
    ZDO_MgmtLqiReq_t               mgmtLqiReq; //!< LQI request
  };
} ZDO_ZdpReqFrame_t;

/********************************************************************************//**
\brief Frame for transmission one of the ZDP requests
***********************************************************************************/
typedef struct PACK
{
  uint8_t header[APS_ASDU_OFFSET];
  union PACK
  {
    ZDO_ZdpRespFrame_t respPayload;
    ZDO_ZdpReqFrame_t  reqPayload;
  };
  uint8_t footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET];
} ZDO_ZdpFrame_t;
END_PACK

/********************************************************************************//**
\brief ZDP response
***********************************************************************************/
typedef struct
{
  AddrMode_t     srcAddrMode; //!< Source address mode, either short or extended
  union
  {
    ShortAddr_t  srcNwkAddr; //!< Short source address
    ExtAddr_t    srcExtAddr; //!< Extended source address
  };
  ZDO_ZdpRespFrame_t respPayload; //!< Response frame
} ZDO_ZdpResp_t;

/********************************************************************************//**
\brief ZDP request. Describes the parameters of the ZDO_ZdpReq() function.
***********************************************************************************/
typedef struct
{
  // Service fields
  struct
  {
    void *next;
    uint16_t ttl;
    uint8_t state;
    uint8_t seqNumCopy;  //used to prevent seq number encription
  } service;

  // Address fields
  uint16_t   reqCluster; //!< Requested cluster
  AddrMode_t dstAddrMode; //!< Destination address mode
  union
  {
    ShortAddr_t  dstNwkAddr; //!< Destination short address
    ExtAddr_t    dstExtAddr;//!< Destination extended address
  };
  // ZDP frame for sending out
  ZDO_ZdpFrame_t req; //!< ZDP request parameters
  //Callback and Response
  void (*ZDO_ZdpResp)(ZDO_ZdpResp_t *zdpResp); //!< Response callback
  ZDO_ZdpResp_t resp; //!< ZDP response parameters
} ZDO_ZdpReq_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_LqiRssiReq() function
***********************************************************************************/
typedef struct
{
  ShortAddr_t  nodeAddr; //!< Address of the requested node
  uint8_t      lqi; /*! Pointer to the memory allocated for LQI.
  The range of the LQI value is from 0 to 255.*/
  int8_t      rssi; /*! Pointer to the memory allocated for RSSI.
  The RSSI value range is different for various radio chips.
  RF230A, RF230B, RF212: from -91 dBm to -7 dBm,
  RF231: from -90 dBm to -7 dBm */
} ZDO_GetLqiRssi_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_ChildrenAddrReq() function
***********************************************************************************/
typedef struct
{
  uint8_t childrenCount; //!< Number of children
  NodeAddr_t *childrenTable; //!< Pointer to the memory allocated for children information
} ZDO_GetChildrenAddr_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_SetTxPowerConf() function
***********************************************************************************/
typedef struct
{
  ZDO_Status_t status; //!< Result of transmitter power setting
} ZDO_SetTxPowerConf_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_SetTxPowerReq() function
***********************************************************************************/
typedef struct
{
  uint8_t txPower; /*! Transmitter power to be set (dBm).
Valid range is hardware-dependent: for AT86RF230 RF part, it is from 0xEF to 0x03 (-17 to 3).
For AT86RF212 RF part, it is from 0xF5 to 0x0B (-11 to 11). */
  void (* ZDO_SetTxPowerConf)(ZDO_SetTxPowerConf_t *conf); //!< The function called to confirm the request
  ZDO_SetTxPowerConf_t confirm; //!< Parameters of the confirm being returned in ZDO_SetTxPowerConf()
} ZDO_SetTxPowerReq_t;

/********************************************************************************//**
\brief List of network status
***********************************************************************************/
typedef enum
{
  ZDO_IN_NETWORK_STATUS, //!< device is in the network
  ZDO_OUT_NETWORK_STATUS //!< device is out of the network
} ZDO_NwkStatus_t;

/********************************************************************************//**
\brief Describes the parameters of the ZDO_GetNeibAmount() function
***********************************************************************************/
typedef struct
{
  uint8_t routersAmount; //!< Amount of routers in the neighbor table
  uint8_t childrenAmount; //!< Amount of children in the neighbor table
} ZDO_GetNeibAmount_t;

/********************************************************************************//**
\brief Describes neighbor table entry
***********************************************************************************/
typedef struct
{
  ShortAddr_t           shortAddr; //!< Short address of the node
  ExtAddr_t             extAddr; //!< Extended address of the node
  DeviceType_t          deviceType; //!< Type of the node
  uint8_t               lqi; //!< LQI value for the node
  int8_t                rssi; //!< RSSI value for the node
  bool                  rxOnWhenIdle; //!< Idle portions of the node
  Relationship_t        relationship; //!< Relationship of the node
  ExtPanId_t            extPanId; //!< Extended PAN identifier of the node
  uint8_t               logicalChannel; //!< Logical channel of the node
  uint8_t               depth; //!< Depth of the node
  bool                  permitJoining; //!< Permit joining of the node
  bool                  potentialParent; //!< Potential parent of the node
} ZDO_Neib_t;

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
typedef struct
{
  ZDO_Status_t status;
} ZDO_EndToEndAppKeyConf_t;

typedef struct
{
  ExtAddr_t deviceAddr;
  void (*ZDO_EndToEndAppKeyConf)(ZDO_EndToEndAppKeyConf_t *conf);
  ZDO_EndToEndAppKeyConf_t confirm;
} ZDO_EndToEndAppKeyReq_t;
#endif // _HIGH_SECURITY_
#endif // _SECURITY_

/************************************************************************************
  Primitives declarations.
 ***********************************************************************************/

/*********************************************************************************//**
\brief Starts network for coordinator and joins the network for router.

This function forms a network for coordinator and joins an existing network for router or end device.

\param[in] startingParams - Determines the network parameters for join and formation
************************************************************************************/
void ZDO_StartNetworkReq(ZDO_StartNetworkReq_t *startingParams);

/**********************************************************************************//**
\brief Resets the stack without any commands to the network

This function resets the stack to default state. No data is send to the network.

\param[in] resetParams - Determines the parameters of the request
**************************************************************************************/
void ZDO_ResetNetworkReq(ZDO_ResetNetworkReq_t *resetParams);

/**********************************************************************************//**
\brief Indicates about network parameters update.

 The function should be defined by an application.
 It is called when the device has resolved address/panid conflict or rejoined the network

\param[out] nwkParams - Describes the reason of network update and new parameters.
**************************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t * nwkParams);

/*************************************************************************************//**
\brief Puts the device to sleep mode.

This function can be used only when the active period in Config Server is set to 0.
The time of sleep period is determined by CS_END_DEVICE_SLEEP_PERIOD in Config Server.

\param[in] req - Determines the sleep parameters.
******************************************************************************************/
void ZDO_SleepReq(ZDO_SleepReq_t *req);

/**************************************************************************************//**
\brief Indicates to an application that the stack is ready to sleep.

After this function the stack is waiting for response. An application should
stop and close all HW activities, sending data and commands to the stack and
wait all confirmations from the stack, after which the application should call
ZDO_SleepResp.
*****************************************************************************************/
void ZDO_SleepInd(void);

/*************************************************************************************//**
\brief Responds to the stack that an application is ready to sleep

The function should be called in response to ZDO_SleepInd. It can be called
only after stopping all HW and stack activities. On receiving this function call,
stack goes to sleep mode.
*****************************************************************************************/
void ZDO_SleepResp(void);

/*************************************************************************************//**
\brief Indicates to an application that the stack sleep timer has fired.

If the stack is in sleep mode, it wakes up and is ready to work.
Application can continue its activities.
******************************************************************************************/
void ZDO_WakeUpInd(void);

/*************************************************************************************//**
\brief Forces the stack to wake up from the sleep mode

This function is used by an application when the sleep timer is not used and
an application is woken up from sleep mode by an external interrupt.

\param[in] req - Determines the parameters of the wakeup request
******************************************************************************************/
void ZDO_WakeUpReq(ZDO_WakeUpReq_t *req);

/*************************************************************************************//**
\brief Send ZDP request

This function is used by an application to send ZDP request.

\param[in] zdpReq - Determines the parameters of the ZDP request
******************************************************************************************/
void ZDO_ZdpReq(ZDO_ZdpReq_t *zdpReq);

/*************************************************************************************//**
\brief Request of LQI and RSSI

This function requests LQI and RSSI for a remote node whose address is
contained in ZDO_GetLqiRssi_t::nodeAddr.
If called for an unknown node (i.e. with no link established to it), will return zeros.

\param[in] lqiRssi - Determines the parameters of the request.
******************************************************************************************/
void ZDO_GetLqiRssi(ZDO_GetLqiRssi_t *lqiRssi);

/*************************************************************************************//**
\brief Request of parent information

This function requests parent information of the node.

\param[in] parentAddr - Determines the parameters of the request.
******************************************************************************************/
void ZDO_GetParentAddr(NodeAddr_t *parentAddr);

/*************************************************************************************//**
\brief Request of children information

This function requests children information of the node.

\param[in] childrenAddr - Determines the parameters of the request.
******************************************************************************************/
void ZDO_GetChildrenAddr(ZDO_GetChildrenAddr_t *childrenAddr);

/*************************************************************************************//**
\brief Setting of tx power

This function sets tx power.

\param[in] req - Determines the parameters of the request.
******************************************************************************************/
void ZDO_SetTxPowerReq(ZDO_SetTxPowerReq_t *req);

/*************************************************************************************//**
\brief Gets the network status

This function returns network status.

\return - network status
******************************************************************************************/
ZDO_NwkStatus_t ZDO_GetNwkStatus(void);

/*************************************************************************************//**
\brief Gets neighbor routers and children amount

\param[out] amount - routers and children amount information
******************************************************************************************/
void ZDO_GetNeibAmount(ZDO_GetNeibAmount_t *amount);

/*************************************************************************************//**
\brief Gets the neighbor table

\param[out] table - neighbor table
******************************************************************************************/
void ZDO_GetNeibTable(ZDO_Neib_t *table);

/*************************************************************************************//**
\brief Start sending sync requests

\return - ZDO status. The primitive returns one of following values:
   - ZDO_SUCCESS_STATUS
   - ZDO_BUSY_STATUS
******************************************************************************************/
ZDO_Status_t  ZDO_StartSyncReq(void);

/*************************************************************************************//**
\brief Stop sending sync requests

\return - ZDO status. The primitive returns one of following values:
   - ZDO_SUCCESS_STATUS
   - ZDO_INVALID_REQUEST_STATUS
******************************************************************************************/
ZDO_Status_t  ZDO_StopSyncReq(void);

#endif  /* _ZDO_H */


