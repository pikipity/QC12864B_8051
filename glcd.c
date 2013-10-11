#include <reg52.h>
#include "glcd.h"

void waiting(void){
	while(1){
		RS=0;
		RW=1;
		En=0;
		LCDdata=0xFF;
		En=1;
		if((LCDdata&busy)==0) break;
	}
}

void lcd_write_command(unsigned char command){
	waiting();
	RS=0;
	RW=0;
	En=1;
	LCDdata=command;
	En=0;
}

void lcd_write_data(unsigned char RWdata){
	waiting();
	RS=1;
	RW=0;
	En=1;
	LCDdata=RWdata;
	En=0;
}

void lcd_init(void){
	RET=1;
	lcd_write_command(0x30);
	lcd_write_command(0x30);
	lcd_write_command(0x0C);
	lcd_write_command(0x01);
	lcd_write_command(0x06);
}

void Display_String(unsigned char line,unsigned char *string){
//Use the default command to display string. It can display chinese
//line is the number of line. There are total 4 lines
//string must be like this: unsigned char code string_1[]={"Test"}
    unsigned char addr,i;
    if(line==1)
      addr=0x80;
    else if(line==2)
      addr=0x90;
    else if(line==3)
      addr=0x88;
    else if(line==4)
		addr=0x98;
    lcd_write_command(addr);
    for(i=0;i<16;i++)
    {
		lcd_write_data(*string++);
	} 
}