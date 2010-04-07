/**************************************************************************//**
  \file coord_wilma.c

  \brief WILMA project coordinator

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
#include <coord_wilma.h>        // Own application header
#include <usart.h>
#include <uid.h>
#include <aps.h>             // Main APS header
#include <zdo.h>             // Main ZDO header


#include "nwkConfig.h"
#include "uart_buffer.h"
#include "messages.h"
#include "util/delay.h"
#include "stdio.h"

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




void delaytimerFired(void)
{
//	static unsigned char x=0;
//	static char msg1[10];

//	if(appState==APP_IN_NETWORK_STATE){
//		msg1[0]=x;

		//sendMessage_wZ(&msg1[0],1,0);
//		sendCommand_wZ(&msg1[0],1,7);
//		x++;
//	}
}

//macros for data&command indication - hex formatting
#define GET_BYTE(X) *(indData->asdu+X)
#define L_NIBBLE(X) (X&0x0F)
#define H_NIBBLE(X) ((X&0xF0)>>4)
#define TO_HEX(X) ((X>9)?(X+'A'-10):(X+'0')) 

//data indication callback function
void DataIndication(APS_DataInd_t *indData){
  static char buffer[2*MAX_MSG_LTH+5];
  unsigned char i;

  i=0;
  buffer[0]='<';
  while(i<indData->asduLength){
	buffer[2*i+1]=TO_HEX(H_NIBBLE(GET_BYTE(i)));
	buffer[2*i+2]=TO_HEX(L_NIBBLE(GET_BYTE(i)));	
	i++;
  }
  buffer[2*i+1]='>';
  buffer[2*i+2]='\r';
  buffer[2*i+3]='\n';
  buffer[2*i+4]=0;

  SendUART(&buffer[0]);
  SYS_PostTask(APL_TASK_ID);
}

//command indication callback function
void CommandIndication(APS_DataInd_t *indData){
  static char buffer[2*MAX_MSG_LTH+5];
  unsigned char i;

  i=0;
  buffer[0]='{';
  while(i<indData->asduLength){
	buffer[2*i+1]=TO_HEX(H_NIBBLE(GET_BYTE(i)));
	buffer[2*i+2]=TO_HEX(L_NIBBLE(GET_BYTE(i)));	
	i++;
  }
  buffer[2*i+1]='}';
  buffer[2*i+2]='\r';
  buffer[2*i+3]='\n';
  buffer[2*i+4]=0;

  SendUART(&buffer[0]);
  SYS_PostTask(APL_TASK_ID);
}


void UARTCommIndication(uint8_t chan, uint8_t comm){
	static unsigned char message[3];
	if(chan=='0'){		//only channel 0 is accepted in this version
		if(comm=='0'){	//if command is 0 - dongle detection message 00
			SendUART("[dongle here]\r\n");
		}else{			//if command is not 0 - send command
			message[0]=chan;
			message[1]=comm;
			message[2]=0;
			sendCommand_wZ(&message[0],2,7);
		}
	}else{				//if channel is not 0, error message
		SendUART("[invalid chn]\r\n");
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
	  uartInit(UARTCommIndication);
	  SendUART("\r\n[initializing]\r\n");

	  initNwkParams();

	  #ifdef COORDINATOR
	  	SendUART("[coord]\r\n");
	  #else
	  	SendUART("[end device]\r\n");
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
  // Network start/join was successful
  if (ZDO_SUCCESS_STATUS == confirmInfo->status)
  {
  	SendUART("[nwk started]\r\n");

	registerEndpoints();
	initMessages(DataIndication, CommandIndication);//initialize messages

    appState = APP_IN_NETWORK_STATE; // Switch application state
  }else{
	SendUART("[nwk not started]\r\n");
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
  static char mess[20];

  switch(nwkParams->status){
	case ZDO_NETWORK_LOST_STATUS:
		SendUART("[nwk lost]\r\n");
		//appState=APP_NO_NETWORK_STATE;
    	SYS_PostTask(APL_TASK_ID);
		break;
	case ZDO_CHILD_JOINED_STATUS:
		sprintf(&mess[0],"[childjoin: %04d]\r\n",nwkParams->childAddr.shortAddr);
		SendUART(&mess[0]);


		//start heartbeat timer
		delaytimer.interval=1000;
		delaytimer.mode=TIMER_REPEAT_MODE;
		delaytimer.callback=delaytimerFired;
		HAL_StartAppTimer(&delaytimer);

		break;
	case ZDO_CHILD_REMOVED_STATUS:
		sprintf(&mess[0],"[childremove: %04d]\r\n",nwkParams->childAddr.shortAddr);
		SendUART(&mess[0]);
		break;
	case ZDO_RESPONSE_WAIT_TIMEOUT_STATUS:
		SendUART("[resp timeout]\r\n");
		break;
	case ZDO_NETWORK_LEFT_STATUS:
		sprintf(&mess[0],"[nwk left]\r\n");
		SendUART(&mess[0]);

		appState=APP_NETWORK_STARTING_STATE;
		SYS_PostTask(APL_TASK_ID);
		break;
	default:
		sprintf(&mess[0],"[other: %d]\r\n",nwkParams->status);
		SendUART(&mess[0]);
		break;
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



