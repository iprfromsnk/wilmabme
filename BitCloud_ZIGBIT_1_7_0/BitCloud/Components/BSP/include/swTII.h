#ifndef _TII_H_
#define _TII_H_

#include <types.h>

#define TII_BUFF_LTH 2

#define BSY_NOERR	0x00		//RDY=0 ERR=0
#define BSY_ERR		0x40		//RDY=0 ERR=1
#define RDY_NOERR	0x80		//RDY=1 ERR=0
#define RDY_ERR		0xC0		//RDY=1 ERR=1


//app layer requests
result_t openSWTII(void (*dataReadyCallback)(uint8_t * data));
void swTIIgetCHNR(void (* tiiCallback)(uint8_t data));
void swTIIgetID(void (* tiiCallback)(uint8_t * chnr));
void swTIImeasure(unsigned char chNr, void (* tiiCallback)(void));
void swTIIstartCont(unsigned char chNr, void (* tiiCallback)(void));
void swTIIstop(unsigned char chNr, void (* tiiCallback)(void));

//internal callback
//void irqCallback(void);

#endif