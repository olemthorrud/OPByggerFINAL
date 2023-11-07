/*
 * CFile1.c
 *
 * Created: 07.11.2023 12:32:51
 *  Author: pmherdle
 */ 

#include "pid.h"

uint16_t controller(uint8_t ref, uint8_t val){
	uint16_t error = 0; 
	if (ref < val){
		error = val - ref;
		set_dir_RtoL();  
	}else{
		error = ref - val;
		set_dir_LtoR();  
	}
	
//	return ((K_p *error) + T*K_i*(*integrated_error));
return ((K_p *error));
}

void motor_init() { //ikke vår egen kode
	dac_init();

	// enable PIOD pins to motor box as output
	PIOD->PIO_PER |= DIR | EN | SEL | NOT_RST | NOT_OE;
	PIOD->PIO_OER |= DIR | EN | SEL | NOT_RST | NOT_OE;

	// enable PIOC pins from motor encoder as input
	PIOC->PIO_PER |= ENCODER_DATA_MASK;
	PIOC->PIO_ODR |= ENCODER_DATA_MASK;

	// enable PIOC clock
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
	PIOD->PIO_SODR = EN; //OLES KODE - DENNE ER VIKTIG. 
	set_dir_LtoR();  
}


int16_t get_stat(){

	PIOD->PIO_CODR |= (1 << 0); //Enable output so we are able to read

	uint8_t encoder_low_bytes, encoder_high_bytes;
	int16_t encoder_value; 
	
	PIOD->PIO_SODR |= (1 << 2);  
	
	_delay_ms(2);
	
	encoder_low_bytes = (PIOC->PIO_PDSR) >> 1;
	
	PIOD->PIO_CODR |= (1 << 2);
	
	_delay_ms(2);
		
	encoder_high_bytes = (PIOC->PIO_PDSR) >> 1;
	
	encoder_value = (encoder_high_bytes << 8) | (encoder_low_bytes);  
	
	PIOD->PIO_CODR |= NOT_RST;
	PIOD->PIO_SODR |= NOT_RST;
	
	PIOD->PIO_SODR |= (1 << 0); //set !OE high again
	
	//OLES KODE - bare å endre. Noen ganger når dritten står i posisjon null, tror den at den står i posisjon 400423523 et eller annet. Prøvde meg på en kjøtthue-løsning. Funka dårlig. 
	if (encoder_value > 2000){
		encoder_value = 0; 
	}
	return encoder_value; 

}

uint8_t calibrate_enc(int16_t from_encoder){
	
	uint16_t from_encoder_casted = (uint16_t)from_encoder;
	uint8_t calibrated = (uint8_t) ((from_encoder_casted*255)/1404);
	return calibrated; 
}

void set_dir_RtoL(){
	PIOD->PIO_SODR |= (1 << 10); 
}

void set_dir_LtoR(){
	PIOD->PIO_CODR |= (1 << 10);
}