#include "avr/io.h"

#ifndef _TII_H_
#define _TII_H_
//
//change below
//

//! defines the number of channels (channel 0 not included)
#define NR_OF_CHANNELS		1
//! defines the id of the supplier (16 bit length)
#define SUPPLIER_ID			0x4040
//! defines the function of the STIM - specified by the supplier (16 bit length)
#define FUNCTIONAL_ID		0x3030
//! defines the variant of the STIM (8 bit length)
#define VARIANT_ID			0x32
//! defines the serial number of the device (32 bit length)
#define SERIAL_NR			0x37373737

//!defines maximal buffer length for input and output buffer
#define MAX_BUFF_LTH		40

#define DIR_SS		DDRB
#define	PORT_SS		PORTB
#define	PIN_SS		PINB
#define SS			4

#define DIR_SS_PIN		DDRB
#define	PORT_SS_PIN		PORTB
#define	PIN_SS_PIN		PINB
#define SS_PIN			4

#define DIR_MISO		DDRB
#define MISO			6

#define DIR_MOSI		DDRB
#define MOSI			5

#define DIR_SCK		DDRB
#define SCK			7

#define DIR_NINT	DDRA
#define PORT_NINT	PORTA
#define PIN_NINT	PINA
#define NINT		6


#define WAKEUP_EDGE_FALLING()		EICRA=(EICRA&(~(1<<ISC21)|(1<<ISC20)))|(1<<ISC21)
#define WAKEUP_EN()					EIMSK|=(1<<INT2)
#define WAKEUP_DIS()				EIMSK&=~(1<<INT2)			
#define WAKEUP_VECT					INT2_vect


#define PUSH_BYTE(X)			SPDR=X

//
//do not change below, unless necessary
//

//slave select pin of the controller
#define SS_OUT()	DIR_SS|=(1<<SS)
#define SS_IN()		DIR_SS&=~(1<<SS)

//pin used for slave-select
#define SS_PIN_OUT()	DIR_SS_PIN|=(1<<SS_PIN)
#define SS_PIN_IN()		DIR_SS_PIN&=~(1<<SS_PIN)
#define SS_PIN_HIGH()	PORT_SS_PIN=PIN_SS_PIN|(1<<SS_PIN)
#define SS_PIN_LOW()	PORT_SS_PIN=PIN_SS_PIN&(~(1<<SS_PIN))
#define NOT_SELECTED()	PIN_SS_PIN&(1<<SS_PIN)

//miso
#define MISO_OUT()		DIR_MISO|=(1<<MISO)
#define MISO_IN()		DIR_MISO&=~(1<<MISO)

//mosi
#define MOSI_OUT()		DIR_MOSI|=(1<<MOSI)
#define MOSI_IN()		DIR_MOSI&=~(1<<MOSI)

//sck
#define SCK_OUT()		DIR_SCK|=(1<<SCK)
#define SCK_IN()		DIR_SCK&=~(1<<SCK)


//nint
#define NINT_OUT()		DIR_NINT|=(1<<NINT)
#define NINT_LOW()		PORT_NINT&=~(1<<NINT)
#define NINT_HIGH()		PORT_NINT|=(1<<NINT)
#define NINT_STATE()	((PIN_NINT&(1<<NINT))==0)

#define BSY_NOERR	0x00		//RDY=0 ERR=0
#define BSY_ERR		0x40		//RDY=0 ERR=1
#define RDY_NOERR	0x80		//RDY=1 ERR=0
#define RDY_ERR		0xC0		//RDY=1 ERR=1



/*!
\brief Stores the data of TII transmission

Stores the incoming and outgoing data of a TII transmission.

mezoket leirni
*/
struct TIIbuffer{
	char * messageptr;
	char * lth;
	unsigned char status;
};


/*!
\brief TII event callback structure

The structure contains the pointers to the callback functions associated with the TII events.
*/
struct TII_event_set_t{
	//! start single measurement event parameters: unsigned char - channel number
	void(* start_single)(unsigned char);	
	
	//! start continuous measurement event parameters: unsigned char - channel number
	void(* start_cont)(unsigned char);		
	
	//! stop measurement event on channel 0
	void(* stop_meas)(void);				
	
	//lehet get_id-t is így kellene- h eeprombot kulon lehessen konfiguralni
	
	//! read data parameters: unsigned char * - pointer to the output buffer (data should be copied here)
	//! maximal length: ... unsigned char - number of the channel
	void(* read_data)(struct TIIbuffer *, unsigned char);	
	
	//!special command event parameters:
	//!unsigned char * - pointer to the output buffer maximal length:...
	//!unsigned char * - pointer to the input buffer, length is in the first byte
	void(* special_command)(struct TIIbuffer *, struct TIIbuffer *);
};





/*!
\brief Describes the state of the of the TII transmission.

Describes the state of the of the TII transmission - for internal use only.
*/
typedef enum{
	IDLE,				//!> no byte received in this packet
	CHANNELREC,			//!> received channel byte
	TR_CHN,			//!> transmitting channel number
	TR_DATA,			//!> sending data
	RX_LTH,				//!> receiving length of special command
	RX_DATA,			//!> receiving special command
	PREPARING,			//!> preparing to power down
	INACTIVE			//!> interface inactive, WAKEUP is the only event out of this state
}tii_state_t;


/*!
\brief Describes a TII event

*/
typedef enum{
	SPIRX,				//!> SPI transmission complete IT
	NINT_LOW,			//!> STIM pulled the NINT low 
	WAKEUP_LOW			//!> NCAP pulled the WAKEUP low
}tii_event_t;


void TIIinit(struct TII_event_set_t * events);
void TIIstateM(char data);
void TIIexecuteC(unsigned char channel, unsigned char command);
unsigned char SPI(unsigned char data);
void TIIsigint(void);
void TIIendint(void);
void TIItxnext(void);
void TIItxchar(char c);


unsigned char TIIisInactive(void);
void test(unsigned char dat);
#endif //_TII_H_
