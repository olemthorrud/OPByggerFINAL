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

static void oled_write_data(uint8_t data){
	volatile char* address = (char*) 0x1200;
	address[0] = data;
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
	oled_clear();
	for (int i = 0 ; i < 8 ; i++)
	{
		oled_goto_line(i);
		oled_goto_column(0);
		for (int j = 0 ; j < 128 ; j++)
		{
			oled_goto_column(j); 
			oled_write_data((0xff));
		}
	}
}
	
void oled_clear() {
	for (int page = 0; page <= 7; page++) {
		oled_pos(page, 0);
		for (int col = 0; col <= 127; col++) {
			oled_write_data(0);
		}
	}
}

void oled_print(char c) {
	//oled_goto_line(0);
	//oled_goto_column(0);
	if (' ' <= c && c <= '~') {
		//printf("I get here"); 
		for (int i = 0; i < FONT_LENGTH; i++) {
			uint8_t character = pgm_read_byte(&(font8[c - ASCII_OFFSET][i]));
			oled_write_data(character);
		}
	}
}

void oled_pos(int line, int col) {
	oled_goto_line(line);
	oled_goto_column(col);
}


void print(const char* str) {
	int i = 0; 
	while (str[i] != '\0') {
		oled_print(str[i]);
		printf("%c", str[i]); 
		++i;
	}
}



void oled_arrow(int* arrow_pos , int k){

	
	oled_pos(*arrow_pos,1);
//	oled_write_data(' '); 
	oled_print(' ');
	
	if(k == 1 ){
		*arrow_pos += 1;
		
		if (*arrow_pos == 8){
			*arrow_pos = 0;
		}
	}
	else{
		if(*arrow_pos == 0){
			*arrow_pos = 7;
		}
		else{
			*arrow_pos -= 1;
		}

	}

	
		oled_pos(*arrow_pos, 1);
		oled_print('>');

	}
	
	
void menu_init(int* arrow_pos){
	oled_pos(0,8);
	print("Play Game");
	oled_pos(1,8);
	print("Choose settings");
	oled_pos(2,8);
	print("Choose mode");
	
	oled_pos(*arrow_pos,0);
	oled_print('>');
	
}



void oled_test_meny(int* arrow_pos_ptr, int js_pos[4] ){
	oled_init();
	oled_clear();
	oled_fill();
	_delay_ms(1000);
	oled_clear();
	menu_init(arrow_pos_ptr);

	while (1)
	{

		adc_driver(js_pos);
		_delay_ms(350); // Denne var 100 ms, men det var plutselig veldig veldig raskt når jeg flyttet den inn i funksjonen
		if (js_pos[1] < 80){
			oled_arrow(arrow_pos_ptr, 1);
			}else if (js_pos[1] > 200) {
			oled_arrow(arrow_pos_ptr, 0);
		}
	}
}
	
	
	
