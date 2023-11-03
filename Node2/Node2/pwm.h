/*
 * pwm.h
 *
 * Created: 03.11.2023 09:52:34
 *  Author: pmherdle
 */ 



#pragma once
#include <sam3x8e.h>
#include "delay.h"


#define pid 36


void pwm(void);

void set_duty_cycle(float val, int chan);
	
	
	
float calculate_dc(uint8_t* js_pos, int dir);