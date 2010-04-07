/**************************************************************************//**
  \file ncap_wilma.c

  \brief WILMA project NCAP

  \author
    Görög, Balázs

  \internal
    History:
	21 febr 2010 created
******************************************************************************/

#include <configServer.h>    // Config Server header
#include <taskManager.h>
#include <appFramework.h>    // Main stack types
#include <appTimer.h>        // Application timer header
#include <apsMacros.h>
#include <ncap_wilma.h>        // Own application header
#include <usart.h>
#include <uid.h>
#include <aps.h>             // Main APS header
#include <zdo.h>             // Main ZDO header


#include "nwkConfig.h"
#include "uart_buffer.h"
#include "messages.h"
#include "stdio.h"
#include "bspTII.h"

/***********************************************************************************
  Local variables
***********************************************************************************/
static AppState_t appState = APP_INITING_STATE;			// Current application state
static ZDO_StartNetworkReq_t networkParams;				// Request params for ZDO_StartNetworkReq

static HAL_AppTimer_t delaytimer;

/***********************************************************************************
  Local functions
***********************************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo); // Network start/join confirmation

//***********************************************************************************
// TIMER CALLBACK FUNCTIONS
//***********************************************************************************
void delaytimerFired(void)
{

	static unsigned char x=0;
	static char msg1[10];

	if(appState==APP_IN_NETWORK_STATE){
		msg1[0]=x;

//		sendMessage_wZ(&msg1[0],1,0);
//		sendCommand_wZ(&msg1[0],1,0);
		x++;
	}

}

//***********************************************************************************
// TII CALLBACK FUNCTIONS
//***********************************************************************************
void dataReadyCallback(uint8_t * data){
	uint8_t lth=data[0]&0x3F;
	if((lth<=40)&&(appState==APP_IN_NETWORK_STATE)){
		data[(data[0]&0x3F)+1]=0;
		sendMessage_wZ(data,lth,0);
	}
}


void tiiCMeasureCallback(void){
	sendCommand_wZ((uint8_t*)"cm",2,0);
}

void tiiStopCallback(void){
	sendCommand_wZ((uint8_t*)"st",2,0);
}

void tiiIDCallback(uint8_t * id){
	static uint8_t message[11];
	message[0]='i';
	message[1]=id[0];
	message[2]=id[1];
	message[3]=id[2];
	message[4]=id[3];
	message[5]=id[4];
	message[6]=id[5];
	message[7]=id[6];
	message[8]=id[7];
	message[9]=id[8];
	message[10]=0;
	sendCommand_wZ(&message[0],10,0);
}

void tiiNRCallback(uint8_t chnr){
	static uint8_t message[3];

	message[0]='n';
	message[1]=chnr;
	message[2]=0;

	sendCommand_wZ(&message[0],2,0);
}

//***********************************************************************************
// RADIO CALLBACK FUNCTIONS
//***********************************************************************************

//command indication callback function
void CommandIndication(APS_DataInd_t *indData){
	uint8_t channel,command;
	//extract channel and command byte
	channel=*(indData->asdu+0);
	command=*(indData->asdu+1);
	
	//execute command
	switch(command){
	case 'c':
		TIIstartCont(channel-'0', tiiCMeasureCallback);
		break;
	case 's':
		TIIstop(channel-'0',tiiStopCallback);
		break;
	case 'n':
	  	TIIgetCHNR(tiiNRCallback);
		break;
	case 'i':
		TIIgetID(tiiIDCallback);
		break;
	default:
		break;
	}
}



/********************************************************************
  Description: Application task handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void APL_TaskHandler(void)
{
  switch (appState)
  {
    // Node is in initial state
    case APP_INITING_STATE:
	  uartInit(NULL);
	  SendUART("\r\n-App Initializing\r\n");

	  initNwkParams();

	  #ifdef COORDINATOR
	  	SendUART("-Coord\r\n");
	  #else
	  	SendUART("-EndDev\r\n");
	  #endif

      appState = APP_NETWORK_STARTING_STATE; // Switch application state
      SYS_PostTask (APL_TASK_ID);
      break;


    // Node is starting/joining network
    case APP_NETWORK_STARTING_STATE:
      // Set network request parameters
      networkParams.ZDO_StartNetworkConf = ZDO_StartNetworkConf;		// Handler for network start confirmation
      ZDO_StartNetworkReq(&networkParams);							// Start/join network

	  //no task posting - only in ZDO_StartNetworkConf
      break;

	case APP_IN_NETWORK_STATE:
	  //waiting for messages
	  break;

    default:
      break;
  }
}



/********************************************************************
  Description: ZDO_StartNetwork primitive confirmation was received.

  Parameters: confirmInfo - confirmation information

  Returns: nothing.
********************************************************************/
void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo)
{
  SendUART("-Start Nwk Conf\r\n");

  // Network start/join was successful
  if (ZDO_SUCCESS_STATUS == confirmInfo->status)
  {
  	SendUART("-Nwk OK\r\n");

	//initialize communication
	registerEndpoints();
	initMessages(NULL,CommandIndication);//initialize messages

	//initialize tii interface
	openTII(dataReadyCallback);

	//start heartbeat timer
	delaytimer.interval=1000;
	delaytimer.mode=TIMER_REPEAT_MODE;
	delaytimer.callback=delaytimerFired;
	HAL_StartAppTimer(&delaytimer);

    appState = APP_IN_NETWORK_STATE; // Switch application state
  }else{
	SendUART("-Nwk NotOK\r\n");
  }

  SYS_PostTask(APL_TASK_ID);
}


/********************************************************************
  Description: update network status event handler

  Parameters: nwkParams - new network parameters

  Returns: nothing.
********************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  // Network is lost/left
  if (ZDO_NETWORK_LOST_STATUS == nwkParams->status)
  {

  }
}

/********************************************************************
  Description: dummy wakeup event handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void ZDO_WakeUpInd(void)
{

}

/********************************************************************
  Description: dummy sleep event handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void ZDO_SleepInd(void)
{
}


