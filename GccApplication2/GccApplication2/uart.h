/*
 * IncFile1.h
 *
 * Created: 05.09.2023 12:41:25
 *  Author: pmherdle
 */ 
#pragma once

#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define UBRR F_CPU / 16 / BAUD - 1
#include <stdio.h>

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void uart_link_printf();


