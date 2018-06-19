#include "lpc17xx.h"

/*With this library a character is obtained when
a joystick key is pressed*/
uint32_t joys;
char pressed;

char joystick(){

	joys = LPC_GPIO1->FIOPIN;
	
	if ((joys & (1<<25))==0){//select
		pressed = 'S';
	}
		
	else if ((joys & (1<<26))==0){//down
		pressed = 'D';
	}
		
	else if ((joys & (1<<27))==0){//Left
		pressed = 'L';
	}
		
	else if ((joys & (1<<28))==0){//riight
		pressed = 'R';
	}
		
	else if ((joys & (1<<29))==0){//under
		pressed = 'U';
	}
	else{pressed='N';}//no pressed
	return pressed;
}
