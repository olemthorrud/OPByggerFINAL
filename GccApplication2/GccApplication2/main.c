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
#include "adc.h"
#include "oled.h"


int main(void)
{
	// Initialize UART
	USART_Init(UBRR);
	uart_link_printf();

	//Initialize SRAM
	SRAM_init(); 
	
	//Initialize ADC clock
	adc_config_clock();
 	 
	  
	  
	  
// 	int ADC_driver_data[4]; 
// 	multifunction_board_test(ADC_driver_data); 
	
	oled_init();
	oled_fill(); 
	
	return 0; 
}



