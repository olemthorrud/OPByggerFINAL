/*
 * CFile1.c
 *
 * Created: 19.09.2023 17:04:25
 *  Author: pmherdle
 */ 

#include "adc.h"


void adc_config_clock() {
	// set PB0 to output PWM timer signal
	DDRB |= 1;

	// set the TCCR0 to CTC mode with (1,0)
	TCCR0 |= (1 << WGM01);
	TCCR0 &= ~(1 << WGM00);
	
	// set PWM toggle on match with internal clock (0,1) with regitster 1 from left
	TCCR0 &= ~(1 << COM01);
	TCCR0 |= (1 << COM00);

	// set PWM signal to match with internal clock, no prescale (0,0,1) with register 2,1,0 from left
	TCCR0 &= ~(1 << CS02);
	TCCR0 &= ~(1 << CS01);
	TCCR0 |= (1 << CS00);

	// frequency set to 0.5 x F_CPU
	OCR0 = 0;
}

uint8_t adc_read(uint8_t channel) {
	volatile char* ADC_mem = (char*) 0x1400;
	ADC_mem[0] = 0;
	
	_delay_ms(9*8/F_CPU);
	
	uint8_t data;
	for (int i = 0; i <= channel; i++){
		data = ADC_mem[0];
	}
	return data;
}

int convert_horiz_JS(uint8_t A){
	
	int percentage;
	int default_pos = 142;
	int middle = 127;
	
	int nom;
	int denom;
	
	if ( A < default_pos -5){
		percentage = ((A* middle)/default_pos); //divided byt distance between default and end point //if move to left
	}
	else if ( A > default_pos + 5) {

		nom = (A -default_pos)* middle;
		denom = (255-default_pos);
		percentage = (nom/denom) + middle;   // divided by distance between default and end point //if move to left

	}
	else{
		percentage = middle;
	}
	
	return percentage;
}

void adc_driver(int* res_list){
	
	volatile int horiz_data, vert_data, slider1, slider2;
	
	volatile uint8_t A = adc_read(0); 
	horiz_data = convert_horiz_JS(A);
	res_list[0] = horiz_data;
	
	volatile uint8_t B = adc_read(1);
	vert_data = B; 
	res_list[1] = vert_data;
	
	volatile uint8_t C = adc_read(2);
	slider1 = C; //Går dette an?
	res_list[2] = slider1;
	
	volatile uint8_t D = adc_read(3);
	slider2 = D; //Går dette an?
	res_list[3] = slider2;
}

void multifunction_board_test(int* ADC_driver_data ){ // Denne funksjonen returnerer joystickposisjoner og sliderposisjoner hver sekund
		 while(1){
			 _delay_ms(1000);
			 
			 adc_driver(ADC_driver_data);
			 printf("[");

			 for (int i = 0; i < 4; i++){
				 printf("%d", ADC_driver_data[i]);
				 printf(" , ");
			 }
			 printf("] \n");
		 }
}