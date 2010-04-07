#ifndef _IA_SPI_H_
#define _IA_SPI_H_

/*
 *  SPI interface to internal accelerometer
 */

#include "avr/io.h"

#define IA_MISO_DIR			DDRD
#define IA_MISO_PIN			PIND
#define IA_MISO_PORT		PORTD
#define IA_MISO_BIT			2

#define IA_MOSI_DIR			DDRD
#define IA_MOSI_PIN			PIND
#define IA_MOSI_PORT		PORTD
#define IA_MOSI_BIT			3

#define IA_SCK_DIR			DDRD
#define IA_SCK_PIN			PIND
#define IA_SCK_PORT			PORTD
#define IA_SCK_BIT			4

void ia_spi_init(void);
char ia_spi_byte(char data);

#endif
