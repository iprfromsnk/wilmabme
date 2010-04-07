/*************************************************************************//**
  \file apsSecurityManager.h

  \brief APS Security Manager header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSECURITYMANAGER_H
#define _APSSECURITYMANAGER_H

#ifdef _SECURITY_


/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <aps.h>
#include <nwk.h>
#include <sspSkke.h>
#include <sspSfp.h>
#include <sspAuthentic.h>
#include <apsDataManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define APS_MAX_MESSAGE_INTEGRITY_CODE_SIZE   16 /*16 bytes == 128 bit*/
#define APS_SM_KEY_SIZE                       16

#define GET_MIC_SIZE_BY_SECURITY_LEVEL(securityLevelIdentifier)   \
        ((1 << ((securityLevelIdentifier & 0x03) + 1)) & (~0x03))



#define APS_SM_INVALID_FRAME_COUNTER_VALUE  (0xffffffffL)

#define APS_SM_BROADCAST_EXT_ADDRESS                        0xffffffffffffffffLL
#define APS_SM_BROADCAST_ALL_EXT_ADDRESS                    0xffffffffffffffffLL
#define APS_SM_BROADCAST_RX_ON_WHEN_IDLE_EXT_ADDRESS        0xfffffffffffffffdLL
#define APS_SM_BROADCAST_ALL_ROUTERS_EXT_ADDRESS            0xfffffffffffffffcLL
#define APS_SM_BROADCAST_LOW_POWER_ROUTERS_EXT_ADDRESS      0xfffffffffffffffbLL

#define APS_SM_UNIVERSAL_TRUST_CENTER_EXT_ADDRESS           0xfffffffffffffffaLL

#define APS_SM_INVALID_EXT_ADDRESS	        0x0000000000000000LL
#define APS_SM_DUMMY_STATE                  0xff


/******************************************************************************
                   Types section
******************************************************************************/

typedef enum _ApsSecurityComponentId_t
{
  APS_SM_EKREQ_ID = 0x00,   //Establish Key Request (initiator)
  APS_SM_EKRESP_ID,         //Establish Key Responder
  APS_SM_EKRO_ID,           //Establish Key Router
  APS_SM_TKR_ID,            //Transport Key Request
  APS_SM_TKI_ID,            //Transport Key Indication
  APS_SM_UDR_ID,            //Update Device Request
  APS_SM_UDI_ID,            //Update Device Indication
  APS_SM_RDR_ID,            //Remove Device Request
  APS_SM_RDI_ID,            //Remove Device Indication
  APS_SM_RKR_ID,            //Request Key Request
  APS_SM_RKI_ID,            //Request Key Indication
  APS_SM_SKR_ID,            //Switch Key Request
  APS_SM_SKI_ID,            //Switch Key Indication
  APS_SM_AUR_ID,            //Authenticate Request
  APS_SM_AUI_ID,            //Authenticate Indication
  APS_SM_MM_ID,
  APS_SM_SSP_ID,
  APS_SM_DUMMY_ID
} ApsSecurityComponentId_t;

/*
typedef struct PACK
{
  ExtAddr_t deviceAddress;
  uint8_t masterKey[16];
  uint8_t linkKey[16];
  uint32_t outFrameCounter;
  uint32_t inFrameCounter;
} ApsKeyPairDescriptor_t;
*/

#ifdef _HIGH_SECURITY_
typedef struct _ApsDeviceKeyPairSet_t
{
  uint8_t amount;
  ApsKeyPairDescriptor_t *keyPairDescriptors;
} ApsDeviceKeyPairSet_t;
#endif //#ifdef _HIGH_SECURITY_


BEGIN_PACK
typedef struct PACK _ApsSKKECommandPayload_t
{
  ExtAddr_t initiatorAddress;
  ExtAddr_t responderAddress;
  uint8_t data[APS_SM_KEY_SIZE];
} ApsSKKECommandPayload_t;

/*TransportKey*/
typedef struct PACK
{
  uint8_t key[APS_SM_KEY_SIZE];
  ExtAddr_t dstAddr;
  ExtAddr_t srcAddr;
} ApsTrustCenterKeyDescriptor_t;

typedef struct PACK
{
  uint8_t key[APS_SM_KEY_SIZE];
  uint8_t sequenceNumber;
  ExtAddr_t dstAddr;
  ExtAddr_t srcAddr;
} ApsNetworkKeyDescriptor_t;

typedef struct PACK
{
  uint8_t key[APS_SM_KEY_SIZE];
  ExtAddr_t partnerAddr;
  uint8_t initiatorFlag;
} ApsAppKeyDescriptor_t;

typedef struct PACK
{
  uint8_t keyType;
  union PACK
  {
    ApsTrustCenterKeyDescriptor_t   trustCenterKey;
    ApsNetworkKeyDescriptor_t       networkKey;
    ApsAppKeyDescriptor_t           appKey;
  };
} ApsTransportKeyCommandPayload_t;

typedef struct PACK
{
  ExtAddr_t deviceAddress;
  ShortAddr_t deviceShortAddress;
  uint8_t status;
} ApsUpdateDeviceCommandPayload_t;

typedef struct PACK
{
  ExtAddr_t childAddress;
} ApsRemoveDeviceCommandPayload_t;

typedef struct PACK
{
  uint8_t keyType;
  ExtAddr_t partnerAddress;
} ApsRequestKeyCommandPayload_t;

typedef struct PACK
{
  uint8_t sequenceNumber;
} ApsSwitchKeyCommandPayload_t;


typedef struct PACK
{
  uint8_t keyType;
  uint8_t keySeqNumber;
  ExtAddr_t initiator;
  ExtAddr_t responder;
  uint8_t challenge[APS_SM_KEY_SIZE];
} ApsAuthChallengeCommandPartWithKeySecNumber_t;

typedef struct PACK
{
  uint8_t keyType;
  ExtAddr_t initiator;
  ExtAddr_t responder;
  uint8_t challenge[APS_SM_KEY_SIZE];
} ApsAuthChallengeCommandPartWithoutKeySecNumber_t;

typedef enum
{
  APS_AUTH_ACTIVE_NETWORK_KEY_TYPE  = 0x00,
  APS_AUTH_LINK_KEY_TYPE            = 0x01
} ApsAuthChallengeKeyType_t;

typedef struct PACK
{
  union PACK
  {
    ApsAuthChallengeCommandPartWithKeySecNumber_t keySeq;
    ApsAuthChallengeCommandPartWithoutKeySecNumber_t noKeySeq;
  };
} ApsAuthChallengeCommandPayload_t;

typedef struct PACK
{
  uint8_t mac[APS_SM_KEY_SIZE];
  uint8_t dataType;
  uint32_t data;
} ApsAuthMacAndDataCommandPayload_t;

typedef struct PACK
{
  ApduCommandHeader_t header;
  union PACK
  {
    ApsSKKECommandPayload_t           skke;           //SKKE-command
    ApsTransportKeyCommandPayload_t   transportKey;   //TransportKeyCommand
    ApsUpdateDeviceCommandPayload_t   updateDevice;   //UpdateDeviceCommand
    ApsRemoveDeviceCommandPayload_t   removeDevice;   //RemoveDeviceCommand
    ApsRequestKeyCommandPayload_t     requestKey;     //RequestKeyCommand
    ApsSwitchKeyCommandPayload_t      switchKey;      //SwitchKeyCommand
    ApsAuthChallengeCommandPayload_t  authChallenge;
    ApsAuthMacAndDataCommandPayload_t authMacData;
  } payload;
} ApsCommand_t;

typedef struct PACK
{
  uint8_t lowLevelHeader[NWK_NSDU_OFFSET];
  ApduCommandHeader_t header;

  union PACK
  {
    ApsSKKECommandPayload_t           skke;           //SKKE-command
    ApsTransportKeyCommandPayload_t   transportKey;   //TransportKeyCommand
    ApsUpdateDeviceCommandPayload_t   updateDevice;   //UpdateDeviceCommand
    ApsRemoveDeviceCommandPayload_t   removeDevice;   //RemoveDeviceCommand
    ApsRequestKeyCommandPayload_t     requestKey;     //RequestKeyCommand
    ApsSwitchKeyCommandPayload_t      switchKey;      //SwitchKeyCommand
    ApsAuthChallengeCommandPayload_t  authChallenge;
    ApsAuthMacAndDataCommandPayload_t authMacData;
  } payload;
  #if (NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
    uint8_t lowLevelFooter[NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET];
  #else
    uint8_t lowLevelFooter[1];
  #endif
} ApsCommandFrame_t;
END_PACK

typedef struct
{
  union
  {
    SSP_EncryptFrameReq_t sspEncryptReq;
    SSP_DecryptFrameReq_t sspDecryptReq;
  };

  ShortAddr_t         shortAddr;
  ExtAddr_t           extAddr;
  //uint32_t            timeout;
  union
  {
    NWK_DataReq_t     nwkDataReq;
    NWK_DataInd_t     nwkDataInd;
  };
  ApsCommandFrame_t   commandFrame;
} ApsCommandDescriptor_t;

#ifdef _HIGH_SECURITY_
typedef struct
{
  uint8_t state;
  ShortAddr_t shortAddr;
  ExtAddr_t extAddr;
  ApsKeyPairDescriptor_t *keyPairDescriptor;
  void *transaction;
  uint32_t timeout;
  //APS_EstablishKeyReq_t req;
  SSP_CalculateSkkeParamsReq_t skkeReq;
} ApsSmSkkeDescriptor_t;

typedef struct
{
  uint8_t state;
  ShortAddr_t shortAddr;
  ExtAddr_t extAddr;
  uint8_t keySeqNumber;
  uint32_t initiatorFrameCounter;
  uint32_t responderFrameCounter;
  NWK_SecMaterialDescriptor_t *keyDescriptor;
  APS_AuthenticateReq_t *transaction;
  uint32_t timeout;
  SSP_CalculateAuthenticParamsReq_t authReq;
} ApsSmAuthDescriptor_t;
#endif //#ifdef _HIGH_SECURITY_

BEGIN_PACK
typedef struct PACK
{
  uint8_t securityLevel     :3;
  uint8_t keyIdentifier     :2;
  uint8_t extendedNonce     :1;
  uint8_t resetved          :2;
} ApsSecurityControlField_t;

typedef struct PACK _ApsSecurityAuxillaryFrameHeader_t
{
  ApsSecurityControlField_t securityControl;
  uint32_t                  frameCounter;
  //uint64_t                  srcAddress;
  uint8_t                   keySequenseNumber;
} ApsSecurityAuxillaryFrameHeader_t;

typedef struct PACK _ApsSecurityMessageIntegrityCodeField_t
{
  uint8_t code[APS_MAX_MESSAGE_INTEGRITY_CODE_SIZE];
} ApsSecurityMessageIntegrityCodeField_t;
END_PACK

/******************************************************************************
                   Constants section
******************************************************************************/

typedef enum _ApsSecurityCommandId_t
{
  APS_CMD_SKKE_1_ID                = 0x01,
  APS_CMD_SKKE_2_ID                = 0x02,
  APS_CMD_SKKE_3_ID                = 0x03,
  APS_CMD_SKKE_4_ID                = 0x04,
  APS_CMD_TRANSPORT_KEY_ID         = 0x05,
  APS_CMD_UPDATE_DEVICE_ID         = 0x06,
  APS_CMD_REMOVE_DEVICE_ID         = 0x07,
  APS_CMD_REQUEST_KEY_ID           = 0x08,
  APS_CMD_SWITCH_KEY_ID            = 0x09,
  APS_CMD_EA_INIT_CHLNG_ID         = 0x0a,
  APS_CMD_EA_RSP_CHLNG_ID          = 0x0b,
  APS_CMD_EA_INIT_MAC_DATA_ID      = 0x0c,
  APS_CMD_EA_RSP_MAC_DATA_ID       = 0x0d,
  APS_CMD_TUNNEL_ID                = 0x0e
} ApsSecurityCommandId_t;

/******************************************************************************
                   External variables section
******************************************************************************/
#ifdef _HIGH_SECURITY_
extern ApsDeviceKeyPairSet_t apsDeviceKeyPairSet;
#endif //#ifdef _HIGH_SECURITY_
/******************************************************************************
                   Prototypes section
******************************************************************************/




/*****************************************************************************
  Make a reset of APS Security Manager
  Parameters: powerFailure - is powerFailure feature activated
  Returns:    None
*****************************************************************************/
extern void apsSecurityManagerReset(bool powerFailure);

/*****************************************************************************
  APS Security Manager Process function
  Parameters: None
  Returns: None
*****************************************************************************/
extern void apsSecurityManagerProcess(void);


extern bool apsCommandReceiveProcess(NWK_DataInd_t *ind);

extern void apsSmPostTask(uint8_t apsSmComponentId);

extern uint8_t apsSmGetFreeBuffersAmount(void);
extern void apsSmMakeCommandHeader(ApduCommandHeader_t *header, uint8_t commandId);
extern Neib_t *apsFindNeibByExtAddr(ExtAddr_t *extAddr);
extern Neib_t *apsFindNeibByShortAddr(ShortAddr_t *shortAddr);
extern uint32_t apsGetPollPeriod(void);

extern ShortAddr_t apsGetParentShortAddr(void);
extern uint32_t apsGetSecurityTimeout(void);
extern bool apsIsKeyValid(uint8_t *key);

#ifdef _HIGH_SECURITY_
//extern void apsDecryptedCommandReceiveProcess(ApsSmBuffer_t *buffer);
//extern void apsSmSetTimeout(ApsSmBuffer_t *buffer, uint32_t timeout);
#endif //#ifdef _HIGH_SECURITY_

extern void apsSmAddToAddrMapTable(ExtAddr_t *extAddr, ShortAddr_t *shortAddr);
/******************************************************************************
                   Inline static functions section
******************************************************************************/




#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSECURITYMANAGER_H

//eof apsSecurityManager.h
