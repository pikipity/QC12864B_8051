#include <reg52.h>
#include "glcd.h"

unsigned char code string_1[]={"ABCD EFGH abcd efgh !@#$%^&*()_+-"};

void draw(){
	display_string_58(0,0,string_1);
}

void main(){
	lcd_init();
	first_page();
	draw();
	while(1);
}