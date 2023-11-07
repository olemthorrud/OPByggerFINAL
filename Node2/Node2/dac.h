/*
 * dac.h
 *
 * Created: 07.11.2023 09:28:48
 *  Author: pmherdle
 */ 

#pragma once

#include <sam3x8e.h>
#include "delay.h"
#include <stdio.h>
#include <stdint.h>

#define periph_id 38

void dac_init();
void dac_transmit(uint8_t data);