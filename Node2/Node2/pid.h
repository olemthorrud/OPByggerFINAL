/*
 * pid.h
 *
 * Created: 07.11.2023 12:32:42
 *  Author: pmherdle
 */ 

#pragma once
#include <sam3x8e.h>
#include "delay.h"

#define K_p 1
#define K_i 2
#define T 1/100



#define DIR             PIO_PD10
#define EN              PIO_PD9
#define SEL             PIO_PD2
#define NOT_RST         PIO_PD1
#define NOT_OE          PIO_PD0
#define ENCODER_DATA_MASK   (0xFF << 1)





uint8_t p_controller(uint8_t ref, uint8_t val); // Husk å ta inn pointer til integrert opp feil

uint8_t pi_controller(uint8_t ref, uint8_t val, int16_t *integrated_error); 

uint8_t pi2_controller(uint8_t ref, uint8_t val, int *integrated_error); 

int16_t get_stat();

void motor_init();

int motor_read_encoder();
uint8_t calibrate_enc(int16_t from_encoder); 

void set_dir_RtoL();

void set_dir_LtoR();


void start();