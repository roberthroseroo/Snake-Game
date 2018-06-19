#include "potenciometer.h"
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "../GLCD.h"

extern int lvl;

void  ADC_IRQHandler (void)	  
{
	//uint32_t regSTAT; 
	uint32_t ADC_result;
	
	//regSTAT = LPC_ADC->ADSTAT;	/* Read ADC will clear the interrupt */
	ADC_result=(LPC_ADC->ADGDR>>4)&0xFFF; /* store the result on ADC_Result*/
	
	/*the value of the ADC result will control the delay, that means how fast the function movement is called. The dificulty of the game */
	if (ADC_result<0x3FF){
		lvl = 0;
	}
	if (ADC_result>=0x3FF & ADC_result<0x7FE){
		lvl = 1;
	}
	if (ADC_result>=0x7FE & ADC_result<0xBFD){
		lvl = 2;
	}
	if(ADC_result>0xBFD){
		lvl = 3;
	}
	enable_timer(0);	 /*the timer is activated to wait a second before starting the potenciometer again*/
}

