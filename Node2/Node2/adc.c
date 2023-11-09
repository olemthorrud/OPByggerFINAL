/*
 * adc.c
 *
 * Created: 04.11.2023 14:06:06
 *  Author: pmherdle
 */ 

#include "adc.h"

void adc_init(){
	ADC->ADC_CR = 1;
	

	ADC->ADC_MR = (1 << 7);
	
	
	PMC->PMC_PCR |= (1<< 28) |(0 << 16) |  (0 << 17) | (p_id);
	PMC->PMC_PCER1 |= 1 << (p_id-32);
	
	ADC->ADC_CHER = (1 << 2); // Using channel 2. This corresponds to PA4 which is A5 on th shield
	
	ADC->ADC_CR = (1 << 1);
}

uint16_t adc_drive(uint16_t* val){
	*val = ADC->ADC_LCDR; 
	//printf("ADC is: %u \n \r", *val);
	return *val;
	
}

int getNewGoal(uint16_t* val){
	int from_ADC, return_value;
	return_value = 0; 
	 
	from_ADC = adc_drive(val);
	//printf("FROMADC is: %u \r \n", from_ADC); 
	if (from_ADC < 1800){  //This value has been different. First time we set it as 700
		return_value = 1; 
	}
	return return_value; 
}


