/**
 * @file 
 * @brief Module for SysTick timer delay
 */


#ifndef NODE2_TIMER_H
#define NODE2_TIMER_H


#include <stdint.h>

static void SysTick_init_ms(int period); 

void _delay_ms(uint16_t ms);


#endif