#ifndef _EA_SPI_H_
#define _EA_SPI_H_

/*
 *  SPI interface to external accelerometer
 *
 *  (and UART interface for debug purposes)
 */

#include "avr/io.h"

// SPI macros
#define EA_MISO_DIR			DDRD
#define EA_MISO_PIN			PIND
#define EA_MISO_PORT		PORTD
#define EA_MISO_BIT			0

#define EA_MOSI_DIR			DDRD
#define EA_MOSI_PIN			PIND
#define EA_MOSI_PORT		PORTD
#define EA_MOSI_BIT			1

#define EA_SCK_DIR			DDRB
#define EA_SCK_PIN			PINB
#define EA_SCK_PORT			PORTB
#define EA_SCK_BIT			0

// UART macros
#define DBG_RXD_DIR			DDRD
#define DBG_RXD_PIN			PIND
#define DBG_RXD_PORT		PORTD
#define DBG_RXD_BIT			0

#define DBG_TXD_DIR			DDRD
#define DBG_TXD_PIN			PIND
#define DBG_TXD_PORT		PORTD
#define DBG_TXD_BIT			1

void ea_spi_init(void);
char ea_spi_byte(char data);

void dbg_uart_init(void);
void dbg_uart_send(char *data, char len);

#endif
