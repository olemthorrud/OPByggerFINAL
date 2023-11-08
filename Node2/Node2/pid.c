/*
 * CFile1.c
 *
 * Created: 07.11.2023 12:32:51
 *  Author: pmherdle
 */ 

#include "pid.h"

uint8_t p_controller(uint8_t ref, uint8_t val){
	uint8_t error = 0; 
	
	//error = ref - val;
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
// 	if (encoder_value > 2000){
// 		encoder_value = 0; 
// 	}
 	return encoder_value; 

}

uint8_t calibrate_enc(int16_t from_encoder){
	
	uint16_t from_encoder_casted = (uint16_t)from_encoder;
	uint8_t calibrated = (uint8_t) ((from_encoder_casted*255)/1404); //Denne var 1404 endret til 311 da dette plutselig var maks
	return calibrated; 
}

void set_dir_RtoL(){
	PIOD->PIO_SODR |= (1 << 10); 
}

void set_dir_LtoR(){
	PIOD->PIO_CODR |= (1 << 10);
}



uint8_t pi_controller(uint8_t ref, uint8_t val, int16_t* integrated_error){
	uint8_t error = 0;
	
	//error = ref - val;
	
	if (ref < val){
		error = val - ref;

		set_dir_RtoL();
		}else{
		error = ref - val;

		set_dir_LtoR();
	}
	
	*integrated_error += (ref-val);
	if (*integrated_error < 0)
	{
		*integrated_error = (*integrated_error)*(-1);
	}
	uint8_t i_e_reduced = (*integrated_error)*K_i*T;
	return ((K_p *error) + i_e_reduced);
}


uint8_t pi2_controller(uint8_t ref, uint8_t val, int* integrated_error){
	uint8_t error = 0;
	
	//error = ref - val;
	if (((ref-val) > 3) | ((val-ref) > 3))
	{
	
	if (ref < val){
		error = val - ref;

		set_dir_RtoL();
		}else{
		error = ref - val;

		set_dir_LtoR();
	}
	
	int integral_effect = 0;
	*integrated_error += (ref-val);
	
	int calculated_effect = *integrated_error * T*K_i;
	int calculated_effect_n = *integrated_error * T*K_i* (-1);
	
	if (calculated_effect < 0)
	{
		integral_effect = (uint8_t) calculated_effect_n;
	}
	else
	{
		integral_effect = (uint8_t) calculated_effect;
	}
	return ((K_p *error) + integral_effect);
	}
	else{return 0;}
}
// Forklaring: Vi vil returnere en uint8_t. Derfor må vi lage en integral_effet som er uint8_t
// For å slippe et rent helvete med fortegn opererer vi med ints ellers og lager derfor to ints som viser integrert error ganget med T og Ki.
// Vi sjekker så om integralet er positivt eller negativt for å velge om vi skal gange med -1 for alltid å få positiv verdi.
//Prøver vi å kaste negativ verdi som en uint_8t blir det trøbbel




void start(){
	motor_init();
	set_dir_RtoL();  
	dac_transmit(120);
	_delay_ms(3000);
	dac_transmit(0);
	motor_init();
}