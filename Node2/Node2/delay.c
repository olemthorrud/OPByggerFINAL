#include "delay.h"
#include <sam.h>
#include <sam3x8e.h>

#define F_CPU                   84000000

volatile uint32_t wait_ticks = 0;


static void SysTick_init_ms(int period) {
	// set SysTick reload value
	SysTick->LOAD = ((int)((F_CPU/1000000)*period))-1;

	// reset SysTick counter value
	SysTick->VAL = 0;

	// set SysTick interrupt priority
	NVIC_SetPriority(SysTick_IRQn, 0); //highest priority

	// set SysTick timer to MCK, enable interrupt and timer
	SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
}
//tungt inspirert

void _delay_ms(uint16_t ms) {
	wait_ticks = ms;
	SysTick_init_ms(1000);
	while(wait_ticks != 0);
}


void SysTick_Handler(void) {
	if(wait_ticks!=0) {
		wait_ticks--;
	}
	else {
		SysTick->CTRL = 0;
	}
}