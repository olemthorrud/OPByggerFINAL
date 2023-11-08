/*
 * Can.h
 *
 * Created: 17.10.2023 10:58:01
 *  Author: pmherdle
 */ 

#pragma once

#include "mcp_driver.h"

typedef struct{
	unsigned short id;
	unsigned char length;
	char data[8];
}can_message;
	

void can_init();

void can_send(can_message* message);

int can_recieve(can_message* message);

void can_test(unsigned short id, unsigned char length, char data[]); 


void send_js_pos(uint8_t* js_pos);


void send_button_push();

can_message* generate_button_IR_can_msg(); 

//To facilitate sending a CAN message that tells of an interrupt




