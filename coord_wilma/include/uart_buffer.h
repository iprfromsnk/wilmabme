#ifndef _UART_BUFFER_H_
#define _UART_BUFFER_H_

#include <types.h>	//uint16_t miatt


#define BUFFER_SIZE 7

typedef struct{
	unsigned char *mp;
	unsigned char lth;
}UARTmessage;



void uartInit(void (*uartCommand)(uint8_t, uint8_t));
void uartClose(void);


void UARTSendNext(void);
void UARTSendConfirm(void);
void SendUART(char *mp);


//buffering functions
void addMessageToBuffer(unsigned char * message, unsigned char length);
UARTmessage getNextMessageFromBuffer(void);
void increase_wptr(void);
void increase_rptr(void);
unsigned char get_buffer_lth(void);

unsigned char IsUARTBusy(void);

void rxCallback(uint16_t len);

#endif //_UART_BUFFER_H_
