/*
 * GccApplication2.c
 *
 * Created: 05.09.2023 12:40:02
 * Author : pmherdle
 */ 




#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define UBRR F_CPU / 16 / BAUD - 1
#include <stdio.h>

#include "uart.h"
#include "sram.h"







int main(void)
{
	unsigned char receivedData;

	// Initialize UART
	USART_Init(UBRR);

	// Redirect printf and scanf to UART
	uart_link_printf();

	// Send a welcome message
	printf("UART Test Program!\n");
	printf("Type any character and it will be echoed back.\n");
	DDRB = 0x0; //set PORTB to input (all 0's) 
	DDRA = 0xFF; //set PORTA to output (all 1's)


	PORTB |= (1 << PB0);

	while (1)
	{
		//Wait for a character from UART
		receivedData = USART_Receive();
		if(receivedData == 'a'){
			PORTA |= (1 << PA3);
		}
		else if (receivedData == 'c'){
			PORTA |= (1 << PA4);
		}
		else if (receivedData == 'b'){
			PORTA &= (0 << PA3);
		}
		else if (receivedData == 'd'){
			PORTA &= (0 << PA4);
		}


		
		// Echo the received character back to the terminal
		printf("%c", receivedData);

	}	

	return 0; // This line will never be reached in an embedded program
}



