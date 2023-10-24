/*
 * led.c
 *
 * Created: 24.10.2023 13:18:38
 *  Author: pmherdle
 */ 




#include "led.h"


void led_test(void){
	PMC->PMC_PCER0 = ( 1<< ID_PIOA);
	PIOA->PIO_OER = (1<<19 ) | (1<<20);
	PIOA->PIO_PER = (1<<19 ) | (1<<20);
	PIOA->PIO_CODR = (1<<19 ) | (1<<20);
	
	while (1)
	{
		
		PIOA->PIO_SODR = (1<<19 ) | (1<<20);	//_delay_ms(1000);
		
		_delay_ms(1000);
		
		PIOA->PIO_CODR = (1<<19 ) | (1<<20);
		
		_delay_ms(1000);
		
		
	}
}
