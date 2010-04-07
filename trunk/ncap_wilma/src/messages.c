#include "messages.h"		 // own header


//***********************************************************************************************
//endpoint descriptors
//***********************************************************************************************
static SimpleDescriptor_t dataDescriptor = {DATA_ENDPOINT, WILMA_PROFILE, 1, 1, 0, 0 , NULL, 0, NULL};
static APS_RegisterEndpointReq_t dataParams;
static SimpleDescriptor_t commandDescriptor = {COMMAND_ENDPOINT, WILMA_PROFILE, 1, 1, 0, 0 , NULL, 0, NULL};
static APS_RegisterEndpointReq_t commandParams;

//***********************************************************************************************
//data request descriptors & payloads
//***********************************************************************************************
static APS_DataReq_t dataReq;        	// Request for APS_DataReq primitive
static APS_DataReq_t commandReq;        // Request for APS_DataReq primitive

static uint8_t dataPayload[MAX_MSG_LTH + APS_AFFIX_LENGTH]; // Buffer for application payload
static uint8_t commPayload[MAX_MSG_LTH + APS_AFFIX_LENGTH]; // Buffer for application payload

//**********************************************************************************************
//callback functions
//**********************************************************************************************
static void (*CommandCallback)(APS_DataInd_t *) 	= NULL;
static void (*DataCallback)(APS_DataInd_t *)		= NULL;


//**********************************************************************************************
// \brief Registers endpoints for command and data
//**********************************************************************************************
void registerEndpoints(void){
	//register data endpoint
	dataParams.simpleDescriptor = &dataDescriptor;
	dataParams.APS_DataInd = APS_DataInd;   	// Register handler for incoming data packets - internal function
    APS_RegisterEndpointReq(&dataParams); 		// Register endpoint

	//register command endpoint
	commandParams.simpleDescriptor = &commandDescriptor;
	commandParams.APS_DataInd = APS_CommandInd; // Register handler for incoming command packets - internal function
    APS_RegisterEndpointReq(&commandParams); 	// Register endpoint
}

//**********************************************************************************************
// \brief Initializes data structures for DataRequest functions (command, data channel)
// \param dataCallback Function pointer to the data indication callback function
// \param commandCallback Function pointer to the command indication callback function
//**********************************************************************************************
void initMessages(void (*dataCallback)(APS_DataInd_t *), void (*commandCallback)(APS_DataInd_t *)){
  //initialize variables for data channel
  dataReq.dstAddrMode             = APS_SHORT_ADDRESS; // Use short (NWK) addressing
  dataReq.txOptions.acknowledgedTransmission = 1;//APP_USE_APS_ACK; // Whether ACKs on application level are used
  dataReq.clusterId               = 1;

  dataReq.dstEndpoint             = DATA_ENDPOINT;       // Destination endpoint
  dataReq.profileId               = dataParams.simpleDescriptor->AppProfileId;
  dataReq.srcEndpoint             = DATA_ENDPOINT;
  
  dataReq.radius                  = 0;
  dataReq.APS_DataConf            = APS_DataConf;  // Confirm callback function

  DataCallback = dataCallback;

  //initialize variables for command channel
  commandReq.dstAddrMode             = APS_SHORT_ADDRESS; // Use short (NWK) addressing
  commandReq.txOptions.acknowledgedTransmission = 1;//APP_USE_APS_ACK; // Whether ACKs on application level are used
  commandReq.clusterId               = 1;

  commandReq.dstEndpoint             = COMMAND_ENDPOINT;       // Destination endpoint
  commandReq.profileId               = commandParams.simpleDescriptor->AppProfileId;
  commandReq.srcEndpoint             = COMMAND_ENDPOINT;
  
  commandReq.radius                  = 0;
  commandReq.APS_DataConf            = APS_DataConf;  // Confirm callback function

  CommandCallback = commandCallback;
}



//**********************************************************************************************
//  \brief Send data - data reques (data may contain zeros)
//  \param message Pointer to message
//  \param lth Message length
//  \param destAddr Destination node address
//**********************************************************************************************
void sendMessage_wZ(uint8_t *message, uint8_t lth, ShortAddr_t destAddr)
{
  unsigned char i;

  //if msg too long - leave it
  if(lth>MAX_MSG_LTH){
	return;
  }

  dataReq.dstAddress.shortAddress = destAddr;       // Destination NWK address - coordinator

  i=0;
  for(i=0;i<lth;i++){
	dataPayload[APS_ASDU_OFFSET+i] = *(message+i);
  }
  
  dataReq.asduLength = i;
  dataReq.asdu = (uint8_t *) &dataPayload[APS_ASDU_OFFSET];

  APS_DataReq(&dataReq);
}




//**********************************************************************************************
//  \brief Send command - data request (command may contain zeros)
//  \param message Pointer to message
//  \param lth Message length
//  \param destAddr Destination node address
//**********************************************************************************************
void sendCommand_wZ(uint8_t *message, uint8_t lth, ShortAddr_t destAddr)
{
  unsigned char i;

  //if msg too long - leave it
  if(lth>MAX_MSG_LTH){
	return;
  }

  commandReq.dstAddress.shortAddress = destAddr;       // Destination NWK address - coordinator

  i=0;
  for(i=0;i<lth;i++){
	commPayload[APS_ASDU_OFFSET+i] = *(message+i);
  }
  
  commandReq.asduLength = i;
  commandReq.asdu = (uint8_t *) &commPayload[APS_ASDU_OFFSET];

  APS_DataReq(&commandReq);
}




//**********************************************************************************************
//\brief Internal function for data request confirmation on data&command channels
//**********************************************************************************************
void APS_DataConf(APS_DataConf_t *confData)
{
//  SendUART("Data conf. ");
  if(confData->status==APS_SUCCESS_STATUS){
//	SendUART("OK\r\n");
  }else{
// 	SendUART("NOT OK\r\n");
  }
  SYS_PostTask(APL_TASK_ID);
}

//**********************************************************************************************
//\brief Internal indication of data receipt on data endpoint
//\params indData Descriptor of received data
//**********************************************************************************************
void APS_DataInd(APS_DataInd_t *indData)
{
  if(DataCallback!=NULL){
	DataCallback(indData);
  }
}

//**********************************************************************************************
//\brief Internal indication of data receipt on command endpoint
//\params indData Descriptor of received data
//**********************************************************************************************
void APS_CommandInd(APS_DataInd_t *indData)
{
  if(CommandCallback!=NULL){
	CommandCallback(indData);
  }
}

