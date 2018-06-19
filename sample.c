/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: SnakeGame implementation
 *----------------------------------------------------------------------------
 * Computer Architectures Special Project
 *Copyright (c) 2018 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------
 *Carlos José Peña Agreda      	s250953@studenti.polito.it
 *Roberth Reynel Rosero Osorio	s251640@studenti.polito.it*/
                  
#include <stdio.h>  
#include <stdlib.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "button_EXINT/button.h"        /*library containing the interrupts of the buttons*/
#include "potenciometer/potenciometer.h"/*library containing the potenciometer functions and interrupts*/
#include "timer/timer.h" /*library containing the timer interrupts functions*/
#include "GLCD.h"/*library used for the control of the display*/
#include "movement/movement.h"/*library used for the control of the snake*/
#include "menu/menu.h"/*library used for the grafical interface*/


/* definition of all global variables */

int x=100, //x and y are the variables used for the position of the snake
		y=100,
		direction = 1,//this variables is the direction of the snake
		x1=100,// x1, x2, y1,y2 are the additional variables used for the tail of the snake
		y1=100,
		x2=100,
		y2=100,
		delay = 60,
		lvl, // level of the difficulty
		index_color_game = 6, //index used for the color of the background of the game
		index_color_snake = 12;// index used for the color of the snale
char point_char[10][5]={"00","01","02","03","04","05","06","07","08","09"};// string used for priting the currents points of the user 
int	points = 0;

char levels[4][10] = {"  CA's  "," Expert ","Beginner"," Dummy  "};  //string used for printing the current level of the game
int colors[]={0x0000,0x000F,0x03E0,0x03EF,0x7800,0x780F,0x7BE0,0xC618,
							0x7BEF,0x001F,0x07E0,0x07FF,0xF800,0xF81F,0xFFE0,0xFFFF};// string containing the diferent values of the color
extern uint32_t ADC_result;//value obtained with the potenciomenter
							
/* the ClockRefresh variables are variables used for the counting the number of ticks in that the system has been running
the differet variables are for different number of ticks. This is used of the difficulty. The faster the snake the less ticks the 
variable counts	*/
							
extern char ClockRefresh0;	
extern char ClockRefresh1;
extern char ClockRefresh2;
extern char ClockRefresh3;
extern char ClockTicks;

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	GLCD_Init();													/* Initiate the GLCD screen              */
	BUTTON_init();												/* BUTTON Initialization              */
	init_timer(0,0x17D7840);             	/* Timer initiation with 1 second duration*/
	Potenciometer_init();									/* Potentiometer initiation              */
	
	opening(); //show the title 
	
	complete_menu();//function where all the menu are configurated
	
	SysTick_Config(SystemCoreClock/100);  /*Every 10ms will be an interruption (SCC = 10kHz)*/
	

	
  while (1) {                           /* Loop forever                       */
		/*With this part of the code we display the always the level and the 
		points when the game is running*/
		GLCD_DisplayString(0,19,0,(unsigned char*)"Level: ");
		GLCD_DisplayString(0,26,0,(unsigned char*) levels[lvl]);
	  GLCD_DisplayString(25,20,0,(unsigned char*)"points:");
		GLCD_DisplayString(25,27,0,(unsigned char*)point_char[points]);
		if(ClockTicks){
			ClockTicks=0;
			direction_change();/*Allows the snake to change the 
			dorections*/
		}
		/*With the colition we evaluate if the snake have "eated" a
		piece of "food in the game"*/
		colition();
		/*With the following switch we control de speed of the 
		game depending on the selected level before*/
		switch(lvl){// depending on the level we use diferent ClockRefresh to call the function more frequently or less frequently
			case 0: if(ClockRefresh0){ClockRefresh0=0;movement();}
			case 1: if(ClockRefresh1){ClockRefresh1=0;movement();}
			case 2: if(ClockRefresh2){ClockRefresh2=0;movement();}
			case 3: if(ClockRefresh3){ClockRefresh3=0;movement();}
		}
  }
}

