#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include "avr/io.h"
#include "avr/interrupt.h"


#define ON_INTERVAL 50


ISR(TIMER0_OVF_vect);

void startSignal(void);
void stopSignal(void);

#endif //_SIGNAL_H_
