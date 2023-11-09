/*
 * can_interrupt.h
 *
 * Author: Gustav O. Often and Eivind H. Jølsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include <stdio.h>
#include <stdint.h>
#ifndef CAN_INTERRUPT_H_
#define CAN_INTERRUPT_H_
void CAN0_Handler       ( void );



void get_js_pos(uint8_t* adress);
void button_push();

#endif /* CAN_INTERRUPT_H_ */