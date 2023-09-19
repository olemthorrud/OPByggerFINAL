/*
 * IncFile1.h
 *
 * Created: 19.09.2023 17:22:04
 *  Author: pmherdle
 */ 


#pragma once


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void oled_init();

static void oled_write(uint8_t cmd);

void oled_fill(void);

void oled_home(); 
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_clear_line(int line);
void oled_pos(int row, int column);
void oled_print(char*);