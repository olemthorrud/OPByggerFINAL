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
#include "spi_driver.h"
#include "mcp_driver.h"
//#include "can.h" denne ligger nå i adc.h











int main(void)
{
	
	// Deklarering av globale verdier for behandling av skjermen og posisjoner på multifunction board

		volatile uint8_t js_pos[4];
		adc_driver(js_pos);
		volatile int arrow_pos = 0;
		int* arrow_pos_ptr = &arrow_pos;
	
	//Initialiseringer
		USART_Init(UBRR);
		uart_link_printf();
		SRAM_init();
		adc_config_clock();
		oled_init();	
		can_init();	
		set_normal_mode();
		
	
		while(1){
		//_delay_ms(200);
 			 printf("[");
			 for (int i = 0; i < 4; i++){
 			 				 printf("%d", js_pos[i]);
 			 				 
 			 				 printf(" , ");
 			 			 }
 			  			 printf("] \r \n");	 
		send_js_pos(js_pos);
		}
	return 0;
}

