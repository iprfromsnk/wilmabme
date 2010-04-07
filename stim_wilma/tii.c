/*!
\file		tii.c
\brief		Contains the routines for the STIM TII interface.
\author		Gorog, Balazs
\version	1.0
\date		2009.oct.20.
\warning	Only tested with WinAVR. Tested on ATMega16, 4MHz. This version is working with UART.
*/



#include "tii.h"
#include "commands.h"
#include "avr/interrupt.h"

#include "leds.h"

#define GO_INACTIVE()		\
	tiistate=INACTIVE;		\
	WAKEUP_EN();			\
	active=0


#define GO_ACTIVE()			\
	tiistate=IDLE;			\
	WAKEUP_DIS();			\
	active=1

#define PREPARE_OUTPUT()						\
	output_buffer[0]&=0x3F; 					\
	output_buffer[0]|=(txbuffer.status&0xC0);	\
	txpointer=0



unsigned char active=0;

tii_state_t tiistate=IDLE;
volatile unsigned char channel=0;
volatile unsigned char command=0;
static struct TII_event_set_t * tiievents;


 char output_buffer[MAX_BUFF_LTH];
 struct TIIbuffer txbuffer;
volatile unsigned char txpointer=0;

 char input_buffer[MAX_BUFF_LTH];
 struct TIIbuffer rxbuffer;
volatile unsigned char rxpointer=0;



/*!
\brief SPI interrupt vector


*/
ISR(SPI_STC_vect){
	TIIstateM(SPDR);
}



/*
\brief Interrupt routine for the interrupt defined in tii.h (Wakeup pin).
\param N/A
\return N/A

The low level on the WAKEUP line generates an interrupt, this routine handles it. It resets the communication state-machine and
the buffers.
*/
ISR(WAKEUP_VECT){
//	LED2_ON();
	GO_ACTIVE();
}


/*!
\brief Initialize the TII interface of the STIM

\param events	This structure contains the function pointers of user defined the event handler callback functions.
\return N/A

Configures SPI to the following settings: interrupt enable, SPI enable, LSB first, SPI slave, SCK high when idle,
sample on leading edge, 125 kbaud on 4 MHz (Fclk/32).
Sets port directions: pins defined in the header file as SS, SCK, MOSI are configured as inputs, MISO as output.
Stores the callback function pointers, enables the interrupt on the WAKEUP line, sets the communication statemachine
into inactive state.


*/
void TIIinit(struct TII_event_set_t * events){
	//direction settings
	SS_IN();
	MISO_OUT();
	SCK_IN();
	MOSI_IN();

	NINT_OUT();
	NINT_HIGH();

	//SPI config: interrupt enable, SPI enable, LSB first
	//slave, SCK high when idle, sample on leading edge
	//125 kbaud on 4 MHz - Fclk/32
	SPCR=(1<<SPIE)|(1<<SPE)|(1<<DORD)|(1<<CPOL)|(1<<SPR1);
	//SPSR=(1<<SPI2X);

	tiievents=events;

	WAKEUP_EDGE_FALLING();
	
	GO_INACTIVE();	

	return;
}



/*!
\brief 		Manages the state-machine of the communication.
\param data	The incoming byte from the SPI.
\return		N/A

Handles the state-machine of the communication. Prepares the reply message if needed and sends it.

kene egy allapotgep abra es az ala a magyarazat

*/
void TIIstateM(char data){
	switch(tiistate){
	case INACTIVE:	//character read in this state is thrown away, WAKEUP should precede it
		//do nothing, if there was no wakeup
		break;
	case IDLE:
		if(data<=NR_OF_CHANNELS){
			//if channel byte valid, next state
			channel=data;
			tiistate=CHANNELREC;
		}else{
			//if channel byte not valid, go inactive
			GO_INACTIVE();
		}
		break;
	case CHANNELREC:
		command=data;

		//initialize buffers
		txbuffer.lth=&output_buffer[0];
		txbuffer.messageptr=&output_buffer[1];
		txbuffer.status=BSY_NOERR;

		rxbuffer.lth=&input_buffer[0];
		rxbuffer.messageptr=&input_buffer[1];
		rxbuffer.status=BSY_NOERR;

		//if command received, execute command		
		TIIexecuteC(channel, command);
		break;

	//nr of channels transmitted
	case TR_CHN:
		//if channel nr transmitted, go idle
		GO_INACTIVE();
		break;
	
	//transmit data
	case TR_DATA:
		//transmit next character
		TIItxnext();
		break;

	//receive data
	case RX_LTH:			//receive length of special command
		input_buffer[0]=data;	//store
		rxpointer=1;			//set pointer to next character
		if(data!=0){
			tiistate=RX_DATA;	//if length is not zero, receive other characters
		}else{
			tiievents->special_command(&txbuffer,&rxbuffer);	//if length is zero, indicate special command
			PREPARE_OUTPUT();									//prepare flag, reset pointer transmit

			TIItxnext();	//transmit next character of prepared output
		}
		break;
	case RX_DATA:
		//receiving special command
		input_buffer[rxpointer]=data;			//store byte of special command

		if(rxpointer<input_buffer[0]){				//if there is any byte left, receive others
			rxpointer++;	//increment pointer
		}else{
			tiievents->special_command(&txbuffer,&rxbuffer);		//all bytes received, indicate special command
			PREPARE_OUTPUT();										//prepare flag, reset pointer transmit

			TIItxnext();		//transmit prepared output
		}
		break;
	default:
		GO_INACTIVE();	//if invalid byte received, go inactive
		break;
	}
}


/*!
\brief Executes the command by calling the appropriate callback function.
\param channel		This byte selects the channel the command is sent to.
\param command		This byte selects the command (selects the callback function).
\return N/A

The function selects the appropriate callback function defined by the command byte (if it is the SPEC_COMM byte, it just changes the
state of the state-machine), or just composes a message to the output buffer (GET_DEV_ID).
*/
void TIIexecuteC(unsigned char channel, unsigned char command){

	switch(command){
			case START_SMEAS:
				//indicate single measurement command to upper layer
				tiievents->start_single(channel);
				//go inactive after indication - no reply has to be transmitted
				GO_INACTIVE();
				break;
			case START_CMEAS:
				//start continuous measurement command indication
				tiievents->start_cont(channel);
				//go inactive - no reply has to be transmitted
				GO_INACTIVE();
				break;
			case STOP_MEAS:
				//pull down NINT line, to ask for time
				TIIsigint();
				//next state is preparing - that state ends with the releasing of the NINT line
				tiistate=PREPARING;
				//indicate stop measurement command
				tiievents->stop_meas();
				break;
			case GET_NR_CHAN:
				
				//transmit channel number
				TIItxchar(NR_OF_CHANNELS);
				//next state is TR_CHN, ends with an SPI transaction
				tiistate=TR_CHN;
				break;
			case GET_DEV_ID:
				//fill up the output buffer with the identification data
				//length
				output_buffer[0]=9;
				//parameters
				output_buffer[1]=(SUPPLIER_ID&0xFF00)>>8;
				output_buffer[2]=SUPPLIER_ID&0x00FF;
				output_buffer[3]=(FUNCTIONAL_ID&0xFF00)>>8;
				output_buffer[4]=FUNCTIONAL_ID&0x00FF;
				output_buffer[5]=VARIANT_ID;
				output_buffer[6]=(SERIAL_NR&0XFF000000)>>24;
				output_buffer[7]=(SERIAL_NR&0X00FF0000)>>16;
				output_buffer[8]=(SERIAL_NR&0X0000FF00)>>8;
				output_buffer[9]= SERIAL_NR&0X000000FF;
				TIItxnext();
				break;
			case READ_DATA:
				//indicate read data command
				tiievents->read_data(&txbuffer,channel);
				//prepare the output buffer
				PREPARE_OUTPUT();
				//transmit next character of prepared output
				TIItxnext();	//ez adja a köv allapotot
				break;
			case SPEC_COMM:
				//next state is RX_LTH - a series of characters is going to be read in this state
				tiistate=RX_LTH;
				break;
			default:
				//if invalid command - go inactive
				GO_INACTIVE();
				break;
		}
}

/*!
\brief Transmits the next character of the message.
\param N/A - the character is selected from the output buffer.
\return N/A

Transmits next character. If there are any untransmitted characters left, the communication status will be TR_DATA,
else the status changes to INACTIVE.
*/
void TIItxnext(void){
	//transmit next character of the output buffer
	TIItxchar(output_buffer[txpointer]);

	//if all the characters transmitted - go inacitve
	if((output_buffer[0]&0x7F)<txpointer){
		//end transmission
		txpointer=0;
		//go inactive
		GO_INACTIVE();
	//if there are other characters left - next state will be TR_DATA state - where the output is sent
	}else{
		//stay in transmitting state
		txpointer++;
		tiistate=TR_DATA;
	}
}

/*!
\brief		Puts the character in the input to the transmit register.
\param c	The character to be transmitted.
\return		N/A
*/

void TIItxchar(char c){
	
	//move the character to the SPI data register
	PUSH_BYTE(c);
}


/*!
\brief Signals on the NINT line.
\param N/A
\return N/A

Requests interrupt from the NCAP by pulling the NINT line low. If it is the reply for a STOP_MEAS command, it means, 
that the controller needs time to prepare for the shut-down.
*/
void TIIsigint(void){
	//pull low the NINT line
	NINT_LOW();
}


/*!
\brief Pulls high the NINT line.
\param N/A
\return N/A

Signals the NCAP the there will be nothing to read after the actual transaction. If the state-machine is in PREPARING
state, it means, that the controller is ready to be shut down.
*/
void TIIendint(void){

	//pull high the nint line
	NINT_HIGH();

	
	if(tiistate==PREPARING){	//ha ebben az allapotban van, akkor az inaktivba kell mennie utana
		GO_INACTIVE();
	}


}

/*!
\brief Tells the application if any communication is in process.
\param N/A
\return 1, if the communication is in INACTIVE state and 0, if the communication is active.

The application needs to know, if any communication is in progress. If there is no communication in progress, the application
can go to sleep, otherwise it shouldn't.
*/
unsigned char TIIisInactive(void){
	
	//tells the application if the uC can be powered down
	if(tiistate==INACTIVE){
		//tii is inactive - the uC can be powered down
		return 1;
	}else{
		return 0;
	}
}


unsigned char SPI(unsigned char data) {
	unsigned char received = 0;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));//poll flag
	received = SPDR;
	return received;
}
