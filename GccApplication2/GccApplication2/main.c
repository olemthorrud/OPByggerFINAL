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

/*
int main(void)
{
	
	volatile int js_pos[4]; 
	adc_driver(js_pos); 
	volatile int arrow_pos = 0;
	int* arrow_pos_ptr = &arrow_pos; 
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
	oled_clear();
	oled_fill();
	
	_delay_ms(1000);
	
	oled_clear(); 
	
	
	menu_init(arrow_pos_ptr);
	_delay_ms(1000);
	oled_arrow(arrow_pos_ptr , 1);
	 
	while (1)
	{

		adc_driver(js_pos);
		_delay_ms(100);
		if (js_pos[1] < 80){
			oled_arrow(arrow_pos_ptr, 1);	
		}else if (js_pos[1] > 200) {
			oled_arrow(arrow_pos_ptr, 0);
		}
}
	

	//oled_clear(); 
// 	char character =  'c'; 
// 	oled_print(character); 
//	print("hei");	

//	oled_arrow(arrow_pos_ptr , 1);

	return 0; 
}






/*
int main(void)
{
	

	// Initialize UART
	USART_Init(UBRR);
	uart_link_printf();
	//Initialize SRAM
	SRAM_init();
	//Initialize ADC clock
	adc_config_clock();
	
	
	spi_init();
	

	
	

	//oled_clear();
	// 	char character =  'c';
	// 	oled_print(character);
	//	print("hei");

	//	oled_arrow(arrow_pos_ptr , 1);

	return 0;
}


*/


int main(void)
{
		volatile int js_pos[4];
		adc_driver(js_pos);
		volatile int arrow_pos = 0;
		int* arrow_pos_ptr = &arrow_pos;
		USART_Init(UBRR);
		uart_link_printf();
		SRAM_init();
		adc_config_clock();
		oled_init();
		spi_init();

		
		uint8_t send = 0x01;
		uint8_t address = 0x0E;
		uint8_t lest;


			while(1){
				_delay_ms(100);
				mcp_write(address, send);
				lest = mcp_read(address);
				//printf("%u " , send);
				printf("%u " , lest);
			}
			
	
	return 0;
}