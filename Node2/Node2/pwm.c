/*
 * pwm.c
 *
 * Created: 03.11.2023 09:52:43
 *  Author: pmherdle
 */ 

#include "pwm.h"

void pwm(void){
	

		
		
		
		PIOC->PIO_PDR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;
		PIOC->PIO_ABSR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;
		
		PMC->PMC_PCR |= (1<< 28) | (pid);
		PMC->PMC_PCER1 |= 1 << (pid-32);
		
		PWM->PWM_CLK = 0; //resetting just in case
		PWM->PWM_CLK = (84 << 16) | (84 << 0); //seting divide factor
		PWM->PWM_CLK |= (0 << 8) | (0 << 24); //setting prescalar (?) 
		
		
		PWM->PWM_CH_NUM[5].PWM_CMR = 11; //setting channel 5 to clock A 
		PWM->PWM_CH_NUM[6].PWM_CMR = 12; //setting channel 6 to clock B
		
		PWM->PWM_ENA = PWM_ENA_CHID5 | PWM_ENA_CHID6; // Kopiert
		
		PWM->PWM_CH_NUM[5].PWM_CPRD = 20000; //(period*MCK)/84 
		PWM->PWM_CH_NUM[6].PWM_CPRD = 20000; //(period*MCK)/84 
		
		//stolen: 
		//int CDTY = (int) (PWM->PWM_CH_NUM[5].PWM_CPRD*(1 - 0.5));
		//PWM->PWM_CH_NUM[5].PWM_CDTY = PWM_CDTY_CDTY(CDTY);

}


void set_duty_cycle(float val, int chan){
	
	// 0,05 gir 1 ms
	// 0,1 inni parantes gir 2.0 ms høy
	int CDTY = (int) (PWM->PWM_CH_NUM[chan].PWM_CPRD*(1 - val));
	PWM->PWM_CH_NUM[chan].PWM_CDTY = PWM_CDTY_CDTY(CDTY);
}

float calculate_dc(uint8_t* js_pos,int dir){
	    // dir = 0 means left/right
		int K = js_pos[dir];
		float r = (0.05/255)*K + 0.05;
		
		return r;
}