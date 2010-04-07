#include "swTII.h"

//task manager
#include <bspTaskManager.h>

//true-false success fail tipusok
#include <types.h>

//gpio eleres
#include <gpio.h>

//kulso megszakitaskeres
#include <irq.h>

// Application timer header
#include <appTimer.h>        


///////////////////////////////////////////////
//TEDS
///////////////////////////////////////////////			
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


///////////////////////////////////////////////
//minta sw tii irq
//#define IRQ_NUMBER IRQ_6

///////////////////////////////////////////////
//minta sw tii gpio makrok
///////////////////////////////////////////////
#define GOMB1_IN() GPIO_IRQ_6_make_in()
#define GOMB1_STATE() (GPIO_IRQ_6_read()==0)
//#define LED1_OUT()
//#define LED1_ON()
//#define LED1_OFF()
//#define LED1_TOGGLE()

//#define WAKEUP_OUT() GPIO_I2C_DATA_make_out()
//#define WAKEUP_LOW() GPIO_I2C_DATA_clr()
//#define WAKEUP_HIGH() GPIO_I2C_DATA_set()
/*#define SS_OUT() GPIO_I2C_CLK_make_out()
#define SS_LOW() GPIO_I2C_CLK_clr()
#define SS_HIGH() GPIO_I2C_CLK_set()*/



typedef enum{
	INACTIVE,		//tii inactive - until opentii
	IDLE,			//tii idle - no operation in progress
	GET_ID,			//tii id callback needed
	GET_CHNR,		//tii chnr callback needed
	SEND_RESULT		//tii data ready callback needed
}tiiState_t;

typedef enum{
	NINT_INDICATION,		//stim indicates that data is ready
	APP_REQUEST				//application service request
}operationType_t;

static struct STIM_descriptor_t{
	uint8_t channelnr;
	uint8_t id[9];
}ch1_desc;
//descriptor for stim


//state variable for state-machine
static tiiState_t state=INACTIVE;

//data for operation in progress
static uint8_t ChannelNr=0;
static uint8_t CommandNr=0;

//which operation is in progress application request, or STIM indication (data ready)
static operationType_t operationInProgress=APP_REQUEST;

//temporary buffer to store measurement result
static uint8_t measurementData[TII_BUFF_LTH];

//descriptor for timer
static HAL_AppTimer_t buttontimer;

static uint8_t data=0;

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


//internal callback function for NINT operation
//void irqCallback(void)
//{
//	//if there is no operation in progress
//	if(state==IDLE){
//		HAL_DisableIrq(IRQ_NUMBER);
//
//		//pull down wakeup line
//		WAKEUP_low();
//
//		//wakeup low state, indicates that wakeup line is pulled low
//		state=WAKEUP_LOW;
//
//		//store parameters for current transaction
//		operationInProgress=NINT_INDICATION;	//this is an indication from the stim
//		ChannelNr=0;							//channel nr=0
//		CommandNr=READ_DATA;					//command is read data
//
//		//schedule next run
//		bspPostTask0(SW_TII);		
//	}else{
//		//lehet nem szukseges, de azert ne zavarjon be az interrupt
//		HAL_DisableIrq (IRQ_NUMBER);
//	}
//}

void buttonTimerFired(void)
{
	if(state==IDLE){
		data=GOMB1_STATE();
		
		state=SEND_RESULT;
		bspPostTask0(SW_TII);
	}
}

//should only be called after a successfull TIIgetCHNR transaction
//\param chnr specifies the channel from which the NCAP has to read
//if chNr is higher than the number of channels of the STIM, the function exits
void swTIIstop(unsigned char chNr, void (* tiiCallback)(void)){
	//store callback pointer
	TII_stCallback=tiiCallback;
	HAL_StopAppTimer(&buttontimer);


}


//should only be called after a successfull TIIgetCHNR transaction
//\param chnr specifies the channel from which the NCAP has to read
//if chNr is higher than the number of channels of the STIM, the function exits
void swTIIstartCont(unsigned char chNr, void (* tiiCallback)(void)){
	if(state==IDLE){
		if(chNr>ch1_desc.channelnr){
			return;
		}

		//store callback pointer
		TII_CMCallback=tiiCallback;

		//start measurement timer
		buttontimer.interval=1000;
		buttontimer.mode=TIMER_REPEAT_MODE;
		buttontimer.callback=buttonTimerFired;
		HAL_StartAppTimer(&buttontimer);

		//schedule next run
		bspPostTask0(SW_TII);
	}
}


//should only be called after a successfull TIIgetCHNR transaction
//\param chnr specifies the channel from which the NCAP has to read
//if chNr is higher than the number of channels of the STIM, the function exits
void swTIImeasure(unsigned char chNr, void (* tiiCallback)(void)){
	if(state==IDLE){
		if(chNr>ch1_desc.channelnr){
			return;
		}

		//store callback pointer
		TII_SMCallback=tiiCallback;

		//schedule next run
		bspPostTask0(SW_TII);
	}
}


//\param void (* tiiCallback)(uint8_t chnr) function pointer to indicate if chnr is ready
void swTIIgetCHNR(void (* tiiCallback)(uint8_t chnr)){
	//if there is nothing in progress
	if(state==IDLE){
		//register application level callback
		TII_CHNRCallback=tiiCallback;

		//next state
		state=GET_CHNR;

		//schedule next run
		bspPostTask0(SW_TII);
	}
}

//\param void (* tiiCallback)(uint8_t * chnr) function pointer to indicate if ID is ready
void swTIIgetID(void (* tiiCallback)(uint8_t * chnr)){
	//if there is nothing in progress
	if(state==IDLE){
		//register application level callback
		TII_IDCallback=tiiCallback;
		
		//set state
		state=GET_ID;
		//schedule next run
		bspPostTask0(SW_TII);
	}
}


//\param void (*dataReadyCallback)(uint8_t * data) function pointer to indicate if data was read from TII
result_t openSWTII(void (*dataReadyCallback)(uint8_t * data))
{
	if(state==INACTIVE){
		ch1_desc.channelnr=0;

		//store function pointer for data indication
		DataReadyCb=dataReadyCallback;

		//set direction for button pin
		GOMB1_IN();

		//initialize stim descriptor
		ch1_desc.channelnr=NR_OF_CHANNELS;
		ch1_desc.id[0]=(SUPPLIER_ID&0xFF00)>>8;
		ch1_desc.id[1]=SUPPLIER_ID&0x00FF;
		ch1_desc.id[2]=(FUNCTIONAL_ID&0xFF00)>>8;
		ch1_desc.id[3]=FUNCTIONAL_ID&0x00FF;
		ch1_desc.id[4]=VARIANT_ID;
		ch1_desc.id[5]=(SERIAL_NR&0XFF000000)>>24;
		ch1_desc.id[6]=(SERIAL_NR&0X00FF0000)>>16;
		ch1_desc.id[7]=(SERIAL_NR&0X0000FF00)>>8;
		ch1_desc.id[8]= SERIAL_NR&0X000000FF;

		//state machine to idle
		state=IDLE;

		//register interrupt routine
		//HAL_RegisterIrq (IRQ_NUMBER, IRQ_LOW_LEVEL, irqCallback);
		////enable interrupt
		// HAL_EnableIrq (IRQ_NUMBER);

		return BC_SUCCESS;
	}else{
		return BC_FAIL;
	}
}
//indications are going to be called from here
//other parts will be handled in separate functions
void swTIIhandler(void)
{
	switch(state){
		case IDLE:
			break;
		case GET_ID:
			state=IDLE;
			TII_IDCallback(&(ch1_desc.id[0]));
			break;
		case GET_CHNR:
			state=IDLE;
			TII_CHNRCallback(ch1_desc.channelnr);
			break;
		case SEND_RESULT:
			state=IDLE;
			measurementData[0]=1|RDY_NOERR;		//stat&len byte
			measurementData[1]=data;			//content

			DataReadyCb(&measurementData[0]);	//callback
			break;
		default:
			break;
	}
}

