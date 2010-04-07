/**************************************************************************//**
  \file nwkSecurity.h

  \brief Network security interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    13/04/2009 Max Gekk - Created.
    15/08/2009 Max Gekk - Refactoring
 ******************************************************************************/
/* The NWK layer is responsible for the processing steps needed to securely
 * transmit outgoing frames and securely receive incoming frames. Upper layers
 * control the security processing operations by setting up the appropriate keys
 * and frame counters and establishing which security level to use.
 * ZigBee spec r17, 4.3, page 426.
 * */
#if !defined _NWK_SECURITY_H && defined _SECURITY_
#define _NWK_SECURITY_H

/******************************************************************************
                                  Includes section
 ******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <sspCommon.h>

/******************************************************************************
                                  Define(s) section
 ******************************************************************************/
#define NWK_PRECONFIGURED_NETWORK_KEY  0
/* Amount of incoming frame counters. */
#define NWK_IN_FRAMES_MAX  4
/* Amount of the network security material descriptors. */
#define NWK_SECURITY_DESCRIPTORS_SIZE  2


/******************************************************************************
                                    Types section
 ******************************************************************************/
/* The Incoming Frame Counter Descriptor. */
typedef struct
{
  /* Extended device address. */
  ExtAddr_t senderAddress;
  /* Incoming frame counter used for incoming frames. */
  uint32_t  inFrameCounter;
} NWK_InFrameCounterSet_t;

/* The Network Security Material Descriptor. */
typedef struct _NWK_SecMaterialDescriptor_t
{
  /* A sequence number assigned to a network key by the Trust Center and used
   * to distinguish network keys for purposes of key updates, and incoming
   * frame security operations. */
  uint8_t  keySeqNum;
  /* Outgoing frame counter used for outgoing frames. */
  uint32_t  outFrameCounter;
  /* Set of incoming frame counter values and corresponding device addresses. */
  NWK_InFrameCounterSet_t  inFrameCounterSet[NWK_IN_FRAMES_MAX];
  /* The actual value of the key. */
  uint8_t  key[SECURITY_KEY_SIZE];
} NWK_SecMaterialDescriptor_t;

/* Set of network security material descriptors. */
typedef struct _NWK_SecMaterialSet_t
{
  /* Descriptors with network security materials. */
  NWK_SecMaterialDescriptor_t  descriptors[NWK_SECURITY_DESCRIPTORS_SIZE];
  /* Current amount of network security material descriptors. */
  uint8_t  size;
} NWK_SecMaterialSet_t;

/* Security-Related NIB Attributes */
typedef struct _NWK_SecurityIB_t
{
  /* The security level for outgoing and incoming NWK frames. */
  uint8_t  securityLevel;
  /* Set of network security material descriptors capable of maintaining
   * an active and alternate network key. */
  NWK_SecMaterialSet_t  securityMaterialSet;
  /* The sequence number of the active network key in securityMaterialSet. */
  uint8_t  activeKeySeqNumber;
  /* Indicates whether incoming NWK frames must be all checked for freshness
   * when the memory for incoming frame counts is exceeded.*/
  bool  allFresh;
  /* Indicates whether security shall be applied to incoming and outgoing NWK data frames. */
  bool  secureAllFrames;
} NWK_SecurityIB_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reseting the network security subsystem.
  \param powerFailure - enables or disables the power failure feature.
  \return none.
 ******************************************************************************/
void  NWK_ResetSecurityIB(const bool powerFailure);

/**************************************************************************//**
  \brief This function gives access to SIB.
  \return Pointer to the NWK security information base.
 ******************************************************************************/
NWK_SecurityIB_t*  NWK_GetSecurityIB(void);

/**************************************************************************//**
  \brief Get value of the nwkSecurityLevel attribute. ZigBee spec r17, page 344, 
    Table 3.44.
  \return Current value of nwkSecurityLevel.
 ******************************************************************************/
uint8_t NWK_GetSecurityLevel(void);

/**************************************************************************//**
  \brief Update of the nwkSecurityLevel attribute. ZigBee spec r17, page 344, 
    Table 3.44.
  \param level - a new value of nwkSecurityLevel.
 ******************************************************************************/
void  NWK_SetSecurityLevel(const uint8_t level);

/**************************************************************************//**
  \brief Getting value of nwkSecureAllFrames attribute.
    ZigBee spec r17, page 344, Table 3.44.
  \return Current value of nwkSecureAllFrames.
 ******************************************************************************/
bool  NWK_GetSecureAllFrames(void);

/**************************************************************************//**
  \brief Getting value of nwkActiveKeySeqNumber attribute. 
     ZigBee spec r17, page 344, Table 3.44.
  \return Current value of nwkActiveKeySeqNumber.
 ******************************************************************************/
uint8_t  NWK_GetActiveKeySeqNumber(void);

/**************************************************************************//**
  \brief  Getting the active security material descriptor.
  \return Pointer to the active security material descriptor.
 ******************************************************************************/
NWK_SecMaterialDescriptor_t* NWK_GetActiveKeyDescriptor(void);

/**************************************************************************//**
  \brief Getting the incoming frame counter by extended address.
  \param keyDescriptor - pointer to the security material descriptor.
  \param srcExtAddr - pointer to an extended source address.
  \return Value of incoming frame counter.
 ******************************************************************************/
uint32_t* NWK_GetInFrameCounter(NWK_SecMaterialDescriptor_t  *const keyDescriptor,
  const ExtAddr_t  *const srcExtAddr);

/**************************************************************************//**
  \brief Update the incoming frame counter.
  \param keyDescriptor - pointer to the security material descriptor.
  \param srcExtAddr - pointer to an extended source address.
  \param newValue - a new value of the incoming frame counter.
  \return 'true' if operation was completed successfully otherwise 'false'.
 ******************************************************************************/
bool NWK_SetInFrameCounter(NWK_SecMaterialDescriptor_t  *const keyDescriptor,
  const ExtAddr_t  *const srcExtAddr, const uint32_t  *const newValue);

/**************************************************************************//**
  \brief Set a new network key.
  \param key - a new network security key.
  \param keySeqNumber - key sequence number.
  \return 'true' if operation was completed successfully otherwise 'false'.
 ******************************************************************************/
bool NWK_SetKey(uint8_t *const key, const uint8_t keySeqNumber);

/**************************************************************************//**
  \brief Network key switching.
  \param keySeqNumber - key sequence number.
  \return 'true' if operation was completed successfully otherwise 'false'.
 ******************************************************************************/
bool NWK_SwitchKey(const uint8_t keySeqNumber);

/**************************************************************************//**
  \brief Find a security material descriptor by a sequence number.
  \param seqNum - a sequence number.
  \return Pointer to a security material descriptor if searching was completed 
     successfully otherwise NULL.
 ******************************************************************************/
NWK_SecMaterialDescriptor_t*  NWK_FindSecMaterialDescriptor(const uint8_t seqNum);

/**************************************************************************//**
  \brief Authenticate a child node.
  \param extAddr - pointer to the extended address of child.
  \return None.
 ******************************************************************************/
void  NWK_AuthenticateNeighbor(ExtAddr_t *extAddr);

#endif  /* _NWK_SECURITY_H and _SECURITY_ */
/* eof nwkSecurity.h */
