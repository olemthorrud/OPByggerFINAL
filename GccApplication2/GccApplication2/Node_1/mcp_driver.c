/*
 * mcp_driver.c
 *
 * Created: 03.10.2023 10:15:37
 *  Author: pmherdle
 */ 

#include "mcp_driver.h"
#include "spi_driver.h"
#include "uart.h"
#include <stdio.h>

#define F_CPU_osc 16000000

uint8_t mcp_read(uint8_t address){
	PORTB &= (0 << PB4); // Set CS low
	SPI_write(MCP_READ);
	SPI_write(address);
	uint8_t data;
	data = SPI_read();
	
	
	PORTB |= (1 << PB4); // Set CS high
	return data;
}


void mcp_write(uint8_t address, uint8_t data) {
	PORTB &= (0 << PB4);
	SPI_write(MCP_WRITE);
	SPI_write(address); 
	SPI_write(data);
	PORTB |= (1 << PB4);
}

void request_to_send(){
		PORTB &= (0 << PB4);
		SPI_write(MCP_RTS_TX0);
		PORTB |= (1 << PB4);
}

uint8_t read_status(){
	uint8_t data;
	PORTB &= (0 << PB4);
	SPI_write(MCP_READ_STATUS);
	data = SPI_read();
	PORTB |= (1 << PB4);
	return data;
}


void bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= (0 << PB4);
	SPI_write(MCP_BITMOD);
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);
	
	PORTB |= (1 << PB4);
}

void set_loopback(){
	 bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	 

	 // verify new mode
	 uint8_t new_mode = mcp_read(MCP_CANSTAT);
	 if ((new_mode & MODE_MASK) != MODE_LOOPBACK) {
		 printf("ERROR: failed to set mode to loopback. \r \n");
	}
}

void set_normal_mode(){
	bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	

	// verify new mode
	uint8_t new_mode = mcp_read(MCP_CANSTAT);
	if ((new_mode & MODE_MASK) != MODE_NORMAL) {
		printf("ERROR: failed to set mode to normal. \r \n");
	}
}

void mcp_init() {
	spi_init();
	mcp_reset();

	_delay_ms(3);
	
	bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
	
	

	uint8_t value = mcp_read(MCP_CANSTAT); 
	
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("ERROR: MCP2515 not in configuration mode after reset. \r\n");
	}
	

	// set CAN bitrate with BAUD rate 250 000
 	uint8_t BRP = (F_CPU_osc / (2*16*(250000)));

 	mcp_write(MCP_CNF1, SJW4 | (BRP - 1));
 	mcp_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((PS1 - 1) << 3) | (PROPAG - 1));
 	mcp_write(MCP_CNF3, WAKFIL_DISABLE | (PS2 - 1));
}

void mcp_reset() {
	PORTB &= (0 << PB4);
	SPI_write(MCP_RESET);
	PORTB |= (1 << PB4);
}

void mcp_test(){
	 uint8_t send = 0x51;
	 uint8_t address = 31;
	 uint8_t lest;
	 		
	 	while(1){
		 	mcp_write(address, send);
		 	lest = mcp_read(address);
			printf("%u  \r \n" , lest);
			
			_delay_ms(1200);
	 		}
}