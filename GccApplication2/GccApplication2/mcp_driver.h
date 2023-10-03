/*
 * IncFile1.h
 *
 * Created: 03.10.2023 10:15:05
 *  Author: pmherdle
 */ 


#pragma once
#include <avr/io.h>


#define READ 0x03
#define WRITE 0x02
#define RESET 0xC0

#define RTS_TXB0 0x81
#define READ_STATUS 0xA0
#define BIT_MODIFY 0x05

uint8_t mcp_read(uint8_t address);

void mcp_write(uint8_t address, uint8_t data);

void request_to_send();

uint8_t read_status();

void bit_modify(uint8_t address, uint8_t mask, uint8_t data);

