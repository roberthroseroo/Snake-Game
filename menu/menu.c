#include <stdio.h>
#include <stdlib.h>
#include "lpc17xx.h"
#include "../GLCD.h"
#include "../button_EXINT/button.h"
#include "../Joystick/joystick.h"
#include "../movement/movement.h"

/*This file contains all the functions used to 
control the game, this are, all the menus that can 
be displayed in the game*/

extern int pass_instructions;
extern int lvl,index_color_game, index_color_snake, colors[];
extern char levels[4][10];
extern int points;
//extern unsigned char* points;
void delay_ms(unsigned int ms);
unsigned char time[3][1]={'1','2','3'};// string containing the countdown numbers
int cntr;
void configuration(void);
void press_select(void);
void play_game(void);
void complete_menu(void);
void opening(void);



void introduction(){/*With this function, the credits are 
	displayed showing the names, year and all related 
	with the game develop*/
	int step_introduction = 100,
			inside = 1,
			selection = 1,
			backpos = 24,
			selection_line = backpos,
			xpos = 24,
			xposarrow = xpos-3;
	
	char key;
	
	GLCD_Clear(Navy);
	GLCD_SetBackColor(Navy);
	GLCD_SetTextColor(White);
	GLCD_DisplayStringTime(1,3,1,(unsigned char*)("The Snake Game"),step_introduction);
	GLCD_DisplayStringTime(10,15,0,(unsigned char*)("Computer Architectures"),step_introduction);
	GLCD_DisplayStringTime(13,19,0,(unsigned char*)("Special Project"),step_introduction);
	GLCD_DisplayStringTime(16,13,0,(unsigned char*)("Carlos Pena, Roberth Rosero"),step_introduction);
	GLCD_DisplayStringTime(19,15,0,(unsigned char*)"Politecnico di Torino",step_introduction);
	GLCD_DisplayStringTime(20,19,0,(unsigned char*)"Torino, Italy",step_introduction);
	GLCD_DisplayStringTime(21,23,0,(unsigned char*)"2018",step_introduction);
	GLCD_DisplayStringTime(backpos,xpos,0,(unsigned char*)"Back",step_introduction);
	GLCD_DisplayString(backpos,xposarrow,0,(unsigned char*)"->");
	
	while (inside == 1){
		delay_ms(95);
		key = joystick();
		GLCD_SetTextColor(White);
		GLCD_DisplayString(selection_line,xposarrow,0,(unsigned char*)"->");
		switch (selection){
			case 1: 
				if (key == 'R'){
					GLCD_SetTextColor(Navy);
					GLCD_DisplayString(selection_line,xposarrow,0,(unsigned char*)"->");
					selection_line = backpos;
					selection = 1;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xposarrow,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Navy);
					GLCD_DisplayString(selection_line,xposarrow,0,(unsigned char*)"->");
					selection_line = backpos;
					selection = 1;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xposarrow,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					//Función para jugar
					complete_menu();
					inside = 0;
					break;
				}
				else{break;}
			}
		}
}


void instructions(){/*With this function, the basic instructions
	are displayed in the screen, we have a little selection that 
	allow us to select if the game starts or to go back to the main 
	menu*/
	int step_instructions = 100,
			inside = 1,
			selection = 1,
			playpos = 19,
			backpos = playpos + 3,
			xpos = 16,
			selection_line = playpos;
	
	char key;
	/*Display all the data in the screen*/
	GLCD_Clear(Blue);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayStringTime(0,4,1,(unsigned char*)"Instructions",step_instructions);
	GLCD_DisplayString(4,0,0,(unsigned char*)"1. Use the joystick to move the snake and avoid crash");
	GLCD_DisplayString(5,3,0,(unsigned char*)"against the wall.");
	GLCD_DisplayString(7,0,0,(unsigned char*)"2. The game have 4 difficulty levels:");
	GLCD_DisplayString(9,4,0,(unsigned char*)"Level 1: Dummie");
	GLCD_DisplayString(10,4,0,(unsigned char*)"Level 2: Beginner");
	GLCD_DisplayString(11,4,0,(unsigned char*)"Level 3: Expert");
	GLCD_DisplayString(12,4,0,(unsigned char*)"Level 4: CA's");
	GLCD_DisplayString(14,3,0,(unsigned char*)"You can control the difficulty with the pontentio-");
	GLCD_DisplayString(15,3,0,(unsigned char*)"meter, moving to the right you increase it and mo-");
	GLCD_DisplayString(16,3,0,(unsigned char*)"ving to the left, you decrease it.");
	
	GLCD_DisplayString(playpos,xpos,0,(unsigned char*)"Play");
	GLCD_DisplayString(backpos,xpos,0,(unsigned char*)"Back");
	/*In this part, wait for the user's selection, play or back*/
	while (inside == 1){
		delay_ms(95);
		key= joystick();
		GLCD_SetTextColor(White);
		GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
		switch (selection){
			case 1: 
				if (key == 'R'){
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = backpos;
					selection = 2;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = backpos;
					selection = 2;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					play_game();/*Starts the game*/
					inside = 0;
					break;
				}
				else{break;}
			case 2:			
				if (key == 'R'){
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = playpos;
					selection = 1;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key == 'L'){
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = playpos;
					selection = 1;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key == 'S'){
					complete_menu();/*Go to the main menu*/
					inside = 0;
					break;
				}
				else{break;}
			}
		}
	}

void play_game(){/*With this function we display 
	a down counter and starts the game*/
	GLCD_Clear(colors[index_color_game]);
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(colors[index_color_game]);
	for(cntr = 2;cntr >= 0;cntr=cntr-1){
		GLCD_DisplayString(4,6,1,time[cntr]);
		delay_ms(1000);
	}
	GLCD_Clear(colors[index_color_game]);
	print_point();/*Principal function that begins the game.
	In this function are all the functions used to print the snake,
	the background, etc.*/
}

void complete_menu(){/*In this function we can find the main menu where the selection is displayed 
	in this function we use the joystick to control the selection and depending on the position and the
	selection we will be moved to another menu.*/
	int selection = 1;
	int inside = 1;
	int step_menu = 50;
	char key;
	int selection_line = 12;
	//Display all the selections
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayStringTime(1,7,1,(unsigned char*)"Menu", step_menu);
	GLCD_DisplayStringTime(12,16,0,(unsigned char*)"Play", step_menu);
	GLCD_DisplayStringTime(15,16,0,(unsigned char*)"Instructions", step_menu);
	GLCD_DisplayStringTime(18,16,0,(unsigned char*)"Configuration", step_menu);
	GLCD_DisplayStringTime(21,16,0,(unsigned char*)"Credits", step_menu);
	GLCD_SetTextColor(Red);
	//with this part we control the selection and move to another menu
	while (inside == 1){
		delay_ms(95);
		key= joystick();
		GLCD_SetTextColor(Red);
		GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
		/*With the switch we will know in which position of the menu we are
		In each case we have to print the value in the color and in the background color
		to delete the last position where the selection icon was*/
		switch (selection){
			case 1: 
				if (key == 'R'){
				/*First we erase the last selection icon printing it with the background color*/
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					/*And after we erase the last value, we update the position and
					print in the new position. This procedure is repeated in all of the
					selection cases*/
					selection_line = 15;
					selection = 2;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 21;
					selection = 4;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					play_game();//call the functions that starts the game 
					inside = 0;
					break;
				}
				else{break;}
			case 2:			
				if (key == 'R'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 18;
					selection = 3;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key == 'L'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 12;
					selection = 1;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key == 'S'){
					/*Call the function that displays the instructions in the screen*/
					instructions();
					inside = 0;
					break;
				}
				else{
				break;}
			case 3:
				if (key== 'R'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 21;
					selection = 4;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 15;
					selection = 2;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					//Call the function to configurate the different characteristics
					configuration();
					inside = 0;
					break;
				}
				else{break;}
			case 4:
				if (key== 'R'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 12;
					selection = 1;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Black);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					selection_line = 18;
					selection = 3;
					GLCD_SetTextColor(Red);
					GLCD_DisplayString(selection_line,13,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					//Call the function that displays the credits
					introduction();
					inside = 0;
					break;
				}
				else{
				break;}
			}
		}//End of the switch
	}

void configuration(){/*With this function we open the configuration window, in this one we can
	change the different parameteres for the game, using the joystick and the potentiometer*/
int step_configuration = 100,
		inside = 1,
		selection = 1;
int gamecolorpos = 17, snakecolorpos = gamecolorpos + 3, difpos = snakecolorpos + 3, xpos = 8,
	backpos = difpos + 3,
		selection_line = gamecolorpos;
char key;

/*First we display all the content on the screen*/

GLCD_Clear(Cyan);
GLCD_SetBackColor(Cyan);
GLCD_SetTextColor(Black);
GLCD_DisplayStringTime(1,3,1,(unsigned char*)"Configuration",step_configuration);
GLCD_DisplayString(8,2,0,(unsigned char*)"Use the joystick in the Up Down directions to");
GLCD_DisplayString(9,2,0,(unsigned char*)"select the configuration and use the <- ->");
GLCD_DisplayString(10,2,0,(unsigned char*)"directions to change the parameters of the");
GLCD_DisplayString(11,2,0,(unsigned char*)"configuration.");
GLCD_DisplayString(13,2,0,(unsigned char*)"For the Difficulty use the potentiometer to select");
GLCD_DisplayString(14,2,0,(unsigned char*)"it");
GLCD_DisplayString(gamecolorpos,xpos,0,(unsigned char*)"Game background color");
GLCD_DisplayString(snakecolorpos,xpos,0,(unsigned char*)"Snake color");
GLCD_DisplayString(difpos,xpos,0,(unsigned char*)"Difficulty");
GLCD_DisplayString(backpos,xpos,0,(unsigned char*)"Back");

/*The folloing loop controls the menu and allows the movement of the selection
icon trought the different parameters*/

while(inside == 1){
	
	delay_ms(95);

	key = joystick();
	/*To print the blocks with the color of the background and the snake we use
	a little block that changes when we select the color*/
	GLCD_SetBackColor(colors[index_color_game]);
	GLCD_SetTextColor(colors[index_color_game]);
	GLCD_DisplayString(gamecolorpos,xpos+30,0,(unsigned char*)". . .");
	
	GLCD_SetBackColor(colors[index_color_snake]);
	GLCD_SetTextColor(colors[index_color_snake]);
	GLCD_DisplayString(snakecolorpos,xpos+30,0,(unsigned char*)". . .");
	
	GLCD_SetBackColor(Cyan);
	
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
	
	GLCD_DisplayString(difpos,xpos+28,0,(unsigned char*)levels[lvl]);
	/*With this function we navigate in the menu and select the 
	parameters to configure*/
	switch (selection){
		case 1: 
			if (key == 'R'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = snakecolorpos;
				selection = 2;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'L'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = backpos;
				selection = 4;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'S'){
				press_select();
				inside = 0;
				break;
			}
			if (key == 'U'){/*When we are in the color configuration, with the 
				joystick we navigate to the right and to the left to change the colors, 
				with this functions we change this value and print it*/
				index_color_game = index_color_game + 1;
				if(index_color_game > 15){
					index_color_game = 0;
				}
				break;
			}
			if (key == 'D'){
				index_color_game = index_color_game - 1;
				if(index_color_game < 0){
					index_color_game = 15;
				}
				break;
			}
			else{break;}
		case 2: 
			if (key == 'R'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = difpos;
				selection = 3;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'L'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = gamecolorpos;
				selection = 1;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'S'){
				press_select();
				inside = 0;
				break;
			}
			if (key == 'U'){
				index_color_snake = index_color_snake + 1;
				if(index_color_snake > 15){
					index_color_snake = 0;
				}
				break;
			}
			if (key == 'D'){
				index_color_snake = index_color_snake - 1;
				if(index_color_snake < 0){
					index_color_snake = 15;
				}
				break;
			}
			else{break;}
	case 3: 
			if (key == 'R'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = backpos;
				selection = 4;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'L'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = snakecolorpos;
				selection = 2;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'S'){
				press_select();
				inside = 0;
				break;
			}
			else{break;}
		case 4:
			if (key == 'R'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = gamecolorpos;
				selection = 1;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'L'){
				GLCD_SetTextColor(Cyan);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				selection_line = difpos;
				selection = 3;
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
				break;
			}
			if (key== 'S'){
				//Función para jugar
				complete_menu();
				inside = 0;
				break;
			}
			else{break;}
		}
	
	
	}
}
	
void opening(){/*This function displays the first screen and 
	shows the name of the game*/
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(4,3,1,(unsigned char*)"The Snake Game");
	delay_ms(1000);
}

void press_select(){/*When you press a selection in the wrong part
	this functions shows that you press and invalid selection*/
	GLCD_Clear(Red);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(4,4,1,(unsigned char*)"WHY SELECT?!");
	delay_ms(300);
	configuration();
}
