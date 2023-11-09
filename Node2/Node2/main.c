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
#include "adc.h"
#include "dac.h"
#include "pid.h"
#include "solenoide.h"


int main(void)
{
	/* Initialize the SAM system, UART, CAN, internal ADC on Arduino and PWM. We are currently disabling the watch dog timer entirely for testing purposes. */
	
	SystemInit();
	configure_uart();  
	uint32_t BR = 0x00143156;
	can_init_def_tx_rx_mb(BR); 
	adc_init();
	pwm();
	dac_init();
	pin_init(); 
	WDT->WDT_MR = WDT_MR_WDDIS;  // Disable watchdog timer
	
	
	start();  // sets to correct position and initiates motor
	
	/* Variables to keep track of joystick position and goal-scoring */
	
	volatile uint8_t js_pos[4];
	volatile uint16_t* adc_converted;
	*adc_converted = NULL;
	int score = 0;
	int newGoal = 0; 	
	

	
	volatile int integrated_error = 0;
 	uint8_t power = 0;
 	uint8_t calculated_pos; 
	int16_t encoder_val = 0; 
	
	

	


	while(1){


  		get_js_pos(js_pos);
		  		printf("[ ");
		  		for (int i = 0 ; i< 4; i++)
		  		{
			  		printf("%d ,", js_pos[i]);
		  		}
		  		printf("] \n\r");
  		set_duty_cycle(calculate_dc(js_pos,3),5);

// 		newGoal = getNewGoal(adc_converted); 
// 		if (newGoal){
// 			score++;
// 			printf("GOOOOLAZZOO!! The score currently is: %d \n \r", score);
// 		//	_delay_ms(2000);
// 		}
	 
	    encoder_val = get_stat();
	    calculated_pos = calibrate_enc(encoder_val);
	    power = pi2_controller(js_pos[0], calculated_pos, &integrated_error);
		if (js_pos[2] < 10)
		{set_pin_low();
		}
	    _delay_ms(50);
		set_pin_high();
	    dac_transmit(power);

		
 	} 		
}
