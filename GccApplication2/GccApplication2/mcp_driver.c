/*
 * mcp_driver.c
 *
 * Created: 03.10.2023 10:15:37
 *  Author: pmherdle
 */ 

#include "mcp_driver.h"
#include "spi_driver.h"
#include <stdio.h>

uint8_t mcp_read(uint8_t address){
	PORTB &= (0 << PB4); // Set CS low
	SPI_write(READ);
	SPI_write(address);
	uint8_t data;
	data = SPI_read();
	
	PORTB |= (1 << PB4); // Set CS high
	return data;
}


void mcp_write(uint8_t address, uint8_t data) {
	PORTB &= (0 << PB4);
	SPI_write(WRITE);
	SPI_write(address); 
	SPI_write(data);
	PORTB |= (1 << PB4);
}

void request_to_send(){
		PORTB &= (0 << PB4);
		SPI_write(RTS_TXB0);
		PORTB |= (1 << PB4);
}

uint8_t read_status(){
	uint8_t data;
	PORTB &= (0 << PB4);
	SPI_write(READ_STATUS);
	data = SPI_read();
	PORTB |= (1 << PB4);
	return data;
}


void bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= (0 << PB4);
	SPI_write(BIT_MODIFY);
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);
	
	PORTB |= (1 << PB4);
}


