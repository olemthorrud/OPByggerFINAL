/*
 * Can.c
 *
 * Created: 17.10.2023 10:58:13
 *  Author: pmherdle
 */ 

#include "can.h"


void can_init(){
	mcp_init();
}



void can_send(can_message* message){

	mcp_write(MCP_TXB0_SIDH, message->id >> 3);
	mcp_write(MCP_TXB0_SIDL, (message->id & 0b00000000111) << 5);
	mcp_write(MCP_TXB0_DLC, message->length);
		

	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0_D0 + i, message->data[i]);
	}
	 
	request_to_send(); //request to send on TXB0 
}

int can_recieve(can_message* message) {
	if (mcp_read(MCP_CANINTF) & MCP_RX0IF) {
		// read from buffers, shift to combine high and low bits
		uint8_t id_low_bits = mcp_read(MCP_RXB0SIDL);
		uint8_t id_high_bits = mcp_read(MCP_RXB0SIDH);
		message->id = (id_low_bits >> 5) + (id_high_bits << 3);
		message->length = mcp_read(MCP_RXB0DLC);
		
		for (int m = 0; m < message->length; m++) {
			message->data[m] = mcp_read(MCP_RXB0D0 + m);
		}
		
		bit_modify(MCP_CANINTF,1,0);
	}
	
	else {
		return 1;
	}

	return 0;
}


void can_test(unsigned short id, unsigned char length, char data[]){
 	
		
	can_message to_send;
	to_send.id = id;
	to_send.length = length;
	memcpy(to_send.data, data, length);
	can_send(&to_send);
	//_delay_ms(50);
	can_message received;
	int K = can_recieve(&received);
	printf("the received ID is: %hu  \r \n", received.id);
	printf("the received length is: %u  \r \n", received.length);

	for (int i = 0; i < received.length; i++)
	{
		printf("char is: %c \r \n", received.data[i]);
	}
}


void send_js_pos(uint8_t* js_pos){
	adc_driver(js_pos);
	can_message to_send;
	to_send.id = 1;
	to_send.length = 4;
	//char* js_pos_as_chars;
//	printf("[ ");
// 	for (int i = 0; i < 4; i++)
// 	{
// 		printf("%d , ",js_pos[i]); 
// 	}
// 	printf("]");
// 	printf("\r\n");
	memcpy(to_send.data, js_pos, 4);
	can_send(&to_send);
}