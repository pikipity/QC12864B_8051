#include <reg52.h>
#include <string.h>
#include "glcd.h"

void waiting(void){
	while(1){
		RS=0;
		RW=1;
		En=0;
		LCDdata=0xFF;
		En=1;
		if((LCDdata&0x80)==0) break;
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

unsigned char lcd_read_data(void){
	unsigned char Rdata;
	waiting();
	RS=1;
	RW=1;
	En=1;
	Rdata=P0;
	En=0;
	return Rdata;
}

void lcd_init(void){
	PSB=1;
	RET=1;
	lcd_write_command(BasicCommand);
	lcd_write_command(ClearScreen);
	lcd_write_command(AddrBackO);
	lcd_write_command(CurserOff);
	lcd_write_command(ClearScreen);
	lcd_write_command(CurserLeft);
}

void display_string(unsigned char line,unsigned char *string){
//Use the default command to display string. It can display chinese
//line is the number of line. There are total 4 lines
//string must be like this: unsigned char code string_1[]={"Test"}
//Maxmum number of characters is 16.
    unsigned char  addr,i;
	unsigned char  maxnum=strlen(string);
    if(line==1)
      addr=0x80;
    else if(line==2)
      addr=0x90;
    else if(line==3)
      addr=0x88;
    else if(line==4)
		addr=0x98;
    lcd_write_command(addr);
    for(i=0;i<maxnum;i++)
    {
		lcd_write_data(*string++);
	} 
}

void first_page(void){
	unsigned char i,j;
	lcd_write_command(ExteCommandOff);
	for(i=0;i<16;i++){
		for(j=0;j<32;j++){
			lcd_write_command(0x80|j);
			lcd_write_command(i|0x80);
			lcd_write_data(0x00);
			lcd_write_data(0x00);	
		}
	}
	lcd_write_command(ExteCommandOn);
	lcd_write_command(BasicCommand);
}

void set_dot(unsigned char x,unsigned char y){
	unsigned int k=0x8000;
	unsigned char m,n;
	lcd_write_command(ExteCommandOn);
	if(y>32){
		y=y-32;
		x=x+128;
	}
	k=k>>x%16;
	lcd_write_command((x/16)|0x80);
	lcd_write_command(0x80|y);
	m=lcd_read_data();
	m=lcd_read_data()|k>>8;
	n=lcd_read_data()|k;
	lcd_write_command(0x80|y);
	lcd_write_command((x/16)|0x80);
	lcd_write_data(m);
	lcd_write_data(n);
	lcd_write_command(BasicCommand);
}

void drawline(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2){
	
}