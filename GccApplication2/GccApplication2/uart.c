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

void SRAM_test(void)
{
		
		volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
		uint16_t ext_ram_size = 0x800;
		uint16_t write_errors = 0;
		uint16_t retrieval_errors = 0;
		printf("Starting SRAM test...\n");
		// rand() stores some internal state, so calling this function in a loop will
		// yield different seeds each time (unless srand() is called before this function)
		uint16_t seed = rand();
		// Write phase: Immediately check that the correct value was stored
		srand(seed);
	

		
		
		for (uint16_t i = 0; i < ext_ram_size; i++) {
			DDRA = 0xFF; //set PORTA to output (all 1's)
			PORTB &= (0 << PB0); // Enabler input på sram
			uint8_t some_value = rand();
			ext_ram[i] = some_value;
			int* memory_address = &ext_ram[0] + i * sizeof(ext_ram[0]);  

		
			uint8_t retreived_value = ext_ram[i];
			if (retreived_value != some_value) {
				printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
				printf("The memory address is %p/" , (void*)memory_address); 
				write_errors++;
			}
		}
		// Retrieval phase: Check that no values were changed during or after the write phase
		srand(seed);
		// reset the PRNG to the state it had before the write phase
		for (uint16_t i = 0; i < ext_ram_size; i++) {
			uint8_t some_value = rand();
			uint8_t retreived_value = ext_ram[i];
			if (retreived_value != some_value) {
				printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
				retrieval_errors++;
			}
		}
		printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

void SRAM_test2(void){
	
		
		DDRA = 0xFF; //set PORTA to output (all 1's)
		PORTB &= (0 << PB0); // Enabler input på sram
	
		volatile char *ext_ram = (char *) 0x1800; 
		uint8_t some_value = 503;
		uint8_t some_value2 = 500;
		uint8_t some_value3 = 400;
			
		ext_ram[0] = some_value;
		ext_ram[16] = some_value2;
		ext_ram[34] = some_value3;
		
			
		DDRA = 0x0; //set PORTA to input (all 0's)
		PORTB |= (1 << PB0);
		
		uint8_t retreived_value = ext_ram[1];
		uint8_t retreived_value1 = ext_ram[16];
		uint8_t retreived_value2 = ext_ram[34];

		printf("Retrieved Value = %02X, Some Value = %02X . ", retreived_value, some_value);
		printf("Retrieved Value = %02X, Some Value = %02X . ", retreived_value1, some_value2);
		printf("Retrieved Value = %02X, Some Value = %02X . ", retreived_value2, some_value3);

		PORTB &= (0 << PB0); 

}

void ram_test(void){
	volatile char *ext_ram = (char *) 0x1800;
	
	uint8_t some_value = 505;
	
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

void SRAM_init(void){
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
}

