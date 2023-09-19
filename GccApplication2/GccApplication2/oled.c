/*
 * CFile1.c
 *
 * Created: 19.09.2023 17:21:57
 *  Author: pmherdle
 */ 


#include "oled.h"


void oled_init()
{
	oled_write(0xae); // display off
	oled_write(0xa1); //segment remap
	oled_write(0xda); //common pads hardware: alternative
	oled_write(0x12);
	oled_write(0xc8); //common output scan direction:com63~com0
	oled_write(0xa8); //multiplex ration mode:63
	oled_write(0x3f);
	oled_write(0xd5); //display divide ratio/osc. freq. mode
	oled_write(0x80);
	oled_write(0x81); //contrast control
	oled_write(0x50);
	oled_write(0xd9); //set pre-charge period
	oled_write(0x21);
	oled_write(0x20); //Set Memory Addressing Mode
	oled_write(0x02);
	oled_write(0xdb); //VCOM deselect level mode
	oled_write(0x30);
	oled_write(0xad); //master configuration
	oled_write(0x00);
	oled_write(0xa4); //out follows RAM content
	oled_write(0xa6); //set normal display
	oled_write(0xaf); // display on
}


static void oled_write(uint8_t cmd){
	volatile char* adress = (char*) 0x1000;
	adress[0] = cmd;
}



void oled_goto_line(int line){
	int commando = 0xB0 + line;
	oled_write(commando);
}



void oled_goto_column(int column){
	oled_write(column % 16);
	oled_write(0x10 + (column/16));
}

void oled_fill(){
	for (int i = 0 ; i < 8 ; i++)
	{
		oled_goto_line(i);
		oled_goto_column(0);
		for (int j = 0 ; j < 128 ; j++)
		{
			oled_write((0xff));
		}
	}
}
	
/*
void oled_clear_line(int line){}
void oled_pos(int row, int column){}
void oled_print(char* c){}
void oled_home(){}
	*/