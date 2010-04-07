#include "avr/io.h"
#include "util/delay.h"
#include "tii.h"
#include "avr/interrupt.h"
#include "stdio.h"
#include "avr/sleep.h"
#include "accmtr.h"
#include "ea_spi.h"
#include "atomic.h"
#include "leds.h"
#include "stdint.h"
#include "signal.h"


void startSingleMeas(unsigned char channel);
void startContMeas(unsigned char channel);
void stopMeas(void);
void readData(struct TIIbuffer * oBuffer, unsigned char channel);
void specialCommand(struct TIIbuffer * oBuffer, struct TIIbuffer * commandBuf);

static struct TII_event_set_t pointers;

#define BUFF_SIZE	30		// sample buffer size
uint16_t ridx, widx;
uint32_t rcnt, wcnt;
int16_t buff[BUFF_SIZE * 3]; // 8 sec buffer

char cnt;
char led1_cnt = 0;


// On-board accelerometer data ready interrupt service
ISR(PCINT3_vect)
{
	accmtr_read_acc_data(0, buff+widx*3);	// read data in buffer

	widx++;									// increment buffer index
	wcnt++;									// increment write counter
	if (widx >= BUFF_SIZE) widx = 0;		

	cnt++;
	if (cnt > 40) cnt = 0;
	if (cnt < 6) LED2_ON(); else LED2_OFF();


	if ((wcnt - rcnt) > 0) {		
		TIIsigint();						
	}
}



int main(void)
{	
	LED1_DIR();
	LED1_ON();
	LED2_DIR();
	LED2_OFF();

	ridx = widx = rcnt = wcnt = 0;

	accmtr_bus_init();
	accmtr_init(0);
	
	//initialize event container
	pointers.start_single=startSingleMeas;
	pointers.start_cont=startContMeas;
	pointers.stop_meas=stopMeas;
	pointers.read_data=readData;
	pointers.special_command=specialCommand;
	
	TIIinit(&pointers);

	accmtr_present(0);
	accmtr_present(0);


	sei();

	while(1){
		//ha nem mernek
			//es keszen vannak - IT-t kerek
			//es nincsenek keszen - alszok

		set_sleep_mode(SLEEP_MODE_IDLE);
      	sleep_mode();

	}
}


void startSingleMeas(unsigned char channel)
{
	//not implemented here
}
void startContMeas(unsigned char channel)
{
	LED1_OFF();
	stopSignal();
	accmtr_meas_start(0);
}

void stopMeas(void)
{
	LED2_OFF();
	LED1_OFF();
	accmtr_meas_stop(0);

	//reset buffer - by G.B. (nem vagyunk kivancsiak az elozo meres vegere)
	ridx=0;
	widx=0;
	rcnt=0;
	wcnt=0;

	startSignal();

	TIIendint();
}

void readData(struct TIIbuffer * oBuffer, unsigned char channel)
{
	uint16_t i;
	uint16_t idx=0;
	char *chbuff;


	//led1_cnt++;
	//if (led1_cnt > 71) led1_cnt = 0;
	//if (led1_cnt < 6) LED1_ON(); else LED1_OFF();

	chbuff = (char *)buff;

	if (rcnt == wcnt) {
		*(oBuffer->lth)=0;
		oBuffer->status=BSY_NOERR;
		TIIendint();
		return;
	}

	while ((rcnt < wcnt) && ((idx + 6) < MAX_BUFF_LTH-1)) {		//ide javitottam, -1 kell, mert a MAX_BUFF_LTH-ben a stat&len byte is benne van
		for (i=0; i<6; i++, idx++) {
			oBuffer->messageptr[idx] = chbuff[ridx*6 + i];
		}
		ridx++;									// increment buffer index
		rcnt++;									// increment write counter
		if (ridx >= BUFF_SIZE) ridx = 0;		// circular buffer

	}
	*(oBuffer->lth)=(char)((idx+1) & 0xff);
	oBuffer->status=RDY_NOERR;

	if ((wcnt - rcnt) < 1) {
		TIIendint();
	}

}

void specialCommand(struct TIIbuffer * oBuffer, struct TIIbuffer * commandBuf){

	//reply
	*(oBuffer->lth)=7;
	*(oBuffer->messageptr)='W';
	*(oBuffer->messageptr+1)='i';
	*(oBuffer->messageptr+2)='l';
	*(oBuffer->messageptr+3)='m';
	*(oBuffer->messageptr+4)='a';
	*(oBuffer->messageptr+5)='\r';
	*(oBuffer->messageptr+6)='\n';

	oBuffer->status=RDY_NOERR;
}
