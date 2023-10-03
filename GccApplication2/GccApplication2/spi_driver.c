/*
 * spi.c
 *
 * Created: 03.10.2023 09:45:02
 *  Author: pmherdle
 */ 

#pragma once
#include <avr/io.h>
#include "spi_driver.h"
#include <avr/interrupt.h>



void SPI_write(char data) 
{
	PORTB &= (0 << PB4);
	/* Start transmission */ 
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))); 
	
	PORTB |= (1 << PB4);
}


uint8_t SPI_read(void)
{
	SPI_write(0); //We are never interested in what the slave says
	return SPDR;
}


void spi_init(){
	DDRB = (1 << PB5) | (1<< PB7) | (1<< PB4);
	SPCR = (1<< SPE) | ( 1 << MSTR) | (1 << SPR0);
}



