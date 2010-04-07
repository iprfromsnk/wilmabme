#include "avr/io.h"
#include "ea_spi.h"

void ea_spi_init(void)
{
}

char ea_spi_byte(char data)
{
	return 0;
}

void dbg_uart_init(void)
{
	DBG_RXD_DIR &= ~(1<<DBG_RXD_BIT);
	DBG_RXD_PORT |= (1<<DBG_RXD_BIT);
	
	DBG_TXD_DIR |= (1<<DBG_TXD_BIT);
	DBG_TXD_PORT &= ~(1<<DBG_TXD_BIT);
	
	/* Set baud rate */
	UBRR0H = 0;
	UBRR0L = 0x0c;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void dbg_uart_send(char *data, char len)
{
	while (len) {
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE0)) );
		/* Put data into buffer, sends the data */
		UDR0 = *data++;
		len--;
	}
	while ( !( UCSR0A & (1<<UDRE0)) );
}
