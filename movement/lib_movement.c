#include "lpc17xx.h"
#include <stdlib.h>
#include "../GLCD.h"
#include "../movement/movement.h"
#include "../Joystick/joystick.h"
#include "../menu/menu.h"


/*set the global variables as extern*/

extern int x, y, direction, x1, y1, x2, y2, lvl,index_color_snake,
index_color_game,	colors[]; 
extern uint32_t joys;// variable used for the position of the joystick
extern unsigned char levels[4][10];
extern unsigned char point_char[10][2];
int Xc,Yc;// position variables of the dot that the snake need to eat
int axe;
extern int points;//number of points that the user has gained
int punt=0;
char key;
int PrintChange;
int size=10;// is the size of the snake you can make it bigger if you want!


void Winner(void){/*This function display a menu when the
	user finish the game and collects the maximum number of points*/
	int inside = 1;
	int step_menu = 100;
	char key;
	int selection_line = 15;
	int selection = 1;
	int xpos = 22;
	int restartpos = 15;
	int menupos = 17;
	int exitpos = 19;
	/*Displays all the text in the screen*/
	GLCD_Clear(Green);
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(4,102,1,(unsigned char*)"YOU WON!");
	GLCD_DisplayStringTime(restartpos,xpos,0,(unsigned char*)"Restart", step_menu);
	GLCD_DisplayStringTime(menupos,xpos,0,(unsigned char*)"Menu", step_menu);
	GLCD_DisplayStringTime(exitpos,xpos,0,(unsigned char*)"Exit", step_menu);
	/*The following loop is used to allows to the user to 
	select an element in the menu, and waits until the user select
  one of the possible choices using the joystick	*/
	while(inside == 1){
		delay_ms(95);
		key = joystick();// use the unction joystick to know the value of the joystick
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
		switch (selection){
			case 1: 
				if (key == 'R'){
					GLCD_SetTextColor(Green);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = menupos;
					selection = 2;
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Green);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = exitpos;
					selection = 3;
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					play_game();/* function that starts the game*/
					inside = 0;
					break;
				}
				else{break;}
			case 2: 
				if (key == 'R'){
					GLCD_SetTextColor(Green);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = exitpos;
					selection = 3;
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Green);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = restartpos;
					selection = 1;
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){/*Go back to the menu*/
					complete_menu();
					inside = 0;
					break;
				}
				else{break;}
			case 3: 
				if (key == 'R'){
					GLCD_SetTextColor(Green);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = restartpos;
					selection = 1;
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(Green);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = menupos;
					selection = 2;
					GLCD_SetTextColor(Blue);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					black_screen();/*Turn off the screen*/
					inside = 0;
					break;
				}
				else{break;}
			}
		x=100; 
		y=100;
		direction = 1;
		x1=100;
		y1=100;
		x2=100;
		y2=100;
		points = 0;
	}
}
void print_point(void){/*print the point that the snake will eat*/
	Yc=rand()%230; //we use a random function to set the position of the point
	Xc=rand()%310;
	GLCD_SetBar(Xc,Yc ,5,5,1024); //punto de adelante
	
}

void colition(void){/*With the following function detects 
	always the position of the snake and the position of the 
	food, and if are the same position, the points are updated,
	and prints a new food in a random position*/
	if (((Yc<=(y+(size/2))) & (Yc>=(y-(size/2)))) &((Xc<=(x+(size/2))) & (Xc>=(x-(size/2))))){// with this condition we established the limit for the colition
		if (points<10){//number of colition the snake has to make before winning
		print_point();
		points+=1;
		}
		else{
					Winner();/*Calls the function where the game ends*/
		}
	}
}	

void findeljuego(void){/*With the following function
	when the snake crashed the game over is displayed and allows
	to choose different options with the game*/
	int inside = 1;
	int step_menu = 100;
	char key;
	int selection_line = 15;
	int selection = 1;
	int xpos = 22;
	int restartpos = 15;
	int menupos = 17;
	int exitpos = 19;
	/*define the end of game screen*/
	points=0;
	while(punt<5000){ // print 5000 points when the user fails. We used this for some kind of cool effect. Is cool right?
		print_point();
		punt+=1;
	}
	punt = 0; //reset the punt value before restarting
	/*Display all the text in the screen*/
	//GLCD_Clear(Maroon);
	GLCD_SetBackColor(colors[index_color_snake]);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(4,102,1,(unsigned char*)"Game Over");
	
	GLCD_DisplayStringTime(restartpos,xpos,0,(unsigned char*)"Restart", step_menu);
	GLCD_DisplayStringTime(menupos,xpos,0,(unsigned char*)"Menu", step_menu);
	GLCD_DisplayStringTime(exitpos,xpos,0,(unsigned char*)"Exit", step_menu);
	/*With the following code we control the menu, and always wait 
	to the user selection after the crash of the snake*/
	while(inside == 1){
		delay_ms(95);
		key = joystick();
		GLCD_SetTextColor(White);
		GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
		/*With the switch we control the position of the selector and
		always, when the position is changed erase the last selector
		and prints the selector in the new position*/
		switch (selection){
			case 1: 
				if (key == 'R'){
					GLCD_SetTextColor(colors[index_color_snake]);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = menupos;
					selection = 2;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(colors[index_color_snake]);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = exitpos;
					selection = 3;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					play_game();/*Call the function to play*/
					inside = 0;
					break;
				}
				else{break;}
			case 2: 
				if (key == 'R'){
					GLCD_SetTextColor(colors[index_color_snake]);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = exitpos;
					selection = 3;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(colors[index_color_snake]);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = restartpos;
					selection = 1;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					complete_menu();/*Call the function for the menu*/
					inside = 0;
					break;
				}
				else{break;}
			case 3: 
				if (key == 'R'){
					GLCD_SetTextColor(colors[index_color_snake]);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = restartpos;
					selection = 1;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'L'){
					GLCD_SetTextColor(colors[index_color_snake]);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					selection_line = menupos;
					selection = 2;
					GLCD_SetTextColor(White);
					GLCD_DisplayString(selection_line,xpos-3,0,(unsigned char*)"->");
					break;
				}
				if (key== 'S'){
					black_screen();/*This function turn off the screen*/
					inside = 0;
					break;
				}
				else{break;}
			}
		x=100; 
		y=100;
		direction = 1;
		x1=100;
		y1=100;
		x2=100;
		y2=100;
	}
}

void black_screen(){/*This function "turn off" the screen*/
	GLCD_Clear(Black);
	while(1);
}

void print(){	//Function to print the squares of the snake
		
		GLCD_SetBar(x,y ,size,size,1024); //First square
		GLCD_SetBar(x1,y1,size,size,1024);  //Middle square

}
void erase(int axe){   //erase the snake on the corresponding axe 0 for x and 1 for y

	if(axe==0){
					GLCD_SetClr(x2,y,size,size,1024);
					GLCD_SetClr(x1,y,size,size,1024);
					x2=x;
					x1=x;
	}
	else{
					GLCD_SetClr(x,y2,size,size,1024);
					GLCD_SetClr(x,y1,size,size,1024);
					y2=y;
					y1=y;
	}
}
void Direction_change_print(int PrintChange){//depending on the direction there is diferent behavior of the snake this function control that part
	switch(PrintChange){
		case 11:
			x2=x1;
			x1=x;
			x+=size;
			print();
			break;
		case 12:
			x2=x1;
			x1=x;
			x-=size;
			print();
			break;
		case 21:
			y2=y1;   //the position is moved
			y1=y;
			y-=size;  //y is increised by the size of the square
			print();
			break;
		case 22:
			y2=y1;   //the position is moved
			y1=y;
			y+=size;  //y is increised by the size of the square
			print();
			break;
		case 31:
			x2=x1;
			x1=x;
			x+=size;
			print();
		  break;
		case 32:
			x2=x1;
			x1=x;
			x-=size;
			print();
			break;
		case 41:
			y2=y1;   //the position is moved
			y1=y;
			y+=size;  //y is increised by the size of the square
			print();
			break;
		case 42:
			y2=y1;   //the position is moved
			y1=y;
			y-=size;  //y is increised by the size of the square
			print();
			break;
			
			
	}
}
void delay_ms(unsigned int ms){/*Counter created to insert a 
	delay when the we are writing the letters of the strings*/
   unsigned int i,j;

   for(i=0;i<ms;i++)
     for(j=0;j<20000;j++);

}

void direction_change(void){/*With the following function we check 
	in which direction the joystick was pressed and this change the 
	direction in which the snakes moves. In particular, this function
	erase the last part of the snake and prints the new part ahead of the 
	snake.*/
		key = joystick();
		switch(direction){
			case 1:
				if (key == 'U'){//left
					direction = 2;     //when the joystick is presed the direction changes
					erase(1); /*Erase the last part of the snake*/
					Direction_change_print(11);
					break;
				}
				if (key == 'D'){ //right
					direction = 4;
					erase(1);
					Direction_change_print(12);
					break;
				}
				else{break;}
				
				/*The procedure described in the upper part is repeated in 
				all the following cases*/
				
			case 2:
				if (key == 'L'){
					direction = 3;
					erase(0);
					Direction_change_print(21);
					break;
				}
				if (key == 'R'){
					direction = 1;
					erase(0);
					Direction_change_print(22);
					break;
				}
				else{break;}
			case 3:
				if (key == 'U'){
					direction = 2;
					erase(1);
					Direction_change_print(31);
					break;
				}
				if (key == 'D'){
					direction = 4;
					erase(1);
					Direction_change_print(32);
					break;
				}
				else{break;}
			case 4:
				if (key == 'R'){
					direction = 1;
					erase(0);
					Direction_change_print(41);
					break;
				}
				if (key == 'L'){
					direction = 3;
					erase(0);
					Direction_change_print(42);
					break;
				}
				else{break;}
			}
}

void movement(){/*this function controls the erasing and the limits of the display.*/
		/*print at the top of the screen the level*/
	  print();
		switch(direction){
			case 1:	
					if ( y>= 230){  //when the snake arrives to the limit of the screen the function findeljuego()is called
						findeljuego();
						break;
					}
					else{
						GLCD_SetClr(x,y2,size,size,1024); //we eliminate the last square while there is no change in direction
						y2=y1;   //the position is moved
						y1=y;
						y+=7;  //y is increised by the size of the square
					}						
				break;
		
			case 2:
					if ( x>= 310){
						findeljuego();
					}
					else{
						GLCD_SetClr(x2,y,size,size,1024);
						x2=x1;
						x1=x;
						x+=7;
					}						
				break;
			case 3:
					if ( y<=5 ){
						findeljuego();
					}
					else{
						GLCD_SetClr(x,y2,size,size,1024);
						y2=y1;
						y1=y;
						y-=7;	
					}						
				break;
			case 4:
					if ( x<= 0){
						findeljuego();
					}
					else{
						GLCD_SetClr(x2,y,size,size,1024);
						x2=x1;
						x1=x;
						x-=7;
					}						
				break;
			}
}

