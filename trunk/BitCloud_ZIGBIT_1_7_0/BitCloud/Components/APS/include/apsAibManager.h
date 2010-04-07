/*************************************************************************//**
  \file apsAibManager.h

  \brief APS AIB Manager header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    06/06/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSAIBMANAGER_H
#define _APSAIBMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <aps.h>


/******************************************************************************
                   Define(s) section
******************************************************************************/
//APS AIB Binding Table size
#define AIB_BINDING_TABLE_SIZE  0

//APS AIB Group Table size
#define APS_GROUP_TABLE_SIZE    0

#define APS_NONMEMBER_RADIUS_ATTRIBUTE_MAX_VALUE  0x07

#define APS_PHY_CHANNEL_MIN_VALUE                 (0x0bL)
#define APS_PHY_CHANNEL_MAX_VALUE                 (0x1aL)
#define APS_CHANNEL_MASK_MIN_VALUE                APS_PHY_CHANNEL_MIN_VALUE
#define APS_CHANNEL_MASK_MAX_VALUE                (((2^(APS_PHY_CHANNEL_MAX_VALUE + 1 - APS_PHY_CHANNEL_MIN_VALUE)) - 1) << APS_PHY_CHANNEL_MIN_VALUE)

#define APS_USE_EXTENDED_PANID_MAX_VALUE          0xfffffffffffffffeLL
#define APS_INVALID_TRUST_CENTER_EXT_ADDRESS      0xffffffffffffffffLL

#define APS_SM_SECURITY_TIMEOUT                   1000uL

/******************************************************************************
                   Types section
******************************************************************************/

/*****************************************************************************
  APS AIB
*****************************************************************************/
typedef struct
{
  //AIB standard attributes
  void *apsBindingTable;
  //bool apsDesignatedCoordinator;  //Deleted because duplicated in Config Server
  //uint32_t apsChannelMask;        //Deleted because duplicated in Config Server
  //uint64_t apsUseExtendedPANID;   //Deleted because duplicated in Config Server
  APS_GroupTable_t *apsGroupTable;
  uint8_t apsNonmemberRadius;
  APS_AibPermissionsConfiguration_t apsPermissionsConfiguration;
  bool apsUseInsecureJoin;
  uint16_t apsInterframeDelay;

  //AIB security attributes
  void *apsDeviceKeyPairSet;
  ExtAddr_t apsTrustCenterAddress;
  uint32_t apsSecurityTimeOutPeriod;

} ApsAib_t;


/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/

/*****************************************************************************
 APS AIB
*****************************************************************************/
extern ApsAib_t apsAIB;


/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  Returns the value pointer of a AIB attribute
  Parameters: id - AIB attribute identifier
              aibAttribute - the pointer to attribute value will be specified
                             during the process
              aibAttributeLength - the pointer to attribute size will be
                                   specified during the processing
  Returns:  true - aibAttributeLength and aibAttribute will contain the real value
            false - invalid parameter
*****************************************************************************/
bool apsGetAibAttribute(APS_AibAttributeId_t id, APS_AibAttribute_t *aibAttribute,
                        uint16_t *aibAttributeLength);


/*****************************************************************************
  Sets the value of a AIB attribute
  Parameters: id - AIB attribute identifier
              aibAttributeValue - attribute value
              aibAttributeLength - attribute value size
  Returns: APS_SUCCESS_STATUS - AIB attribute value is changed successfully
           APS_INVALID_PARAMETER_STATUS - parameter value or length is incorrect
           APS_UNSUPPORTED_ATTRIBUTE_STATUS - if parameter ID unknown
*****************************************************************************/
APS_Status_t apsSetAibAttribute(APS_AibAttributeId_t id, APS_AibAttribute_t aibAttributeValue,
                                uint16_t aibAttributeLength);


/*****************************************************************************
  Reset AIB
  Parameters: options - reset mode (0 - clear AIB and set to default,
                        1 - restore AIB from EEPROM)
  Returns: None
*****************************************************************************/
void apsResetAibManager(void);


/*****************************************************************************
  APS Bind Manager Process function
  Parameters: None
  Returns: None
*****************************************************************************/
void apsAIBManagerProcess(void);


/******************************************************************************
                   Inline static functions section
******************************************************************************/


#endif  //#ifndef _APSAIBMANAGER_H

//eof apsAibManager.h
