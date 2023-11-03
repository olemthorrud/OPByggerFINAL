/*
 * Node2.c
 *
 * Created: 24.10.2023 13:16:53
 * Author : pmherdle
 */ 




#include <sam.h>
#include <sam3x8e.h>
#include <stdio.h>
#include <stdint.h>


#include "led.h"
#include "delay.h"
#include "utdelt/uart.h"
#include "utdelt/printf-stdarg.h"
#include "utdelt/can_controller.h"
#include "utdelt/can_interrupt.h"
#include "pwm.h"


int main(void)
{
	/* Initialize the SAM system */
	
	
	SystemInit();
	configure_uart();
	
	volatile uint8_t js_pos[4];
	 
	uint32_t BR = 0x00143156;
	can_init_def_tx_rx_mb(BR); 
	
	
	WDT->WDT_MR = WDT_MR_WDDIS;  // Disable watchdog timer
	pwm();
	
	
	//set_duty_cycle(0.5,5);
	//set_duty_cycle(0.5,6);
	
	
	get_js_pos(js_pos);
	
/*	
	while(1){	
 	printf("[ ");
	for (int i = 0 ; i< 4; i++)
	{
		printf("%d ,", js_pos[i]);
	}
	printf("] \n\r");
	get_js_pos(js_pos);
	_delay_ms(500); 
	}
*/	
	printf("Jeg er her");
	//led_test();
	while(1){
		
		set_duty_cycle(calculate_dc(js_pos,0),5);
		set_duty_cycle(calculate_dc(js_pos,1),6);

		
		get_js_pos(js_pos);
		
		printf("[ ");
			for (int i = 0 ; i< 4; i++)
			{
				printf("%d ,", js_pos[i]);
			}
			printf("] \n\r");
		
	}

}
