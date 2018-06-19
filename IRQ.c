/*----------------------------------------------------------------------------
 * Name:    IRQ.c
 * Purpose: IRQ Handler
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/


unsigned long ticks = 0;
unsigned char ClockLEDOn;               /* On for 30 ms every 50 ms           */
unsigned char ClockLEDOff;              /* On for 20 ms every 50 ms           */
unsigned char ClockANI;                 /* Clock for Animation 150 ms         */
/*clock rates for the different levels of difficulty of the game*/

unsigned char ClockRefresh0;            /*Every 30ms*/ 
unsigned char ClockRefresh1;						/*Every 60ms*/
unsigned char ClockRefresh2;						/*Every 80ms*/
unsigned char ClockRefresh3;						/*Every 90ms*/
unsigned char ClockLetters;							/*Clock to write the letters in the screen*/
unsigned char ClockTicks;


/*----------------------------------------------------------------------------
  Systick Interrupt Handler
  SysTick interrupt happens every 10 ms
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) {
  ticks++;
	ClockTicks=1; 
  switch (ticks) {
    case  3:  /*30 ms passed*/
      ClockRefresh0 = 1;
      break;
    case  5:  /*50 ms passed*/
			ClockLetters =1;
      break;
		case 6:   /*60 ms passed*/
			ClockRefresh1 = 1;
		 ClockRefresh0 = 1;
			break;
    case 9:
      ClockRefresh2 = 1;
		  ClockRefresh0 = 1;
      break;
		case 10:
			ClockLetters =1;
      break;
    case 12:
			ClockRefresh3 = 1;
      ClockRefresh0 = 1;
		  ClockRefresh1 = 1;
			ticks =0;
    default:
      break;
  }
}
