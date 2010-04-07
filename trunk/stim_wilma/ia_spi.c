#include "ia_spi.h"

void ia_spi_init(void)
{
	UBRR1 = 0;

	// MISO: input, pull-up
	IA_MISO_DIR &= ~(1<<IA_MISO_BIT);
	IA_MISO_PORT |= (1<<IA_MISO_BIT);

	// MOSI: output, low
	IA_MOSI_DIR |= (1<<IA_MOSI_BIT);
	IA_MOSI_PORT &= ~(1<<IA_MOSI_BIT);

	// SCK: output, low
	IA_SCK_DIR |= (1<<IA_SCK_BIT);
	IA_SCK_PORT |= (1<<IA_SCK_BIT);

	UCSR1C = (1<<UMSEL11)|(1<<UMSEL10)|(1<<UCPHA1)|(1<<UCPOL1);
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	UBRR1 = 7;
}

char ia_spi_byte(char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );
	/* Put data into buffer, sends the data */
	UDR1 = data;
	/* Wait for data to be rec1ived */
	while ( !(UCSR1A & (1<<RXC1)) );
	/* Get and return received data from buffer */
	return UDR1;
}
