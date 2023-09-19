/*
 * CFile1.c
 *
 * Created: 05.09.2023 13:29:33
 *  Author: pmherdle
 */ 

#include "uart.h"



void USART_Init( unsigned int ubrr )
{
	/* Setting baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable the reciever and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}
//
//
//
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffeggggg*/
	while ( !( UCSR0A & (1<<UDRE0)))
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0))); 
	/* Get and return received data from buffer */
	return UDR0;
}


void uart_link_printf() {
	fdevopen(&USART_Transmit, &USART_Receive);
}














void ram_test(void){
	volatile char *ext_ram = (char *) 0x1800;
	
	uint8_t some_value = 5;
	
	while (1){
		ext_ram[1] = some_value;	
	}  
	
}
void oled_test(void){
	volatile char *ext_oled = (char *) 0x1000;
	
	uint8_t some_value = 505;
	
	while (1){
		ext_oled[1] = some_value;
	}
	
}

void adc_test(void){
	volatile char *ext_adc = (char *) 0x1400;
	
	uint8_t some_value = 505;
	
	while (1){
		ext_adc[1] = some_value;
	}
	
}








