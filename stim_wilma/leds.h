#ifndef _PINOUT_H_
#define _PINOUT_H_

#define LED1_DDR	DDRA
#define LED1_PORT	PORTA
#define LED1_BIT	1

#define LED2_DDR	DDRA
#define LED2_PORT	PORTA
#define LED2_BIT	2

#define LED1_DIR()	LED1_DDR|=(1<<LED1_BIT)
#define LED1_ON()	LED1_PORT &= ~(1<<LED1_BIT)
#define LED1_OFF()	LED1_PORT |= (1<<LED1_BIT)

#define LED2_DIR()	LED2_DDR|=(1<<LED2_BIT)
#define LED2_ON()	LED2_PORT &= ~(1<<LED2_BIT)
#define LED2_OFF()	LED2_PORT |= (1<<LED2_BIT)

#endif
