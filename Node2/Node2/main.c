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
	dac_init();
	WDT->WDT_MR = WDT_MR_WDDIS;  // Disable watchdog timer
	
	start();  // sets to correct position and initiates motor
	
	/* Variables to keep track of joystick position and goal-scoring */
	
	volatile uint8_t js_pos[4];
	volatile uint16_t* adc_converted;
	*adc_converted = NULL;
	int score = 0;
	int newGoal = 0; 	
	
	uint8_t message_from_button[8]; 
	
	
	
	//volatile uint16_t integrated_error = 0;
	volatile int integrated_error = 0;
 	uint8_t power = 0;
 	uint8_t calculated_pos; 
	int16_t encoder_val = 0; 
	
	



	while(1){


		//_delay_ms(500); 
  		//get_js_pos(js_pos);
//  		set_duty_cycle(calculate_dc(js_pos,0),5);
//  		set_duty_cycle(calculate_dc(js_pos,1),6);
		 
		
// 		newGoal = getNewGoal(adc_converted); 
// 		if (newGoal){
// 			score++;
// 			printf("GOOOOLAZZOO!! The score currently is: %d \n \r", score);
// 			_delay_ms(2000);
// 		}
 		
//   		printf("Ref is %u \r \n" , js_pos[0]);
 		//dac_transmit(js_pos[0]);
 	//	_delay_ms(10); 
 	//	test_8 = calibrate_enc(get_stat());
	 
	 
	 
// Tilhørende en ok fungerende pi K_p = 0.8
/*
	    test = get_stat();
		test_8 = calibrate_enc(test);
		printf("%u ", js_pos[0]);
 		printf("%u ", test_8);
 		balle = pi_controller(js_pos[0], test_8, &integrated_error); 
		printf("padrag %d  \r \n", balle);
		_delay_ms(2);
		dac_transmit(balle);
*/


//Tilhørende en p som funker. K_P 1.8		


// 		encoder_val = get_stat();
// 		calculated_pos = calibrate_enc(encoder_val);
// 		power = p_controller(js_pos[0],encoder_val);
// 		_delay_ms(2);
// 		dac_transmit(power);
// 	


 		get_js_pos(js_pos); //JSPOS SENDES NÅ IKKE FRA NODE 1, IKKE BLI STRESSA
		
		//printf("%d", message_from_button[0]);

// 	    encoder_val = get_stat();
// 	    calculated_pos = calibrate_enc(encoder_val);
// 	    power = pi2_controller(js_pos[0], calculated_pos, &integrated_error);
// 		//printf("verdiene fra multifuc board er %d, %d, %d, %d  \r \n", js_pos[0], js_pos[1], js_pos[2], js_pos[3]);
// 	    _delay_ms(20);
// 	    //transmit(power);

		
 	} 		
}
