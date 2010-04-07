#ifndef APSMEMORYMANAGER_H_
#define APSMEMORYMANAGER_H_
#include <aps.h>
#include <nwk.h>
#include <appTimer.h>
#include <apsBindManager.h>
#include <apsDataManager.h>
#include <apsSecurityManager.h>

typedef enum
{
  APS_DM_DATA_BUFFER_TYPE,
  APS_DM_ACK_DATA_BUFFER_TYPE,
  APS_SM_FREE_BUFFER_TYPE,
  APS_SM_EKREQ_SKKE1_COMMAND_BUFFER_TYPE,
  APS_SM_EKREQ_SKKE3_COMMAND_BUFFER_TYPE,
  APS_SM_EKREQ_SSP_SKKE_BUFFER_TYPE,
  APS_SM_EKRESP_SSP_SKKE_BUFFER_TYPE,
  APS_SM_EKRESP_SKKE2_COMMAND_BUFFER_TYPE,
  APS_SM_EKRESP_SKKE4_COMMAND_BUFFER_TYPE,
  APS_SM_EKRO_SKKE_COMMAND_BUFFER_TYPE,

  APS_SM_AUR_SSP_AUTH_BUFFER_TYPE,
  APS_SM_AUR_CHALLENGE_COMMAND_BUFFER_TYPE,
  APS_SM_AUR_MAC_DATA_COMMAND_TYPE,

  APS_SM_AUI_SSP_AUTH_BUFFER_TYPE,
  APS_SM_AUI_CHALLENGE_COMMAND_BUFFER_TYPE,
  APS_SM_AUI_MAC_COMMAND_BUFFER_TYPE,

  APS_SM_SSPD_BUFFER_TYPE,

  APS_SM_UDR_COMMAND_BUFFER_TYPE,             //UpdateDevice command
  APS_SM_RDR_COMMAND_BUFFER_TYPE,             //RemoveDevice command
  APS_SM_RKR_COMMAND_BUFFER_TYPE,             //RequestKey command
  APS_SM_SKR_COMMAND_BUFFER_TYPE,             //RequestKey command
  APS_SM_TKR_COMMAND_BUFFER_TYPE,             //TransportKey command
  APS_SM_TKI_COMMAND_BUFFER_TYPE,
  APS_SM_COMMAND_IND_BUFFER_TYPE
} ApsBufferType_t;


typedef struct
{

//  APS_DataReq_t *apsDataReq; //pointer to appropriate object linked with
#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
  union
  {
    SSP_EncryptFrameReq_t sspEncryptReq;
    SSP_DecryptFrameReq_t sspDecryptReq;
  };
  APS_Status_t securityStatus;
#endif // _HIGH_SECURITY_
#endif // _SECURITY_

  uint8_t busy        /*:1*/;     //busy/free - 0 - free; 1 - busy
  uint8_t entryType   /*:2*/;//00b - NLDE-DATA.request primitive, 01b - NLDE-DATA.request primitive for Acknowledgement,
  uint8_t state       /*:5*/;
//  uint32_t timeout;

  union
  {
    uint8_t retriesCounter; //if request with ack requested data frame then it is a retries counter
    uint8_t index;          //if request with ack frame then it is a index of entry in APSAcknowledgementFramePool_t
  };

  NWK_DataReq_t nwkDataReq; //NLDE-DATA.request primitive

#ifdef _BINDING_
  ApsBindingDescriptor_t bindDescriptor;
#endif

} ApsDataDescriptor_t;

typedef struct
{
  void    *link; // request pointer
  uint8_t  type; /*ApsBufferType_t should be used*/
  uint32_t timeout;
  union
  {
    ApsDataDescriptor_t     dataDescriptor;
#ifdef _SECURITY_
    ApsCommandDescriptor_t  commandDescriptor;
#ifdef _HIGH_SECURITY_
    ApsSmSkkeDescriptor_t   skkeDescriptor;
    ApsSmAuthDescriptor_t   authDescriptor;
#endif //#ifdef _HIGH_SECURITY_
#endif // _SECURITY_
  };
} ApsBuffer_t;


typedef struct
{
  uint8_t size;
  uint8_t maxAckCounter;
  uint8_t maxReqCounter;
  uint8_t ackCounter;
  uint8_t reqCounter;
  ApsBuffer_t *entries;
} ApsDataManagerMemoryPool_t;

#ifdef _APS_FRAGMENTATION_

enum
{
    APS_PERMIT,     // - permitted
    APS_REJECT,     // - must be rejected
    APS_INDICATE   // - must be indicated
};

typedef struct
{
  uint8_t state;
  uint8_t *buffers;
  uint8_t *bufferLengths;
  uint8_t maxBlocksAmount;
  uint8_t totalLength;
  uint32_t timeout;
  uint8_t blocksAmount;
  uint8_t blocksReceived;
  uint8_t currentWindowStartBlockNumber;
  uint8_t ackBitfield;
  uint16_t srcAddress;
  uint8_t dstEndpoint;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;

BEGIN_PACK
  struct PACK
  {
    uint8_t lowLevelHeader[NWK_NSDU_OFFSET];
    ApduAcknowledgementFrame_t ackFrame;                     //Acknowledgement frame

    #if (NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
      uint8_t lowLevelFooter[NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET];
    #else
      #ifndef __GNUC__
        uint8_t lowLevelFooter[1];
      #else
        uint8_t lowLevelFooter[0];
      #endif
    #endif
  };
END_PACK
  NWK_DataReq_t nwkDataReq;
} ApsFragmentedReceiveDescriptor_t;

typedef struct
{
    uint8_t buffer[APS_ASDU_OFFSET + APS_MAX_ASDU_SIZE + APS_AFFIX_LENGTH - APS_ASDU_OFFSET];
    uint8_t blockNumber;
    uint8_t ackBlockNumber; // block number that expect ack, also it is first block number in the window
    uint8_t blocksToTransmit; // block in window requires to  transmit. 1 required transmission
    uint8_t blocksCount;
    uint8_t apsCounter;
    uint8_t retryCounter;
    HAL_AppTimer_t sendTimer; // timer that send frame per apsInterframeDelay
    ApsBuffer_t *block; // memory for block
} ApsFragmentedTransmitDescriptor_t;

#endif

#ifdef _SECURITY_
/*****************************************************************************
  APS Security Manager Buffer get function
  Parameters: bufferType - type of buffer (ApsSecurityBufferType_t should be used)
  Returns:    valid buffer pointer if free buffer exist,
              NULL - in other case
*****************************************************************************/
ApsBuffer_t *apsSmGetBuffer(uint8_t bufferType);
/*****************************************************************************
  APS Security Manager Buffer free function
  Parameters: buffer - buffer pointer
  Returns:    None
*****************************************************************************/

/*****************************************************************************
  APS Security Manager Buffer free function
  Parameters: buffer - buffer pointer
  Returns:    None
*****************************************************************************/
void apsSmFreeBuffer(ApsBuffer_t *buffer);
ApsBuffer_t *apsSmFindBuffer(ApsBuffer_t *buffer, uint8_t bufferType);
#endif // _SECURITY_
#endif /*APSMEMORYMANAGER_H_*/
