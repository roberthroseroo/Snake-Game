#include "lpc17xx.h"               /* NXP LPC17xx definitions            */
#include "Potenciometer.h"


void Potenciometer_init(void){
 LPC_PINCON->PINSEL3 |= 0xC0000000;	/* P1.31, A0.5, function 11 */	
 LPC_SC->PCONP |= (1<<12); // Enable power to ADC block
 LPC_ADC->ADCR = (1<<5) | //                  select AD0.5 pin
								 (4<<8) | // ADC clock is 25MHz/5
                 (1<<21); // enable ADC
 LPC_ADC->ADCR |= (1<<24);//|(1<<16); // starts the A/D converter
 

 LPC_ADC->ADINTEN &= (1<<8); // global enable interrupt
	
 NVIC_EnableIRQ(ADC_IRQn); // enable ADC Interrupt	
}
