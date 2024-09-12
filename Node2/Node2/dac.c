/*
 * dac.c
 *
 * Created: 07.11.2023 09:29:13
 *  Author: pmherdle
 */ 

#include "dac.h"


void dac_init(){
	DACC->DACC_CR = DACC_CR_SWRST;
	
	PMC->PMC_PCR |= (1<< 28) |(0 << 16) |  (0 << 17) | (periph_id);
	PMC->PMC_PCER1 |= 1 << (periph_id-32);
	
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1 | (1 << 27); //Startuptime på 512 clock cycles
	DACC->DACC_CHER = 2;
}

void dac_transmit(uint8_t data){
	//DACC->DACC_CDR = data; 
 	uint16_t twelve_bit_value = (uint16_t)((data* 4096)/256);
	// uint16_t twelve_bit_value = (uint16_t)(data << 3);
 
 	DACC->DACC_CDR = twelve_bit_value;
}
