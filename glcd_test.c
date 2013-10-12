#include <reg52.h>
#include "glcd.h"

void draw(){
	draw_frame();
}

void main(){
	lcd_init();
	first_page();
	draw();
	while(1);
}