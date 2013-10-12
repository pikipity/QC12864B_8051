#include <reg52.h>
#include "glcd.h"

void draw(){
	draw_line(127,63,0,0);
	draw_line(0,63,0,0);
	draw_line(0,0,127,0);
	draw_line(0,63,127,63);
	draw_line(127,63,127,0);
	draw_line(127,0,0,63);
}

void main(){
	lcd_init();
	first_page();
	draw();
	while(1);
}