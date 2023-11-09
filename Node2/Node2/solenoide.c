/*
 * solenoide.c
 *
 * Created: 09.11.2023 11:28:59
 *  Author: pmherdle
 */ 

#include "solenoide.h"

void pin_init(){
	//PMC->PMC_PCER0 |= (1u << 11); // Replace ID_PIOA with the actual peripheral ID for PIOA
	PIOA->PIO_PER |= PIO_PDR_P2; // Ensure this is the correct mask for PA2
	PIOA->PIO_OER |= PIO_OER_P2; // Set PA2 as an output
	PIOA->PIO_SODR |= PIO_SODR_P2; // Set PA2 to low
}

void set_pin_low(){
	PIOA->PIO_CODR |= PIO_CODR_P2;
}

void set_pin_high(){
	PIOA->PIO_SODR |= PIO_SODR_P2;
}