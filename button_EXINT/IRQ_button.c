#include "button.h"
#include "lpc17xx.h"
#include "../menu/menu.h"
extern int pass_instructions;

void EINT0_IRQHandler (void)	  
{
  LPC_SC->EXTINT |= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
  LPC_SC->EXTINT |= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT |= (1 << 2);     /* clear pending interrupt         */    
}


