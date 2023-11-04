/*
 * adc.h
 *
 * Created: 04.11.2023 14:05:54
 *  Author: pmherdle
 */ 

#pragma once
#include <sam3x8e.h>
#include "delay.h"

#define p_id 37



void adc_init();

uint16_t adc_drive(uint16_t* val);

int getNewGoal(uint16_t* val);