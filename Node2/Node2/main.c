/*
 * Node2.c
 *
 * Created: 24.10.2023 13:16:53
 * Author : pmherdle
 */ 




#include <sam.h>
#include <sam3x8e.h>
#include <stdio.h>
#include <stdint.h>


#include "led.h"
#include "delay.h"
#include "utdelt/uart.h"
#include "utdelt/printf-stdarg.h"
#include "utdelt/can_controller.h"
#include "utdelt/can_interrupt.h"



int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	configure_uart();
	//uint32_t BR = (SMP << 24) | (BRP << 16) | ((SJW-1) << 12) | ((PROPAG-1) << 8) | ((PS1-1) << 4) | (PS2 - 1);
	uint32_t BR = 0x00143156;
	can_init_def_tx_rx_mb(BR);
	
	while(1){}
	
	


	led_test();
}
