#include <reg52.h>
#include "glcd.h"

void draw(){
	draw_circle(128/2-1,64/2-1,31,1);
}

void main(){
	lcd_init();
	first_page();
	draw();
	while(1);
}