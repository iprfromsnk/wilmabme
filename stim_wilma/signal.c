#include "signal.h"
#include "leds.h"




volatile unsigned char ledcntr=0;

ISR(TIMER0_OVF_vect)
{
	if(ledcntr==154){
		ledcntr=0;
	}else{
		ledcntr++;
	}

	if(ledcntr<ON_INTERVAL){
		LED1_ON();
	}else{
		LED1_OFF();
	}
}


void startSignal(void){
	TCCR0B|=(1<<CS02)|(1<<CS00);//clock source clkio/1024
	TCNT0=0;		  //start counting from 0
	TIMSK0|=(1<<TOIE0);//enable interrupt on overflow

	ledcntr=0;
}

void stopSignal(void){
	LED2_OFF();
	TCCR0B=0;	//disable timer
}
