#include "bspTII.h"

//spi include-ok
#include <halSpi.h>
#include <spi.h>

//task manager
#include <bspTaskManager.h>

//true-false success fail tipusok
#include <types.h>

//gpio eleres
#include <gpio.h>

//kulso megszakitaskeres
#include <irq.h>

//delay
#include "util/delay.h"

//own commands defined in:
#include "commands.h"


#define WAKEUP_DELAY_MS 5

//mitmot kartyahoz
//#define IRQ_NUMBER IRQ_6
//wilma
#define IRQ_NUMBER IRQ_7

///////////////////////////////////////////////
//mitmot kartyahoz
//#define WAKEUP_OUT() GPIO_I2C_DATA_make_out()
//#define WAKEUP_LOW() GPIO_I2C_DATA_clr()
//#define WAKEUP_HIGH() GPIO_I2C_DATA_set()

//wilma
#define WAKEUP_OUT() GPIO_8_make_out()
#define WAKEUP_LOW() GPIO_8_clr()
#define WAKEUP_HIGH() GPIO_8_set()

//mitmot kartyahoz
/*#define SS_OUT() GPIO_I2C_CLK_make_out()
#define SS_LOW() GPIO_I2C_CLK_clr()
#define SS_HIGH() GPIO_I2C_CLK_set()*/
//wilma
#define SS_OUT() GPIO_1WR_make_out()
#define SS_LOW() GPIO_1WR_clr()
#define SS_HIGH() GPIO_1WR_set()


typedef enum{
	INACTIVE,
	IDLE,
	WAKEUP_LOW,
	CH_D_SENDING,
	CH_D_SENT,
//	WAITING,
	GETTING_CHNR,
	GOT_CHNR,
	GETTING_LTH,
	GETTING_LONG_ANSWER,
	GOT_ANSWER
}tiiState_t;

typedef enum{
	NINT_INDICATION,		//stim indicates data is ready
	APP_REQUEST				//application service request
}operationType_t;

static struct STIM_descriptor_t{
	uint8_t channelnr;
	uint8_t id[9];
}ch1_desc;
//descriptor for stim


//descriptor for spi init
static HAL_SpiDescriptor_t stim;

//state variable for state-machine
static tiiState_t state=INACTIVE;

//buffer for spi transaction
static uint8_t TIIbuffer[TII_BUFF_LTH];

//data for operation in progress
static uint8_t ChannelNr=0;
static uint8_t CommandNr=0;

//stopping request flag
static uint8_t stopReq=0;

//which operation is in progress application request, or STIM indication (data ready)
static operationType_t operationInProgress=APP_REQUEST;

//temporary buffer to store measurement result
static uint8_t measurementData[TII_BUFF_LTH];


//indication for STIM channel nr reading
void (* TII_CHNRCallback)(uint8_t chnr);

//functionpointer to indicate if data was read from TII
void (*DataReadyCb)(uint8_t * data);

//functionpointer for STIM ID reading
void (* TII_IDCallback)(uint8_t * chnr);

//functionpointer to indicate that measure command is sent
void (* TII_SMCallback)(void);

//functionpointer to indicate that measure command is sent
void (* TII_CMCallback)(void);

//functionpointer to indicate that NCAP stopped
void (* TII_stCallback)(void);

//variable used for storing the lth of the data to be read
static uint16_t buffer_lth=0;



//internal callback function for NINT operation
void irqCallback(void)
{
	//if there is no operation in progress
	if(state==IDLE){
		HAL_DisableIrq(IRQ_NUMBER);

		//pull down wakeup line
		WAKEUP_low();

		//wakeup low state, indicates that wakeup line is pulled low
		state=WAKEUP_LOW;

		//store parameters for current transaction
		operationInProgress=NINT_INDICATION;	//this is an indication from the stim
		ChannelNr=0;							//channel nr=0
		CommandNr=READ_DATA;					//command is read data

		//schedule next run
		bspPostTask0(BSP_TII);		
	}else{
		//lehet nem szukseges, de azert ne zavarjon be az interrupt
		HAL_DisableIrq (IRQ_NUMBER);
	}
}

//internal callback function for spi operations
void spiCallback(void)
{
	unsigned char i;
	SS_HIGH();

	switch(state){
	case IDLE:
		// do nothing, the spi interface is opened
		break;
	case CH_D_SENDING:
		state=CH_D_SENT;	//channel and command is sent, return to task handler to call indication or wait
		//schedule task handler
		bspPostTask0(BSP_TII);
		break;
	case GETTING_CHNR:
		//store number of channels
		ch1_desc.channelnr=TIIbuffer[0];
		//next state is GOT_CHNR, handled int the task handler - indication routine should be called from there
		state=GOT_CHNR;
		bspPostTask0(BSP_TII); 
		break;
	case GETTING_LTH:
		//read lth - first byte of message
		buffer_lth=TIIbuffer[0];
		
		SS_LOW();
		switch(CommandNr){
	    case GET_DEV_ID:
			//read nr of bytes defined in lth
			HAL_ReadSpi(&stim,&TIIbuffer[0],buffer_lth);
			break;
		case READ_DATA:
			//read nr of bytes (error and status masked out)
			HAL_ReadSpi(&stim,&TIIbuffer[0],buffer_lth&0x3F);
			break;
		default:
			break;
		}
		
		//next state is GETTING_LONG_ANSWER - handled in spiCallback
		state=GETTING_LONG_ANSWER;
		break;
	case GETTING_LONG_ANSWER:
		switch(CommandNr){
		case GET_DEV_ID:
			//copy data to descriptor
			for(i=0;i<buffer_lth;i++){
				ch1_desc.id[i]=TIIbuffer[i];
			}
			break;
		case READ_DATA:
			//first byte of buffer is the lth&status
			measurementData[0]=buffer_lth;

			//copy the data into the buffer
			for(i=1;i<=(buffer_lth&0x3F);i++){
				measurementData[i]=TIIbuffer[i-1];
			}
			break;
		default:
			break;
		}
		state=GOT_ANSWER;
		bspPostTask0(BSP_TII);
		break;
	default:
		break;
	}
}

//should only be called after a successfull TIIgetCHNR transaction
//\param chnr specifies the channel from which the NCAP has to read
//if chNr is higher than the number of channels of the STIM, the function exits
void TIIstop(unsigned char chNr, void (* tiiCallback)(void)){
	//store callback pointer
	TII_stCallback=tiiCallback;

	if(state==IDLE){
		if(chNr>ch1_desc.channelnr){
			return;
		}
		//pull down wakeup line
		WAKEUP_low();

		//wakeup low state, indicates that wakeup line is pulled low
		state=WAKEUP_LOW;

		//store parameters for current transaction
		operationInProgress=APP_REQUEST;	//this is an application request
//***********************
//WILMA version chnr=0
//***********************
		ChannelNr=0;					//channel nr=0
		CommandNr=STOP_MEAS;			//command is STOP_MEAS

		//schedule next run
		bspPostTask0(BSP_TII);
	}else{
		//set flag if busy
		stopReq=1;
	}
}


//should only be called after a successfull TIIgetCHNR transaction
//\param chnr specifies the channel from which the NCAP has to read
//if chNr is higher than the number of channels of the STIM, the function exits
void TIIstartCont(unsigned char chNr, void (* tiiCallback)(void)){
	if(state==IDLE){
		if(chNr>ch1_desc.channelnr){
			return;
		}

		//store callback pointer
		TII_CMCallback=tiiCallback;

		//pull down wakeup line
		WAKEUP_low();

		//wakeup low state, indicates that wakeup line is pulled low
		state=WAKEUP_LOW;

		//store parameters for current transaction
		operationInProgress=APP_REQUEST;	//this is an application request
		ChannelNr=chNr;					//channel nr=0
		CommandNr=START_CMEAS;			//command is GET_NR_CHAN

		//schedule next run
		bspPostTask0(BSP_TII);
	}
}


//should only be called after a successfull TIIgetCHNR transaction
//\param chnr specifies the channel from which the NCAP has to read
//if chNr is higher than the number of channels of the STIM, the function exits
void TIImeasure(unsigned char chNr, void (* tiiCallback)(void)){
	if(state==IDLE){
		if(chNr>ch1_desc.channelnr){
			return;
		}

		//store callback pointer
		TII_SMCallback=tiiCallback;

		//pull down wakeup line
		WAKEUP_low();

		//wakeup low state, indicates that wakeup line is pulled low
		state=WAKEUP_LOW;

		//store parameters for current transaction
		operationInProgress=APP_REQUEST;	//this is an application request
		ChannelNr=chNr;					//channel nr=0
		CommandNr=START_SMEAS;			//command is GET_NR_CHAN

		//schedule next run
		bspPostTask0(BSP_TII);
	}
}


//\param void (* tiiCallback)(uint8_t chnr) function pointer to indicate if chnr is ready
void TIIgetCHNR(void (* tiiCallback)(uint8_t chnr)){
	//if there is nothing in progress
	if(state==IDLE){
		//register application level callback
		TII_CHNRCallback=tiiCallback;

		//pull down wakeup line
		WAKEUP_low();

		//wakeup low state, indicates that wakeup line is pulled low
		state=WAKEUP_LOW;

		//store parameters for current transaction
		operationInProgress=APP_REQUEST;	//this is an application request
		ChannelNr=0;					//channel nr=0
		CommandNr=GET_NR_CHAN;			//command is GET_NR_CHAN

		//schedule next run
		bspPostTask0(BSP_TII);
	}
}

//\param void (* tiiCallback)(uint8_t * chnr) function pointer to indicate if ID is ready
void TIIgetID(void (* tiiCallback)(uint8_t * chnr)){
	//if there is nothing in progress
	if(state==IDLE){
		//register application level callback
		TII_IDCallback=tiiCallback;

		//pull down wakeup line
		WAKEUP_low();

		//wakeup low state, indicates that wakeup line is pulled low
		state=WAKEUP_LOW;

		//store parameters for current transaction
		operationInProgress=APP_REQUEST;	//this is an application request
		ChannelNr=0;					//channel nr=0
		CommandNr=GET_DEV_ID;			//command is GET_ID

		//schedule next run
		bspPostTask0(BSP_TII);
	}
}


//\param void (*dataReadyCallback)(uint8_t * data) function pointer to indicate if data was read from TII
result_t openTII(void (*dataReadyCallback)(uint8_t * data))
{
	if(state==INACTIVE){
		ch1_desc.channelnr=0;

//initiate SPI interface
		stim.tty=USART_CHANNEL_0;
		//SPI config: LSB first
		//master, SCK high when idle, sample on leading edge
		stim.clockMode=SPI_CLOCK_MODE2;
		stim.dataOrder=SPI_DATA_LSB_FIRST;
		stim.baudRate=SPI_CLOCK_RATE_125;

		stim.callback=spiCallback;	//register internal callback function

		//store function pointer for data indication
		DataReadyCb=dataReadyCallback;

		//wakeup direction out
		WAKEUP_OUT();
		WAKEUP_HIGH();

		//slave select direction out
		SS_OUT();
		SS_HIGH();

		//register interrupt routine
		HAL_RegisterIrq (IRQ_NUMBER, IRQ_LOW_LEVEL, irqCallback);
		//enable interrupt
	    HAL_EnableIrq (IRQ_NUMBER);

		if(HAL_OpenSpi(&stim)==0){
			state=IDLE;
			return BC_SUCCESS;
		}else{
			return BC_FAIL;
		}
		return BC_SUCCESS;
	}else{
		return BC_FAIL;
	}
}

void WAKEUP_low(void){
	WAKEUP_LOW();
}

void WAKEUP_high(void){
	WAKEUP_HIGH();
}

//indications are going to be called from here
//other parts will be handled in separate functions
void bspTIIhandler(void)
{
	switch(state){
	case WAKEUP_LOW:
		_delay_ms(WAKEUP_DELAY_MS);
		WAKEUP_high();//wakeup line can be pulled high

		if(operationInProgress==APP_REQUEST){
			//if there is an application request in progress, serve it with the data requested by application
			TIIbuffer[0]=ChannelNr;
			TIIbuffer[1]=CommandNr;
		}else{
			//if it is a STIM indication, read all the values from channel 0
			ChannelNr=0;
			CommandNr=READ_DATA;
			TIIbuffer[0]=0;
			TIIbuffer[1]=READ_DATA;
		}
		
		state=CH_D_SENDING;		//next state indicates, that channel and data sending is in progress

		//send command and channel on spi
		SS_LOW();
		HAL_WriteSpi(&stim,&TIIbuffer[0],(uint16_t)2);
		//spiCallback will be called after data is sent

		break;
	case CH_D_SENT:
		switch(CommandNr){
		case START_SMEAS:
			//next request can be sent
			goIdle();
			//call callback routine
			TII_SMCallback();
			break;
		case START_CMEAS:
			//next request can be sent
			goIdle();
			//call callback routine
			TII_CMCallback();
			break;
		case STOP_MEAS:
			//next request can be sent
			HAL_DisableIrq(IRQ_NUMBER);
			_delay_ms(1);
			goIdle();
//**************
//WILMA VERSION - NOT WAITING FOR NINT
//**************
			//call the callback routine
			TII_stCallback();
			break;
		case GET_NR_CHAN:
			//wait - impossible with app timer
			_delay_ms(1);

			//read 1 character from the spi
			TIIbuffer[0]=0;
			SS_LOW();

			HAL_ReadSpi(&stim,&TIIbuffer[0],(uint16_t)1);

			//next state - GETTING_CHNR
			state=GETTING_CHNR;
			//spiCallback will be called when ready
			break;
		case GET_DEV_ID:
			//wait - impossible with app timer
			_delay_ms(1);

			//read lth on the spi
			TIIbuffer[0]=0;
			SS_LOW();

			HAL_ReadSpi(&stim,&TIIbuffer[0],(uint16_t)1);

			//next state - GETTING_LTH 
			state=GETTING_LTH;
			//spiCallback will be called when ready
			break;
		case READ_DATA:
			//wait - impossible with app timer
			_delay_ms(1);

			//read lth from on the spi
			TIIbuffer[0]=0;
			SS_LOW();

			HAL_ReadSpi(&stim,&TIIbuffer[0],(uint16_t)1);

			//next state - GETTING_LTH
			state=GETTING_LTH;
			//spiCallback will be called when ready
			break;
		case SPEC_COMM:
			//? is not handled yet
			break;
		default:
			break;
		}
		break;
	case GOT_CHNR:
		//finished reading number of channels
		state=IDLE;
		//call callback
		TII_CHNRCallback(ch1_desc.channelnr);
		break;
	case GOT_ANSWER:
		switch(CommandNr){
		case GET_DEV_ID:
			goIdle();
			TII_IDCallback(&(ch1_desc.id[0]));
			break;
		case READ_DATA:
			goIdle();
			DataReadyCb(&measurementData[0]);
			break;
		default:
			break;
		}
		break;
	default:
		goIdle();
		break;
	}

	//if finished with current job
	if(state==IDLE){
		//if stopping flag is set
		if(stopReq!=0){
			//unset flag
			stopReq=0;

			//pull down wakeup line
			WAKEUP_low();

			//wakeup low state, indicates that wakeup line is pulled low
			state=WAKEUP_LOW;

			//store parameters for current transaction
			operationInProgress=APP_REQUEST;	//this is an application request
//***********************
//WILMA version chnr=0
//***********************
			ChannelNr=0;					//channel nr=0
			CommandNr=STOP_MEAS;			//command is STOP_MEAS

			//schedule next run
			bspPostTask0(BSP_TII);
		}
	}

}

//returns to idle state and enables external interrupt
inline void goIdle(void){
	state=IDLE;
	HAL_EnableIrq (IRQ_NUMBER);
}

