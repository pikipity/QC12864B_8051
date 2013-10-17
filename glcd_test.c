#include <reg52.h>
#include "glcd.h"

unsigned char code string_1[]={"Test"};

void draw(){
	display_string_58(20,20,string_1,270);
}

void main(){
	lcd_init();
	first_page();
	draw();
	while(1);
}