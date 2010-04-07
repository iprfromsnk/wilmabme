/*************************************************************************//**
  \file aps.h

  \brief The header file describes the public APS interface and APS types

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    06.06.07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APS_H
#define _APS_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <configServer.h>
#include <types.h>
#include <nwk.h>
#include <appFramework.h>
#include <macAddr.h>


/******************************************************************************
                   Define(s) section
******************************************************************************/

// \cond internal
#ifndef APS_MAX_TRANSMISSION_WINDOW_SIZE
#define APS_MAX_TRANSMISSION_WINDOW_SIZE        3
#endif
// \endcond

#ifndef _HIGH_SECURITY_
/*************************************************************************//**
  \brief Max APS header size
*****************************************************************************/
#define APS_MAX_DATA_FRAME_HEADER_LENGTH  12

/*************************************************************************//**
  \brief Max APS footer size
*****************************************************************************/
#define APS_MAX_DATA_FRAME_FOOTER_LENGTH  0
#else // _HIGH_SECURITY_
/*************************************************************************//**
  \brief Max APS header size
*****************************************************************************/
#define APS_MAX_DATA_FRAME_HEADER_LENGTH  (12 + 6) /*6 bytes - auxiliary header*/

/*************************************************************************//**
  \brief Max APS footer size
*****************************************************************************/
  #if (CS_SECURITY_LEVEL == 0x05)
    #define APS_MAX_DATA_FRAME_FOOTER_LENGTH  4        /*4 bytes - Message Integrity Code (MIC)*/
  #elif (CS_SECURITY_LEVEL == 0x06)
    #define APS_MAX_DATA_FRAME_FOOTER_LENGTH  8        /*8 bytes - Message Integrity Code (MIC)*/
  #elif (CS_SECURITY_LEVEL == 0x07)
    #define APS_MAX_DATA_FRAME_FOOTER_LENGTH  16       /*15 bytes - Message Integrity Code (MIC)*/
  #endif // SECURITY_LEVEL parsing

#endif // _HIGH_SECURITY_

/*************************************************************************//**
  \brief Max size of APS payload
*****************************************************************************/
#define APS_MAX_ASDU_SIZE           (NWK_MAX_NSDU_SIZE - APS_MAX_DATA_FRAME_HEADER_LENGTH - APS_MAX_DATA_FRAME_FOOTER_LENGTH)

/*************************************************************************//**
  \brief Size of the reserved header in the data frame
*****************************************************************************/
#define APS_ASDU_OFFSET             (NWK_NSDU_OFFSET + APS_MAX_DATA_FRAME_HEADER_LENGTH)

/*************************************************************************//**
  \brief Size of the reserved part in the data frame
*****************************************************************************/
#define APS_AFFIX_LENGTH            (APS_MAX_DATA_FRAME_HEADER_LENGTH + APS_MAX_DATA_FRAME_FOOTER_LENGTH + NWK_AFFIX_LENGTH)

/*************************************************************************//**
  \brief APS Broadcast Endpoint
*****************************************************************************/
#define APS_BROADCAST_ENDPOINT      0xff

/*************************************************************************//**
  \brief Min user endpoint number
*****************************************************************************/
#define APS_MIN_USER_ENDPOINT       0x01

/*************************************************************************//**
  \brief Max user endpoint number
*****************************************************************************/
#define APS_MAX_USER_ENDPOINT       0xf0

// \cond internal
//ZDO Endpoint
#define APS_ZDO_ENDPOINT            0x00

//Reserved endpoints
#define APS_MIN_RESERVED_ENDPOINT   0xf1
#define APS_MAX_RESERVED_ENDPOINT   0xfe

// APS short address defines
#define APS_MAX_UNICAST_SHORT_ADDRESS     0xfff7
// \endcond


/******************************************************************************
                   Types section
******************************************************************************/


/*****************************************************************************
  Special APS Level data types definition
*****************************************************************************/

/*************************************************************************//**
  \brief
    Common APS Address type

    Used as the part of standard APS primitives
*****************************************************************************/
typedef struct
{
  union
  {
  ShortAddr_t shortAddress; //!< 16-bit network address
#ifdef _APS_MULTICAST_
  GroupAddr_t groupAddress; //!< 16-bit group (multicast) address
#endif
  };                            //
  ExtAddr_t extAddress;     //!< 64-bit extended IEEE address
} APS_Address_t;

/*************************************************************************//**
  Address mode is used in some of APS primitives
  \brief
    APS addressing modes

    Defines APS addressing modes used in some standard primitives
*****************************************************************************/
typedef enum
{
  APS_NO_ADDRESS        = 0x00,   //!< Indirect addressing mode via binding future
#ifdef _APS_MULTICAST_
  APS_GROUP_ADDRESS     = 0x01,   //!< Group addressing mode via multicast
#endif
  APS_SHORT_ADDRESS     = 0x02,   //!< Unicast addressing mode by 16-bit network address
  APS_EXT_ADDRESS       = 0x03    //!< Unicast addressing mode by 64-bit IEEE address
} APS_AddrMode_t;

/*************************************************************************//**
  Status values in some of the APS primitives
  \brief
    APS status values

    APS status values used in the most part of standard primives except
    for the security service primitives where APS_SecurityStatus_t is used
    instead
*****************************************************************************/
typedef enum
{
  APS_SUCCESS_STATUS                      = 0x00,   //!<SUCCESS
  APS_ASDU_TOO_LONG_STATUS                = 0xa0,   //!<ASDU_TOO_LONG
  APS_DEFRAG_DEFERRED_STATUS              = 0xa1,   //!<DEFRAG_DEFERRED
  APS_DEFRAG_UNSUPPORTED_STATUS           = 0xa2,   //!<DEFRAG_UNSUPPORTED
  APS_ILLEGAL_REQUEST_STATUS              = 0xa3,   //!<ILLEGAL_REQUEST
  APS_INVALID_BINDING_STATUS              = 0xa4,   //!<INVALID_BINDING
  APS_INVALID_GROUP_STATUS                = 0xa5,   //!<INVALID_GROUP
  APS_INVALID_PARAMETER_STATUS            = 0xa6,   //!<INVALID_PARAMETER
  APS_NO_ACK_STATUS                       = 0xa7,   //!<NO_ACK
  APS_NO_BOUND_DEVICE_STATUS              = 0xa8,   //!<NO_BOUND_DEVICE
  APS_NO_SHORT_ADDRESS_STATUS             = 0xa9,   //!<NO_SHORT_ADDRESS
  APS_NOT_SUPPORTED_STATUS                =	0xaa,   //!<NOT_SUPPORTED
  APS_SECURED_LINK_KEY_STATUS             = 0xab,   //!<SECURED_LINK_KEY
  APS_SECURED_NWK_KEY_STATUS              = 0xac,   //!<SECURED_NWK_KEY
  APS_SECURITY_FAIL_STATUS                = 0xad,   //!<SECURITY_FAIL
  APS_TABLE_FULL_STATUS                   = 0xae,   //!<TABLE_FULL
  APS_UNSECURED_STATUS                    = 0xaf,   //!<UNSECURED
  APS_UNSUPPORTED_ATTRIBUTE_STATUS        = 0xb0,   //!<UNSUPPORTED_ATTRIBUTE
  //Proprietary status values
  APS_NOT_INDICATED_STATUS                = 0xb1,    //!<NOT_INDICATED (nonstandard status value)
  APS_REQUEST_MEMORY_FULL_STATUS          = 0xb2
} APS_Status_t;

#ifdef _SECURITY_
/*************************************************************************//**
  Status values as result of SKKE protocol (APS Security)

  \brief
    APS SKKE status values

    APS SKKE status values used in APS Key
    Establishment mechanism
*****************************************************************************/
typedef enum
{
  APS_SKKE_SUCCESS_STATUS             = 0x00,   //!<SUCCESS
  APS_SKKE_INVALID_PARAMETER_STATUS   = 0x01,   //!<INVALID_PARAMETER
  APS_SKKE_NO_MASTER_KEY_STATUS       = 0x02,   //!<NO_MASTER_KEY
  APS_SKKE_INVALID_CHALLENGE_STATUS   = 0x03,   //!<INVALID_CHALLENGE
  APS_SKKE_INVALID_SKG_STATUS         = 0x04,   //!<INVALID_SKG
  APS_SKKE_INVALID_MAC_STATUS         = 0x05,   //!<INVALID_MAC
  APS_SKKE_INVALID_KEY_STATUS         = 0x06,   //!<INVALID_KEY
  APS_SKKE_TIMEOUT_STATUS             = 0x07,   //!<TIMEOUT
  APS_SKKE_BAD_FRAME_STATUS           = 0x08,   //!<BAD_FRAME
} APS_SkkeStatus_t;
#endif //#ifdef _SECURITY_

/*************************************************************************//**
  AIB Attribute's ID definition

  \brief
    APS Information base attributes IDs

    APS Information base attribute IDs used for AIB management with
    standard AIB maintenance primitives
*****************************************************************************/
typedef enum
{
  //AIB standard attributes
  APS_AIB_BINDING_TABLE                   = 0xc1,   //!<apsBindingTable
  APS_AIB_DESIGNATED_COORDINATOR          = 0xc2,   //!<apsDesignatedCoordinator
  APS_AIB_CHANNEL_MASK                    = 0xc3,   //!<apsChannelMask
  APS_AIB_USE_EXTENDED_PANID              = 0xc4,   //!<apsUseExtendedPANID
  APS_AIB_GROUP_TABLE                     = 0xc5,   //!<apsGroupTable
  APS_AIB_NONMEMBER_RADIUS                = 0xc6,   //!<apsNonmemberRadius
  APS_AIB_PERMISSIONS_CONFIGURATION       = 0xc7,   //!<apsPermissionsConfiguration
  APS_AIB_USE_INSECURE_JOIN               = 0xc8,   //!<apsUseInsecureJoin
  APS_AIB_INTERFRAME_DELAY                = 0xc9,   //!<apsInterframeDelay

  //AIB security attributes ID
  APS_AIB_DEVICE_KEY_PAIR_SET             = 0xaa,   //!<apsDeviceKeyPairSet
  APS_AIB_TRUST_CENTER_ADDRESS            = 0xab,   //!<apsTrustCenterAddress
  APS_AIB_SECURITY_TIME_OUT_PERIOD        = 0xac    //!<apsSecurityTimeOutPeriod
} APS_AibAttributeId_t;

/*************************************************************************//**
  APS constants stored in AIB

  \brief
    APS SubLayer Constants

    The constants defining the characteristics of the APS sub-layer
*****************************************************************************/
typedef struct
{
  uint8_t   apscMaxDescriptorSize;                    //!<apscMaxDescriptorSize
  uint8_t   apscMaxFrameRetries;                      //!<apscMaxFrameRetries
  uint32_t  apscAckWaitDuration;                      //!<apscAckWaitDuration
  uint8_t   apscMinDuplicateRejectionTableSize;       //!<apscMinDuplicateRejectionTableSize
  uint8_t   apscMaxWindowSize;                        //!<apscMaxWindowSize
  uint16_t  apscInterframeDelay;                      //!<apscInterframeDelay
  uint8_t   apscMinHeaderOverHead;                    //!<apscMinHeaderOverHead
} APS_AibPermissionsConfiguration_t;



/*****************************************************************************
  APS Group Table entry type
*****************************************************************************/
//\cond internal
typedef struct
{
  bool busy;
  GroupAddr_t groupAddr;              //Group address
  Endpoint_t endpoints[1];            //endpoints (group members)
} APS_GroupTableEntry_t;
//\endcond

/*****************************************************************************
  APS Group Table type
*****************************************************************************/
//\cond internal
typedef struct
{
  uint8_t   groupsAmount;             //Table size in cells (amount of entries)
  uint8_t   endpointsAmount;          //Maximum amount of group members
                                      //(positive value)
  uint16_t  entrySizeof;              //Entry size in bytes
  APS_GroupTableEntry_t *entries;     //Table entries buffer pointer
} APS_GroupTable_t;
//\endcond

/*************************************************************************//**
  Types of parameters which can be set to the APS AIB

  \brief
    Types of parameters which can be set to the APS AIB

    This union used in AIB management primitives to interpret the particular
    parameter values
*****************************************************************************/
typedef union
{
  //AIB standard attributes

  void      *apsBindingTable;         //!<  apsBindingTable pointer
  bool      apsDesignatedCoordinator; //!<  apsDesignatedCoordinator value
  uint32_t  apsChannelMask;           //!<  apsChannelMask value
  ExtPanId_t apsUseExtendedPANID;      //!<  apsUseExtendedPANID value
  APS_GroupTable_t *apsGroupTable;    //!<  apsGroupTable pointer
  uint8_t   apsNonmemberRadius;       //!<  apsNonmemberRadius value

                                      //!   apsPermissionsConfiguration pointer
  APS_AibPermissionsConfiguration_t *apsPermissionsConfiguration;

  bool      apsUseInsecureJoin;       //!<  apsUseInsecureJoin value
  uint16_t  apsInterframeDelay;       //!<  apsInterframeDelay value

  //AIB security attributes
  void      *apsDeviceKeyPairSet;     //!<  apsDeviceKeyPairSet pointer
  uint64_t  apsTrustCenterAddress;    //!<  apsTrustCenterAddress value
  uint16_t  apsSecurityTimeOutPeriod; //!<  apsSecurityTimeOutPeriod value
} APS_AibAttribute_t;



/*****************************************************************************
  APSDE Entity Primitives
*****************************************************************************/

/*************************************************************************//**
  \brief
  Parameters structure of the APS_DataReq_t::APS_DataConf() function.
  The APSDE-DATA.confirm primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  //APS_AddrMode_t dstAddrMode;
  //APS_Address_t dstAddress;
  //Endpoint_t dstEndpoint;
  //Endpoint_t srcEndpoint;
  APS_Status_t status;                //!<  The status of the corresponding request
  uint32_t txTime;                    //!<  Timestamp for the transmitted packet based on the local clock, as provided by the NWK layer.

} APS_DataConf_t;


/*************************************************************************//**
  \brief
    Describes the options of data transmission
*****************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  uint8_t   securityEnabledTransmission   :1;   //!<  Security enabled transmission
  uint8_t   useNwkKey                     :1;   //!<  Use NWK key
  uint8_t   acknowledgedTransmission      :1;   //!<  Acknowledged transmission
  uint8_t   fragmentationPermitted        :1;   //!<  Fragmentation permitted
  uint8_t   reserved                      :4;   //!<  Reserved. Should always be zero
} APS_TxOptions_t;
END_PACK

/*************************************************************************//**
  \brief
    Parameters structure of the APS_DataReq() function.
    The APSDE-DATA.request primitive.
*****************************************************************************/
typedef struct
{
  //Service fields
  /*! Used for queue support*/
  struct
  {
    void *next;
  } service;

  //Primitive fields
  /*!
  The addressing mode for the destination address used in this primitive and the
  APDU to be transferred. May possess any non-reserved value from the following list: \n
  0x00 = DstAddress and DstEndpoint are missing\n
  0x01 = 16-bit group address for DstAddress, DstEndpoint is missing\n
  0x02 = 16-bit address for DstAddress, DstEndpoint is present\n
  0x03 = 64-bit extended address for DstAddress, DstEndpoint is present\n
  0x04 - 0xff = reserved\n
  Note: It will be convenient to use the APS_AddrMode_t values
  */
  APS_AddrMode_t dstAddrMode;
  /*!The address of the individual device or group address of the entity to which the ASDU is
  being transferred.
  */
  APS_Address_t dstAddress;
  /*!This parameter shall be present if and only if the DstAddrMode parameter
  value is 0x02 or 0x03 and, if present, shall contain either the number of
  individual endpoints of the entity to which the ASDU is being transferred,
  or the broadcast endpoint (0xff).
  */
  Endpoint_t dstEndpoint;
  /*!The identifier of the profile for which this frame is intended.*/
  ProfileId_t profileId;
  /*!The identifier of the object for which this frame is intended.*/
  ClusterId_t clusterId;
  /*!The individual endpoint of the entity from which the ASDU is being transferred.*/
  Endpoint_t srcEndpoint;
  /*!The number of octets comprising the ASDU to be transferred. The maximum length of an
  individual APS frame payload is given as NsduLength-apscMinHeaderOverhead. Assuming
  the possibility of fragmentation, a maximum-sized single ASDU consists of 256 such blocks.
  */
  uint8_t asduLength;
  /*!The set of octets comprising the ASDU to be transferred.*/
  uint8_t *asdu;
  /*! <0000 xxxx> (Where x can be 0 or 1)
  The transmission options for the ASDU to be transferred.
  Must be selected among the following values:\n
  0x01 = Security enabled transmission,\n
  0x02 = Use NWK key,\n
  0x04 = Acknowledged transmission,\n
  0x08 = Fragmentation permitted,\n
  probably combined by logical OR.\n
  It is fine to use the APS_TxOptions_t enumerations.*/
  APS_TxOptions_t txOptions;
  /*!The distance, in hops, that a transmitted frame will be allowed to
  travel via the network.
  */
  uint8_t radius;
  //Callback and Confirm
  /*!Callback function pointer as a handler of corresponding confirm primitive*/
  void (*APS_DataConf)(APS_DataConf_t *conf);
  APS_DataConf_t confirm;                       //!<  Confirm primitive as a parameter of the callback function
} APS_DataReq_t;


/*************************************************************************//**
  \brief
    Parameters structure of the APS_RegisterEndpointReq_t::APS_DataInd() function
    The function is determined by certain End Point.
    The APSDE-DATA.indication primitive.
*****************************************************************************/
typedef struct
{
  /*!The addressing mode for the destination address used in this primitive and of the
  APDU that has been received. May possess any non-reserved value from the following list:\n
  0x00 = reserved\n
  0x01 = 16-bit group address for DstAddress; DstEndpoint is missing\n
  0x02 = 16-bit address for DstAddress, DstEndpoint is present\n
  0x03 - 0xff = reserved\n
  Note: It will be convenient to use the APS_AddrMode_t values*/
  APS_AddrMode_t dstAddrMode;
  /*!The individual device address or group address to which the ASDU is directed.
  Value size depends on the dstAddrMode parameter*/
  APS_Address_t dstAddress;
  /*!The target endpoint on the local entity to which the ASDU is directed.*/
  Endpoint_t dstEndpoint;
  /*!The addressing mode for the source address used in this primitive and of the
  APDU that has been received. May possess any non-reserved value from the following list:\n
  0x00 = reserved\n
  0x01 = reserved\n
  0x02 = 16-bit short address for SrcAddress, SrcEndpoint is present\n
  0x03 = 64-bit extended address for SrcAddress, SrcEndpoint is present\n
  0x04 - 0xff = reserved\n
  Note: It will be convenient to use the APS_AddrMode_t values*/
  APS_AddrMode_t srcAddrMode;
  /*!The individual device address of the entity from which the ASDU has been
  received. Value type and size is depend of the srcAddrMode parameter*/
  APS_Address_t srcAddress;
  /*!The number of the individual endpoint of the entity from which the ASDU has been
  received.*/
  Endpoint_t srcEndpoint;
  /*!The identifier of the profile from which this frame originates.*/
  ProfileId_t profileId;
  /*!The identifier of the received object.*/
  ClusterId_t clusterId;
  /*!The number of octets comprising the ASDU being indicated by the APSDE.*/
  uint8_t asduLength;
  /*!The set of octets comprising the ASDU being indicated by the APSDE.*/
  uint8_t *asdu;
  /*!The status of the incoming frame processing.*/
  APS_Status_t status;
  /*!UNSECURED if the ASDU was received without any security.\n
  SECURED_NWK_KEY if the received ASDU was secured with the NWK key.\n
  SECURED_LINK_KEY if the ASDU was secured with a link key.*/
  APS_Status_t securityStatus;
  /*!The link quality indication delivered by the NLDE.*/
  uint8_t linkQuality;
  /*!Timestamp for the received packet based on the local clock, as provided by
  the NWK layer.*/
  uint32_t rxTime;
  //\cond internal
  int8_t rssi;
  //\endcond
} APS_DataInd_t;

//============================================================================

#ifdef _BINDING_
/*****************************************************************************
  Binding Primitives
*****************************************************************************/
/*************************************************************************//**
\brief
  Parameters structure of the APS_BindConf() function.
  ZigBee spec r17: Table 2.7, page 36:
  The APSME-BIND.confirm primitive.
  This primitive allows the next higher layer to be notified of the results of
  its request to bind two devices together, or to bind a device to a group.
*****************************************************************************/
typedef struct
{
  /*!The results of the binding request.*/
  APS_Status_t status;
} APS_BindConf_t;


/*************************************************************************//**
\brief
  ZigBee spec r17: Table 2.6, page 34:
  Parameters structure of the APS_BindReq() function. Binding allows the next 
  higher layer to request to bind two devices together, or to bind a device 
  to a group, by creating an entry in its local binding table, if supported.
*****************************************************************************/
typedef struct
{
  /*! The source IEEE address for the binding entry.*/
  ExtAddr_t srcAddr;
  /*! The source endpoint for the binding entry.*/
  Endpoint_t srcEndpoint;
  /*! The identifier of the cluster on the source device that is to be bound 
  to the destination device.*/
  ClusterId_t clusterId;
  /*! The addressing mode for the destination address used in this primitive. 
  This parameter can take one of the non-reserved values from the following list:
  0x00 = reserved
  0x01 = 16-bit group address for DstAddr and DstEndpoint not present
  0x02 = reserved
  0x03 = 64-bit extended address for DstAddr and DstEndpoint present
  0x04 . 0xff = reserved*/
  APS_AddrMode_t dstAddrMode;
  /*! The destination address for the binding entry.*/
  APS_Address_t dstAddr;
  /*! This parameter will be present only if the DstAddrMode parameter has a value
  of 0x03 and, if present, will be the destination endpoint for the binding entry.*/
  Endpoint_t dstEndpoint;
  /*! APS Bind confirm parameters structure.*/
  APS_BindConf_t confirm;
} APS_BindReq_t;


/*************************************************************************//**
\brief 
  Parameters structure of the APS_UnbindConf() function.
  ZigBee spec r17: Table 2.9, page 34:
  The APSME-UNBIND.confirm primitive.
  This primitive allows the next higher layer to be notified of the results of
  its request to unbind two devices, or to unbind a device from a group.
*****************************************************************************/
typedef struct
{
  /*! The results of the unbind request.*/
  APS_Status_t status;
} APS_UnbindConf_t;


/*************************************************************************//**
\brief 
  Parameters structure of the APS_UnbindReq_t() function.
  ZigBee spec r17: Table 2.8, page 38:
  APSME-UNBIND.request Parameters.
  The APSME-UNBIND.request primitive. This primitive allows the next higher 
  layer to request to unbind two devices, or to unbind a device from a group,
  by removing an entry in its local binding table, if supported.
*****************************************************************************/
typedef struct
{
  /*! The source IEEE address for the binding entry.*/
  ExtAddr_t srcAddr;
  /*! The source endpoint for the binding entry.*/
  Endpoint_t srcEndpoint;
  /*! The identifier of the cluster on the source device that is bound to the 
  destination device.*/
  ClusterId_t clusterId;
  /*! The addressing mode for the destination address used in this primitive.
  This parameter can take one of the non-reserved values from the following list:
  0x00 = reserved
  0x01 = 16-bit group address for DstAddr and DstEndpoint not present
  0x02 = reserved
  0x03 = 64-bit extended address for DstAddr and DstEndpoint present
  0x04 . 0xff = reserved*/
  APS_AddrMode_t dstAddrMode;
  /*! The destination address for the binding entry.*/
  APS_Address_t dstAddr;
  /*! This parameter will be present only if the DstAddrMode parameter has a value
  of 0x03 and, if present, will be the destination endpoint for the binding entry.*/
  Endpoint_t dstEndpoint;
  /*! APS Unbind confirm parameters structure.*/
  APS_UnbindConf_t confirm;
} APS_UnbindReq_t;

#endif //#ifdef _BINDING_

/*****************************************************************************
  AIB Maintenance Primitives
*****************************************************************************/

/*************************************************************************//**
  \brief
    Parameters structure of the APS_GetConf() function.
    The APSME-GET.confirm primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The results of the request to read an AIB attribute value.*/
  APS_Status_t status;
  /*!The length, in octets, of the attribute value being returned.*/
  uint16_t aibAttributeLength;
  /*!The value of the AIB attribute that was read.*/
  APS_AibAttribute_t aibAttributeValue;
} APS_GetConf_t;


/*************************************************************************//**
  \brief
    Parameters structure of the APS_GetReq() function.
    The APSME-GET.request primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The identifier of the AIB attribute to read.*/
  APS_AibAttributeId_t aibAttribute;

  //Confirm
  /*!The confirm primitive as transaction result*/
  APS_GetConf_t confirm;
} APS_GetReq_t;


/*************************************************************************//**
  \brief
    Parameters structure of the APS_SetConf() function
    The APSME-SET.confirm primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The result of the request to write the AIB Attribute.*/
  APS_Status_t status;
} APS_SetConf_t;


/*************************************************************************//**
  \brief
    Parameters structure of the APS_SetReq() function
    The APSME-SET.request primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The identifier of the AIB attribute to be written.*/
  APS_AibAttributeId_t aibAttribute;
  /*!The length, in octets, of the attribute value being set.*/
  uint16_t aibAttributeLength;
  /*!The value of the AIB attribute that should be written.*/
  APS_AibAttribute_t aibAttributeValue;

  //Confirm
  /*!The confirm primitive as transaction result*/
  APS_SetConf_t confirm;
} APS_SetReq_t;
//============================================================================

#ifdef _APS_MULTICAST_
/*****************************************************************************
  APS Group Management Primitives
*****************************************************************************/

/*************************************************************************//**
  \brief
    Parameters structure of the APS_AddGroupConf() function.
    The APSME-ADD-GROUP.confirm primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The status of the request to add a group.*/
  APS_Status_t status;
} APS_AddGroupConf_t;

/*************************************************************************//**
  \brief
    Parameters structure of the APS_AddGroupReq() function.
    The APSME-ADD-GROUP.request primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The 16-bit address of the group being added.*/
  GroupAddr_t groupAddress;
  /*!The endpoint to which the given group is being added.*/
  Endpoint_t endpoint;

  //Confirm
  /*!The confirm primitive as transaction result*/
  APS_AddGroupConf_t confirm;
} APS_AddGroupReq_t;


/*************************************************************************//**
  \brief
    Parameters structure of the APS_RemoveGroupConf() function.
    The APSME-REMOVE-GROUP.confirm primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The status of the request to remove a group.*/
  APS_Status_t status;
} APS_RemoveGroupConf_t;

/*************************************************************************//**
  \brief
    Parameters structure of the APS_RemoveGroupReq() function.
    The APSME-REMOVE-GROUP.request primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The 16-bit address of the group being removed.*/
  GroupAddr_t groupAddress;
  /*!The endpoint from which the given group is being removed.*/
  Endpoint_t endpoint;

  //Confirm
  /*!The confirm primitive as transaction result*/
  APS_RemoveGroupConf_t confirm;
} APS_RemoveGroupReq_t;


/*************************************************************************//**
  \brief
    Parameters structure of the APS_RemoveAllGroupsConf() function.
    The APSME-REMOVE-ALL-GROUPS.confirm primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The status of the request to remove all groups.*/
  APS_Status_t status;
} APS_RemoveAllGroupsConf_t;

/*************************************************************************//**
  \brief
    Parameters structure of the APS_RemoveAllGroupsReq() function.
    The APSME-REMOVE-ALL-GROUPS.request primitive.
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The endpoint from which the group is being removed.*/
  Endpoint_t endpoint;

  //Confirm
  /*!The confirm primitive as transaction result.*/
  APS_RemoveAllGroupsConf_t confirm;
} APS_RemoveAllGroupsReq_t;
//============================================================================
#endif //#ifdef _APS_MULTICAST_

//\cond internal
#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
typedef struct
{
  ExtAddr_t deviceAddress;
  uint8_t masterKey[16];
  uint8_t linkKey[16];
  uint32_t outFrameCounter;
  uint32_t inFrameCounter;
} ApsKeyPairDescriptor_t;



/*****************************************************************************
  APS Security Management Primitives
*****************************************************************************/

typedef enum
{
  APS_SKKE_KEY_ESTABLISHMENT_METHOD = 0x00
} APS_KeyEstablishmentMethod_t;


/*****************************************************************************
  APSME-ESTABLISH-KEY.confirm primitive
*****************************************************************************/
typedef struct
{
  ExtAddr_t address;
  APS_SkkeStatus_t status;
} APS_EstablishKeyConf_t;



/*****************************************************************************
  APSME-ESTABLISH-KEY.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  /*! Used for queue support*/
  struct
  {
    void *next;
  } service;
  //Standards fields
  ExtAddr_t responderAddress;
  bool useParent;
  ExtAddr_t responderParentAddress;
  APS_KeyEstablishmentMethod_t keyEstablishmentMethod;
  //Confirm and callback
  APS_EstablishKeyConf_t confirm;
  void (*APS_EstablishKeyConf)(APS_EstablishKeyConf_t *conf);
} APS_EstablishKeyReq_t;


/*****************************************************************************
  APSME-ESTABLISH-KEY.response primitive
*****************************************************************************/
typedef struct
{
  ExtAddr_t initiatorAddress;
  bool accept;
  //Confirm and callback
  APS_EstablishKeyConf_t confirm;
  void (*APS_EstablishKeyConf)(APS_EstablishKeyConf_t *conf);
} APS_EstablishKeyResp_t;


/*****************************************************************************
  APSME-ESTABLISH-KEY.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t initiatorAddress;
  APS_KeyEstablishmentMethod_t keyEstablishmentMethod;
} APS_EstablishKeyInd_t;
#endif //#ifdef _HIGH_SECURITY_



//============================================================================
typedef enum
{
  APS_TRUST_CENTER_MASTER_KEY_TYPE =      0x00,
  APS_STANDARD_NETWORK_KEY_TYPE =         0x01,
  APS_APP_MASTER_KEY_TYPE =               0x02,
  APS_APP_LINK_KEY_TYPE =                 0x03,
  APS_TRUST_CENTER_LINK_KEY_TYPE =        0x04,
  APS_HIGH_SECURITY_NETWORK_KEY_TYPE =    0x05
} APS_TransportKeyType_t;


typedef struct
{
  ExtAddr_t parentAddress;
  uint8_t key[16];
} APS_ReqTrustCenterMasterOrLinkKeyTransportData_t;

typedef struct
{
  uint8_t keySeqNumber;
  uint8_t networkKey[16];
  bool useParent;
  ExtAddr_t parentAddress;
} APS_ReqNetworkKeyTransportData_t;

typedef struct
{
  ExtAddr_t partnerAddress;
  bool initiator;
  uint8_t key[16];
} APS_ReqApplicationMasterOrLinkKeyTransportData_t;

typedef union
{
  APS_ReqTrustCenterMasterOrLinkKeyTransportData_t trustCenterKey;
  APS_ReqNetworkKeyTransportData_t networkKey;
  APS_ReqApplicationMasterOrLinkKeyTransportData_t applicationKey;
} APS_ReqTransportKeyData_t;


typedef enum
{
  APS_TKR_SUCCESS_STATUS                      = 0x00,
  APS_TKR_NO_SHORT_ADDRESS_STATUS             = 0x01,
  APS_TKR_SECURITY_FAIL_STATUS                = 0x02,
  APS_TKR_NOT_SENT_STATUS                     = 0x03
} APS_TkrStatus_t;

/*****************************************************************************
  (Out of ZigBee Standard) APSME-TRANSPORT-KEY.confirm primitive
*****************************************************************************/
typedef struct
{
  APS_TkrStatus_t status;
} APS_TransportKeyConf_t;

/*****************************************************************************
  APSME-TRANSPORT-KEY.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  struct
  {
    void *next;
  } service;

  //Standards fields
  ExtAddr_t destAddress;
  APS_TransportKeyType_t keyType;
  APS_ReqTransportKeyData_t transportKeyData;

  //Callback and Confirm
  APS_TransportKeyConf_t confirm;
  void (*APS_TransportKeyConf)(APS_TransportKeyConf_t *conf);
} APS_TransportKeyReq_t;

//============================================================================

typedef struct
{
  uint8_t trustCenterMasterKey[16];
} APS_IndTrustCenterMasterOrLinkKeyTransportData_t;

typedef struct
{
  uint8_t keySeqNumber;
  uint8_t networkKey[16];
} APS_IndNetworkKeyTransportData_t;

typedef struct
{
  ExtAddr_t partnerAddress;
  uint8_t key[16];
} APS_IndApplicationMasterOrLinkKeyTransportData_t;

typedef union
{
  APS_IndTrustCenterMasterOrLinkKeyTransportData_t trustCenterKey;
  APS_IndNetworkKeyTransportData_t networkKey;
  APS_IndApplicationMasterOrLinkKeyTransportData_t applicationKey;
} APS_IndTransportKeyData_t;


/*****************************************************************************
  APSME-TRANSPORT-KEY.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t srcAddress;
  APS_TransportKeyType_t keyType;
  APS_IndTransportKeyData_t transportKeyData;
} APS_TransportKeyInd_t;
//============================================================================

typedef enum
{
  APS_STANDARD_DEVICE_SECURED_REJOIN_STATUS =           0x00,
  APS_STANDARD_DEVICE_UNSECURED_JOIN_STATUS =           0x01,
  APS_DEVICE_LEFT_STATUS =                              0x02,
  APS_STANDARD_DEVICE_UNSECURED_REJOIN_STATUS =         0x03,
  APS_HIGH_SECURITY_DEVICE_SECURED_REJOIN_STATUS =      0x04,
  APS_HIGH_SECURITY_DEVICE_UNSECURED_JOIN_STATUS =      0x05,
  APS_RESERVED_STATUS =                                 0x06,
  APS_HIGH_SECURITY_DEVICE_UNSECURED_REJOIN_STATUS =    0x07
} APS_UpdateDeviceStatus_t;

typedef enum
{
  APS_UDR_SUCCESS_STATUS                      = 0x00,
  APS_UDR_NO_SHORT_ADDRESS_STATUS             = 0x01,
  APS_UDR_SECURITY_FAIL_STATUS                = 0x02,
  APS_UDR_NOT_SENT_STATUS                     = 0x03
} APS_UdrStatus_t;

/*****************************************************************************
  (Out of ZigBee Standard) APSME-UPDATE-DEVICE.confirm primitive
*****************************************************************************/
typedef struct
{
  APS_UdrStatus_t status;
} APS_UpdateDeviceConf_t;


/*****************************************************************************
  APSME-UPDATE-DEVICE.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  struct
  {
    void *next;
  } service;

  //Standards fields
  ExtAddr_t destAddress;
  ExtAddr_t deviceAddress;
  APS_UpdateDeviceStatus_t status;
  ShortAddr_t deviceShortAddress;

  //Callback and Confirm
  APS_UpdateDeviceConf_t confirm;
  void (*APS_UpdateDeviceConf)(APS_UpdateDeviceConf_t *conf);
} APS_UpdateDeviceReq_t;


/*****************************************************************************
  APSME-UPDATE-DEVICE.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t srcAddress;
  ExtAddr_t deviceAddress;
  APS_UpdateDeviceStatus_t status;
  ShortAddr_t deviceShortAddress;
} APS_UpdateDeviceInd_t;
//============================================================================

typedef enum
{
  APS_RDR_SUCCESS_STATUS                      = 0x00,
  APS_RDR_NO_SHORT_ADDRESS_STATUS             = 0x01,
  APS_RDR_SECURITY_FAIL_STATUS                = 0x02,
  APS_RDR_NOT_SENT_STATUS                     = 0x03
} APS_RdrStatus_t;

/*****************************************************************************
  (Out of ZigBee Standard) APSME-REMOVE-DEVICE.confirm primitive
*****************************************************************************/
typedef struct
{
  APS_RdrStatus_t status;
} APS_RemoveDeviceConf_t;


/*****************************************************************************
  APSME-REMOVE-DEVICE.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  struct
  {
    void *next;
  } service;

  //Standards fields
  ExtAddr_t parentAddress;
  ExtAddr_t childAddress;

  //Callback and Confirm
  APS_RemoveDeviceConf_t confirm;
  void (*APS_RemoveDeviceConf)(APS_RemoveDeviceConf_t *conf);
} APS_RemoveDeviceReq_t;


/*****************************************************************************
  APSME-REMOVE-DEVICE.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t srcAddress;
  ExtAddr_t childAddress;
} APS_RemoveDeviceInd_t;
//============================================================================


#ifdef _HIGH_SECURITY_

typedef enum
{
  APS_NETWORK_KEY_TYPE =      0x01,
  APS_APP_KEY_TYPE =          0x02
} APS_RequestKeyType_t;

typedef enum
{
  APS_RKR_SUCCESS_STATUS                      = 0x00,
  APS_RKR_NO_SHORT_ADDRESS_STATUS             = 0x01,
  APS_RKR_SECURITY_FAIL_STATUS                = 0x02,
  APS_RKR_NOT_SENT_STATUS                     = 0x03
} APS_RkrStatus_t;
/*****************************************************************************
  (Out of ZigBee Standard) APSME-REQUEST-KEY.confirm primitive
*****************************************************************************/
typedef struct
{
  APS_RkrStatus_t status;
} APS_RequestKeyConf_t;

/*****************************************************************************
  APSME-REQUEST-KEY.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  struct
  {
    void *next;
  } service;

  //Standards fields
  ExtAddr_t destAddress;
  APS_RequestKeyType_t keyType;
  ExtAddr_t partnerAddress;

  //Callback and Confirm
  APS_RequestKeyConf_t confirm;
  void (*APS_RequestKeyConf)(APS_RequestKeyConf_t *conf);
} APS_RequestKeyReq_t;

/*****************************************************************************
  APSME-REQUEST-KEY.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t srcAddress;
  APS_RequestKeyType_t keyType;
  ExtAddr_t partnerAddress;
} APS_RequestKeyInd_t;

#endif //#ifdef _HIGH_SECURITY_

//============================================================================




typedef enum
{
  APS_SKR_SUCCESS_STATUS                      = 0x00,
  APS_SKR_NO_SHORT_ADDRESS_STATUS             = 0x01,
  APS_SKR_SECURITY_FAIL_STATUS                = 0x02,
  APS_SKR_NOT_SENT_STATUS                     = 0x03
} APS_SkrStatus_t;

/*****************************************************************************
  (Out of ZigBee Standard) APSME-SWITCH-KEY.confirm primitive
*****************************************************************************/
typedef struct
{
  APS_SkrStatus_t status;
} APS_SwitchKeyConf_t;


/*****************************************************************************
  APSME-SWITCH-KEY.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  struct
  {
    void *next;
  } service;

  //Standards fields
  ExtAddr_t destAddress;
  uint8_t keySeqNumber;

  //Callback and Confirm
  APS_SwitchKeyConf_t confirm;
  void (*APS_SwitchKeyConf)(APS_SwitchKeyConf_t *conf);
} APS_SwitchKeyReq_t;


/*****************************************************************************
  APSME-SWITCH-KEY.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t srcAddress;
  uint8_t keySeqNumber;
} APS_SwitchKeyInd_t;
//============================================================================

#ifdef _HIGH_SECURITY_

typedef enum
{
  APS_INITIATE_ACTION =               0x00,
  APS_RESPOND_ACCEPT_ACTION =         0x01,
  APS_RESPOND_REJECT_ACTION =         0x02
} APS_AuthenticateAction_t;

typedef enum
{
  APS_AUTH_SUCCESS_STATUS =               0x00,
  APS_AUTH_INVALID_PARAMETER_STATUS =     0x01,
  APS_AUTH_NO_KEY_STATUS =                0x02,
  APS_AUTH_NO_DATA_STATUS =               0x03,
  APS_AUTH_INVALID_CHALLENGE_STATUS =     0x04,
  APS_AUTH_INVALID_MAC_STATUS =           0x05,
  APS_AUTH_INVALID_KEY_STATUS =           0x06,
  APS_AUTH_TIMEOUT_STATUS =               0x07
} APS_AuthenticateStatus_t;

/*****************************************************************************
  APSME-AUTHENTICATE.confirm primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t address;
  APS_AuthenticateStatus_t status;
} APS_AuthenticateConf_t;


/*****************************************************************************
  APSME-AUTHENTICATE.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  struct
  {
    void *next;
  } service;

  //Standards fields
  ExtAddr_t partnerAddress;
  APS_AuthenticateAction_t action;
  uint8_t randomChallenge[16];

  //Callback and Confirm
  void (*APS_AuthenticateConf)(APS_AuthenticateConf_t *conf);
  APS_AuthenticateConf_t confirm;
} APS_AuthenticateReq_t;

/*****************************************************************************
  APSME-AUTHENTICATE.indication primitive
*****************************************************************************/
typedef struct
{
  //Standards fields
  ExtAddr_t initiatorAddress;
  uint8_t randomChallenge[16];
} APS_AuthenticateInd_t;

#endif //#ifdef _HIGH_SECURITY_

//============================================================================
#endif //#ifdef _SECURITY_
//\endcond


/*****************************************************************************
  APS Special Primitives
*****************************************************************************/
//\cond internal


/*****************************************************************************
  APSME-RESET.confirm primitive
*****************************************************************************/
typedef struct
{
  //Standard fields
  APS_Status_t status;
} APS_ResetConf_t;

/*****************************************************************************
  APSME-RESET.request primitive
*****************************************************************************/
typedef struct
{
  //Standard fields
  bool powerFailure;
  //Callback and Confirm
  void (*APS_ResetConf)(APS_ResetConf_t *conf);
  APS_ResetConf_t confirm;
} APS_ResetReq_t;

/*****************************************************************************
  APSME-START.confirm primitive
*****************************************************************************/
typedef struct
{
  //Standard fields
  APS_Status_t status;
} APS_StartConf_t;

/*****************************************************************************
  APSME-START.request primitive
*****************************************************************************/
typedef struct
{
  //Standard fields

  //Callback and Confirm
  void (*APS_StartConf)(APS_StartConf_t *conf);
  APS_StartConf_t confirm;
} APS_StartReq_t;


/*****************************************************************************
  APSME-STOP.confirm primitive
*****************************************************************************/
typedef struct
{
  //Standard fields
  APS_Status_t status;
} APS_StopConf_t;


/*****************************************************************************
  APSME-STOP.request primitive
*****************************************************************************/
typedef struct
{
  //Standard fields

  //Callback and Confirm
  void (*APS_StopConf)(APS_StopConf_t *conf);
  APS_StopConf_t confirm;
} APS_StopReq_t;
//\endcond
//============================================================================




/*****************************************************************************
  APS Endpoint Register/Unregister Primitives
*****************************************************************************/

/*************************************************************************//**
  \brief
    Parameters structure of the APS_RegisterEndpointReq() function.
    APSME-REGISTER-ENDPOINT.request primitive
*****************************************************************************/
typedef struct
{
  //Service fields
  /*! Used for queue support*/
  struct
  {
    void *next;
    struct
    {
      uint8_t noIndication  :1; //If
      uint8_t reserved      :7;
    };
  } service;

  //Standard fields
  /*!Simple descriptor pointer*/
  SimpleDescriptor_t *simpleDescriptor;
  /*!The APSDE-DATA.indication handler pointer for endpoint should be registered.*/
  void (*APS_DataInd)(APS_DataInd_t *ind);
} APS_RegisterEndpointReq_t;

/*************************************************************************//**
  \brief
    Parameters structure of the APS_UnregisterEndpointReq() function.
    APSME-UNREGISTER-ENDPOINT.request primitive
*****************************************************************************/
typedef struct
{
  //Standard fields
  /*!The endpoint which should be unregistered.*/
  Endpoint_t endpoint;
} APS_UnregisterEndpointReq_t;
//============================================================================



/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/


/*****************************************************************************
  APS API Prototypes
*****************************************************************************/

/*****************************************************************************
  APS Task Manager API
*****************************************************************************/
// \cond internal
/*****************************************************************************
  Peforms APS sublayer processing.
  Parameters: None
  Returns:    None
*****************************************************************************/
extern void APS_TaskHandler(void);
// \endcond
//============================================================================

#ifdef _BINDING_
/*****************************************************************************
  APS Binding API
*****************************************************************************/
void APS_BindReq(APS_BindReq_t *req);
void APS_UnbindReq(APS_UnbindReq_t *req);
#endif //#ifdef _BINDING_

/*****************************************************************************
  APS AIB Manager API
*****************************************************************************/

/**************************************************************************//**
  \brief
    Gets a parameter from AIB.

  \param[in] req  The APSME-GET.request (APS_GetReq_t) primitive pointer.
  \return         None.
*****************************************************************************/
extern void APS_GetReq(APS_GetReq_t *req);

/**************************************************************************//**
  \brief
    Sets a parameter to AIB

  Function returns the result of transaction via callback call with confirm (APS_SetConf_t)
  primitive pointer as parameter

  \param[in] req  The APSME-SET.request (APS_SetReq_t) primitive pointer.
  \return         None.
*****************************************************************************/
extern void APS_SetReq(APS_SetReq_t *req);
//============================================================================

/*****************************************************************************
  APS Control Manager API
*****************************************************************************/

/*************************************************************************//**
  \brief
    Registers endpoint to APS

  \param[in] req  The register endpoint primitive pointer.
  \return         None.
*****************************************************************************/
extern void APS_RegisterEndpointReq(APS_RegisterEndpointReq_t *req);

/*************************************************************************//**
  \brief
    Unregisters endPoint from APS

  \param[in] req  The unregister endpoint primitive pointer.
  \return         None.
*****************************************************************************/
extern void APS_UnregisterEndpointReq(APS_UnregisterEndpointReq_t *req);

/*************************************************************************//**
  \brief
    Returns the pointer to APS EndPointList

  \return         Valid APS EndpointList pointer or NULL if there are no registered endpoints.
*****************************************************************************/
extern APS_RegisterEndpointReq_t *APS_GetEndpointList(void);

/*************************************************************************//**
  \brief
    Stops APS Data indications of specific endpoint number.

  \param[in] endpoint  The registered endpoint number. The 0xff special value means all registered endpoints.
  \return         None.
*****************************************************************************/
extern void APS_StopEndpointIndication(Endpoint_t endpoint);

/*************************************************************************//**
  \brief
    Resumes APS Data indications of specific endpoint number.

  \param[in] endpoint  The registered endpoint number. The 0xff special value means all registered endpoints.
  \return         None.
*****************************************************************************/
extern void APS_ResumeEndpointIndication(Endpoint_t endpoint);

//\cond internal
/**************************************************************************//**
 brief Resets APS to default state

 The function can be called only by ZDO

  \param[in] req  The APS-RESET.request primitive pointer.
  \return         None.
*****************************************************************************/
extern void APS_ResetReq(APS_ResetReq_t *req);

/**************************************************************************//**
 brief APS system reset handler

 The function can be called only by ZDO. Must be called before any operation with APS.
*****************************************************************************/
extern void APS_Init(void);


/**************************************************************************//**
 \brief Makes APS allow processing of incoming commands

 After this function is called, APS is ready to process incoming commands
*****************************************************************************/
extern void APS_StartReq(APS_StartReq_t *req);

/**************************************************************************//**
 \brief Makes APS disallow processing of incoming commands

 After this function is called, APS does not process incoming commands
*****************************************************************************/
extern void APS_StopReq(APS_StopReq_t *req);
// \endcond
//============================================================================

/*****************************************************************************
  APS Data Manager API
*****************************************************************************/

/**************************************************************************//**
  \brief
    Sends data to a node of a network

  Unicast, broadcast, or multicast data can be sent by this function.
  Function returns the result of transaction via callback call with confirm (APS_DataConf_t)
  primitive pointer as parameter.

  \param[in] req  The APSDE-DATA.request (APS_DataReq_t) primitive pointer.
  \return         None.
*****************************************************************************/
extern void APS_DataReq(APS_DataReq_t *req);


#ifdef _APS_MULTICAST_
/*****************************************************************************
  APS Group Manager API
*****************************************************************************/

/**************************************************************************//**
  \brief
    Adds a group to APS

    This function adds the current device to the members of certain group.
    Function returns the result of transaction via callback call with confirm (APS_AddGroupConf_t)
    primitive pointer as parameter.

    \param[in] req  The APSME-ADD-GROUP.request (APS_AddGroupReq_t) primitive pointer.
    \return         None.
*****************************************************************************/
extern void APS_AddGroupReq(APS_AddGroupReq_t *req);

/**************************************************************************//**
  \brief
    Removes a group from APS

    This function removes the current device from the members of certain group.
    Function returns the result of transaction via callback call with confirm (APS_RemoveGroupConf_t)
    primitive pointer as parameter.

    \param[in] req  The APSME-REMOVE-GROUP.request (APS_RemoveGroupReq_t) primitive pointer.
    \return         None.
*****************************************************************************/
extern void APS_RemoveGroupReq(APS_RemoveGroupReq_t *req);

/**************************************************************************//**
  \brief
    Removes all groups from APS

    This function removes the current device from members of all groups.
    Function returns the result of transaction via callback call with confirm (APS_RemoveAllGroupsConf_t)
    primitive pointer as parameter.

    \param[in] req  The APSME-REMOVE-ALL-GROUPS.request (APS_RemoveAllGroupsReq_t) primitive pointer.
    \return         None.

*****************************************************************************/
extern void APS_RemoveAllGroupsReq(APS_RemoveAllGroupsReq_t *req);

//\cond internal
/***************************************************************************//**
 brief Finds certain group in APS

  This function searches for the certain group in the APS.

  param[in] groupAddr -  group address
  param[in] index     -  index value pointer will be filled if the group exists.
              Can be NULL if not required. If the group doesn't exist and there
              is a free APS group Table entry, its index will be used instead.
              If group specified doesn't exist and there are no free APS
              group Table entries, the 0xff value will be used instead;
  return    APS_GroupTableEntry_t*  pointer to group entry if found or NULL otherwise

*****************************************************************************/
APS_GroupTableEntry_t* APS_FindGroup(GroupAddr_t groupAddr, uint8_t *index);
//\endcond

/**************************************************************************//**
  \brief Check of an accessory to group.

  \param[in] groupAddr - a group address.
  \return 'true' if groupAddr is own group address or 'false' otherwise.

 *****************************************************************************/
extern bool APS_IsOwnGroup(ShortAddr_t addr);

//============================================================================
#endif


//\cond internal
#ifdef _SECURITY_
/*****************************************************************************
  APS Security Manager API
*****************************************************************************/
extern void APS_DeleteLinkKeyAndResetCounters(ExtAddr_t *extAddr);

/*****************************************************************************
  APS Master Key Set function
  Parameters: extAddr - extAddr pointer
              ket     - key material pointer
  Returns:    true - success
              false - no place
*****************************************************************************/
extern bool APS_SetMasterKey(ExtAddr_t *extAddr, uint8_t *key);

/*****************************************************************************
  APS Link Key Set function
  Parameters: extAddr - extAddr pointer
              ket     - key material pointer
  Returns:    true - success
              false - no place
*****************************************************************************/
extern bool APS_SetLinkKey(ExtAddr_t *extAddr, uint8_t *key);

#ifdef _HIGH_SECURITY_
//Key Establishment feature
extern void APS_EstablishKeyReq(APS_EstablishKeyReq_t *req);
extern void APS_EstablishKeyResp(APS_EstablishKeyResp_t *resp);
/*Must be provided*/
extern void APS_EstablishKeyInd(APS_EstablishKeyInd_t *ind);
//extern void APS_EstablishKeyConf(APS_EstablishKeyConf_t *conf);
#endif //#ifdef _HIGH_SECURITY_


//Transport Key feature
extern void APS_TransportKeyReq(APS_TransportKeyReq_t *req);
/*Must be provided*/
extern void APS_TransportKeyInd(APS_TransportKeyInd_t *ind);

//Update Device feature
extern void APS_UpdateDeviceReq(APS_UpdateDeviceReq_t *req);
/*Must be provided*/
extern void APS_UpdateDeviceInd(APS_UpdateDeviceInd_t *ind);


//Remove Device feature
extern void APS_RemoveDeviceReq(APS_RemoveDeviceReq_t *req);
/*Must be provided*/
extern void APS_RemoveDeviceInd(APS_RemoveDeviceInd_t *ind);

#ifdef _HIGH_SECURITY_
//Request Key feature
extern void APS_RequestKeyReq(APS_RequestKeyReq_t *req);
/*Must be provided*/
extern void APS_RequestKeyInd(APS_RequestKeyInd_t *ind);
#endif //#ifdef _HIGH_SECURITY_

//Switch Key feature
extern void APS_SwitchKeyReq(APS_SwitchKeyReq_t *req);
/*Must be provided*/
extern void APS_SwitchKeyInd(APS_SwitchKeyInd_t *ind);

#ifdef _HIGH_SECURITY_
//Autenticate feature
extern void APS_AuthenticateReq(APS_AuthenticateReq_t *req);
/*Must be provided*/
extern void APS_AuthenticateInd(APS_AuthenticateInd_t *ind);


//ApsKeyPairSet API
extern ApsKeyPairDescriptor_t *APS_GetKeyPairDescriptor(ExtAddr_t *address);
extern uint8_t *APS_GetMasterKey(ApsKeyPairDescriptor_t *keyPairDescriptor);
extern bool APS_SetMasterKey(ExtAddr_t *extAddr, uint8_t *key);
extern uint8_t *APS_GetLinkKey(ApsKeyPairDescriptor_t *keyPairDescriptor);
extern bool APS_SetLinkKey(ExtAddr_t *extAddr, uint8_t *key);
extern uint8_t *_APS_GetLinkKey(ExtAddr_t *extAddr);
extern bool APS_DeleteKeyPair(ExtAddr_t *extAddr);
#endif //#ifdef _HIGH_SECURITY_

#endif
// \endcond




// \cond internal
/*****************************************************************************
  NLDE-DATA.indication handler
  Parameters: req - primitive pointer
  Returns:    None
*****************************************************************************/
extern void NWK_DataInd(NWK_DataInd_t *req);


/*****************************************************************************
  NLDE-DATA.confirm handler
  Parameters: req - primitive pointer
  Returns:    None
*****************************************************************************/
extern void NWK_DataConf(NWK_DataConf_t *req);

/*****************************************************************************
  ZDO APSDE-DATA.indication handler
  Parameters: ind - primitive pointer
  Returns:    None
*****************************************************************************/
extern void APS_ZdoDataInd(APS_DataInd_t *ind);
// \endcond

extern void APS_CalculateTimes(void);

/*****************************************************************************
  Resets all entries in the key pair set descriptor table.
*****************************************************************************/
extern void APS_ResetKeyPairSet(void);

#endif  //#ifndef _APS_H


//eof aps.h
