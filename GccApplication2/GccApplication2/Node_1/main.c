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
		
	
	// UART
	
		USART_Init(UBRR);
		uart_link_printf();
		

	// Initialize SRAM
	
		SRAM_init();
	
	
	// Initialize ADC clock
	
		adc_config_clock();
			
			
	// oled
	
		oled_init();
		
		 //int ADC_driver_data[4];                              //Hvor verdiene i funksjonen under lagres
		 //multifunction_board_test(ADC_driver_data);           //Testfunskjon for å hente 4 verdier fra js og sliders. Kan nok slås sammen med den under
		 //oled_test_meny(arrow_pos_ptr,js_pos);              //Testfunskjon til menyen på oledskjermen
		
		
	// Initialisering av can. Initfunksjonen setter den i loopback
		
		can_init();
	
		// mcp_test();                                        // Test av Spi sender 81 til et register og leser det igjen
		char my_array[] = {'f',' ','t','e','k','l','e','d'};             //Arrayet som skal sendes i loopbackmode i can_test
		//can_test(2, 4, my_array);                           //Funksjon som sender innad i can-kontrolleren i loopback mode
		 

	
	
		set_normal_mode();
		
		button_IR_init(); //OLES KODE 
		
// 		can_message to_send;
// 		to_send.id = 2;
// 		to_send.length = 8;
// 		memcpy(to_send.data, my_array, 8);
// 		can_send(&to_send);
		
		while(1){
// 			 printf("[");
// 			 for (int i = 0; i < 4; i++){
// 				 printf("%d", js_pos[i]);
// 				 
// 				 printf(" , ");
// 			 }
 			 //printf("] \r \n");	 
		//send_js_pos(js_pos); 	
		
		//send_button_push(); check for this
		}
		
		

	return 0;
}

