/*
 * IncFile1.h
 *
 * Created: 19.09.2023 17:22:04
 *  Author: pmherdle
 */ 


#pragma once
#include "fonts.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define FONT_LENGTH 8
#define ASCII_OFFSET 32

void oled_init();

static void oled_write(uint8_t cmd);

void oled_fill(void);

void oled_home(); 
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_print(char c);
static void oled_write_data(uint8_t data); 
void oled_clear();
void oled_pos(int line, int col);
void print(const char* str); 

void oled_arrow(int* arrow_pos , int k);


void menu_init(int* arrow_pos);