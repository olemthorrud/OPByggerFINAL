/*
 * IncFile1.h
 *
 * Created: 19.09.2023 17:04:05
 *  Author: pmherdle
 */ 



#pragma once


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h> //OLES KODE
#include "can.h"


void adc_config_clock(void);

uint8_t adc_read(uint8_t channel);

int convert_horiz_JS(uint8_t A);

void adc_driver(uint8_t* ADC_driver_data); //ADC_driver_data er en array som sendes som pass-by-reference

void multifunction_board_test(int* ADC_driver_data); 

void button_IR_init(); 


//void set_button_high();