#include <reg52.h>
#include "glcd.h"

void draw(){
	draw_line(0,0,127,63);
	set_dot(0,32);
}

void main(){
	lcd_init();
	first_page();
	draw();
	while(1);
}