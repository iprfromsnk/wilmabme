#include "uart_buffer.h"

#include "nwkConfig.h"
#include "messages.h"

#include <usart.h>


static HAL_UsartDescriptor_t appUartDescriptor; // UART descriptor (required by stack)
static UARTmessage UARTbuffer[BUFFER_SIZE];

#define INPUT_BUFFER_SIZE 40
static char inputBuffer[INPUT_BUFFER_SIZE];

static bool UART_inuse=false;

//indication for command receipt on uart
static void (*UARTCommand)(uint8_t, uint8_t) = NULL;

//*************************************************************
//************ interface for upper layer ******************
//*************************************************************

//**************************************************************
//	\brief Initialize UART descriptor structure and open UART
//	\param uartCommand Callback function pointer for UART command receipt
//**************************************************************
void uartInit(void (*uartCommand)(uint8_t, uint8_t))
{
  appUartDescriptor.tty             = USART_CHANNEL_1;
  appUartDescriptor.mode            = USART_MODE_ASYNC;
  appUartDescriptor.baudrate        = USART_BAUDRATE_38400;
  appUartDescriptor.dataLength      = USART_DATA8;
  appUartDescriptor.parity          = USART_PARITY_NONE;
  appUartDescriptor.stopbits        = USART_STOPBIT_1;
  appUartDescriptor.txBuffer        = NULL;
  appUartDescriptor.txBufferLength  = 0;
#ifdef COORDINATOR
  appUartDescriptor.rxCallback      = rxCallback;
  appUartDescriptor.rxBuffer        = &inputBuffer[0];
  appUartDescriptor.rxBufferLength  = INPUT_BUFFER_SIZE;
#else
  appUartDescriptor.rxCallback      = NULL;
  appUartDescriptor.rxBuffer        = NULL;
  appUartDescriptor.rxBufferLength  = 0;
#endif
  appUartDescriptor.txCallback      = UARTSendConfirm;
  appUartDescriptor.flowControl     = USART_FLOW_CONTROL_NONE;

//store indication pointer
  UARTCommand=uartCommand;

  HAL_OpenUsart(&appUartDescriptor);
}

void uartClose(void)
{
	 HAL_CloseUsart(&appUartDescriptor);
}

void SendUART(char *mp){
	unsigned char lth;
	for(lth=0;lth<60;lth++){
		if((mp[lth]==0)&&(lth>0)){
			addMessageToBuffer((unsigned char *)mp,lth);
			UARTSendNext();
			return;
		}
	}

	return;
}

//***************************************************
//*****inner functions - resource handling***************
//***************************************************
void UARTSendNext(void){
	UARTmessage x;

	if(UART_inuse==true){		//if locked
		return;
	}
	if(get_buffer_lth()==0){    //if nothing in buffer
		return;
	}

	x=getNextMessageFromBuffer();
	if(x.mp==0){				//ervenyes uzenet pointere nem 0
		return;
	}

	HAL_WriteUsart(&appUartDescriptor,x.mp,x.lth);	//use
	UART_inuse=true;								//lock
}


void UARTSendConfirm(void){
	UART_inuse=false;					//free resource
	if(get_buffer_lth()>0){				//if other messages left
		UARTSendNext();					//send them
	}
}


//*******************************************************************
//************BUFFERING FUNCTIONS*********************************
//*******************************************************************
static unsigned char buffer_wptr=0;
static unsigned char buffer_rptr=0;
static unsigned char buffer_lth=0;

void addMessageToBuffer(unsigned char * message, unsigned char length){
	UARTbuffer[buffer_wptr].mp=message;
	UARTbuffer[buffer_wptr].lth=length;

	if(buffer_lth==BUFFER_SIZE){
		increase_wptr();
		buffer_rptr=buffer_wptr;
	}else{
		buffer_lth++;
		increase_wptr();
	}
}
UARTmessage getNextMessageFromBuffer(void){
	UARTmessage x;

	x=UARTbuffer[buffer_rptr];
	UARTbuffer[buffer_rptr].mp=0;//hogy biztosan ne hajtsa vegre megegyszer

	if(buffer_lth>0){
		increase_rptr();
		buffer_lth--;
	}else{
		x.mp=0;
	}
	return x;
}

void increase_wptr(void){
	buffer_wptr=(buffer_wptr<BUFFER_SIZE-1)?(buffer_wptr+1):0;
}

void increase_rptr(void){
	buffer_rptr=(buffer_rptr<BUFFER_SIZE-1)?(buffer_rptr+1):0;
}
unsigned char get_buffer_lth(void){
	return buffer_lth;
}


////////////////////////////////////////////////////////////////////
unsigned char IsUARTBusy(void){
	if(get_buffer_lth()>0){
		return 1;
	}

	if(UART_inuse==true){
		return 1;
	}

	return 0;
}


//*******************************************************************
//	\brief Internal callback function for command indication
//  
//	Each command consists of 2 bytes in this software version. If 2 bytes
//  had been received, the registered callback function of the upper layer
//  is called.
//*******************************************************************
void rxCallback(uint16_t len){
	static unsigned char message[2];
	if(len==2){
		HAL_ReadUsart(&appUartDescriptor,&message[0],len);
		if(UARTCommand!=NULL){
			UARTCommand(message[0],message[1]);
		}
	}	
}
