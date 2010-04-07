#ifndef _TII_H_
#define _TII_H_

#include <types.h>

#define TII_BUFF_LTH 40



//app layer requests
result_t openTII(void (*dataReadyCallback)(uint8_t * data));
void TIIgetCHNR(void (* tiiCallback)(uint8_t data));
void TIIgetID(void (* tiiCallback)(uint8_t * chnr));
void TIImeasure(unsigned char chNr, void (* tiiCallback)(void));
void TIIstartCont(unsigned char chNr, void (* tiiCallback)(void));
void TIIstop(unsigned char chNr, void (* tiiCallback)(void));

//internal callback
void spiCallback(void);
void irqCallback(void);

//internal functions
void WAKEUP_high(void);
void WAKEUP_low(void);
inline void goIdle(void);

#endif