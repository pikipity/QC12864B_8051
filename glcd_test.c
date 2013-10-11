#include <reg52.h>
#include "glcd.h"

unsigned char code string_1[]={"Test! Now  "};

void main(){
	lcd_init();
	Display_String(4,string_1);
	while(1);
}