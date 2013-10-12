#include <reg52.h>
#include "glcd.h"

unsigned char code string_1[]={"Test! Now"};

void draw(){
	display_string(1,string_1);
	set_dot(100,60);
}

void main(){
	lcd_init();
	first_page();
	while(1){
		draw();	
	}
}