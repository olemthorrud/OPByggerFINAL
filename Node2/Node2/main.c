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


int main(void)
{
	/* Initialize the SAM system, UART, CAN, internal ADC on Arduino and PWM. We are currently disabling the watch dog timer entirely for testing purposes. */
	
	SystemInit();
	configure_uart();  
	uint32_t BR = 0x00143156;
	can_init_def_tx_rx_mb(BR); 
	adc_init();
	pwm();
	//dac_init();
	WDT->WDT_MR = WDT_MR_WDDIS;  // Disable watchdog timer
	motor_init();
	
	/* Variables to keep track of joystick position and goal-scoring */
	
	volatile uint8_t js_pos[4];
	volatile uint16_t* adc_converted;
	*adc_converted = NULL;
	int score = 0;
	int newGoal = 0; 	
	volatile uint16_t* integrated_error;
	*integrated_error = NULL;
	
	uint8_t balle;
	uint8_t test_8; 
	
	uint16_t test = 0; 	
	//int test = 0; 	
	uint8_t ref = 70; 
	while(1){
		//	led_test();
		//_delay_ms(500); 
 		get_js_pos(js_pos);
// 		set_duty_cycle(calculate_dc(js_pos,0),5);
// 		set_duty_cycle(calculate_dc(js_pos,1),6);
// 		
// 		newGoal = getNewGoal(adc_converted); 
// 		
// 		if (newGoal){
// 			score++;
// 			printf("GOOOOLAZZOO!! The score currently is: %d \n \r", score);
// 			_delay_ms(2000);
// 		}
 		
  		//printf("BALLE %u \r \n" , js_pos[0]);
		//_delay_ms(100); 
  		
 		//test_8 = calibrate_enc(get_stat());
 		//printf("Position is : %u \r \n", test_8);
		  
 		test = controller(ref, calibrate_enc(get_stat()));   
 		printf("reference is : %u, recorded position is: %u, and the difference is: %u \r \n", ref, get_stat(), test);  
		dac_transmit(test); //dette gikk dårlig. Du må se på kontrolleren, den løsningen jeg har prøvd meg på der funker ikke noe særlig. 
// 		_delay_ms(100);

	
		
 	} 		
}
