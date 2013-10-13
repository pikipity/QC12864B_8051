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
	if(x>=0 && x<=127 && y>=0 && y<=63){
	//initial variables
	unsigned int k=0x8000;
	unsigned char highdata,lowdata;
	//Open external command and graphic display
	lcd_write_command(ExteCommandOn);
	//According to y, adjust x and y
	if(y>=32){
		y=y-32;
		x=x+128;
	}
	//according to x, get which bit will be setted.
	k=k>>x%16;
	//write x and y to prepare to read data
	lcd_write_command(0x80|y);
	lcd_write_command((x/16)|0x80);
	//read exist data and change them to new data.
	highdata=lcd_read_data();
	highdata=lcd_read_data()|k>>8;
	lowdata=lcd_read_data()|k;
	//write x and y	to prepare to write data
	lcd_write_command(0x80|y);
	lcd_write_command((x/16)|0x80);
	//write data
	lcd_write_data(highdata);
	lcd_write_data(lowdata);
	//go back to basic command
	lcd_write_command(BasicCommand);
	}
}

void draw_line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2){	
	char dx,dy;//Difference between x1 and x2 and difference between y1 and y2
	unsigned char x,y,temp;//x,y: location of pixel.  temp: temp value for exchange of x and y
	int e;//adjust whether should be increased
	bit k,j;//k: upper slope flag.  j: negative slope flag
	dx=x2-x1;
	dy=y2-y1;
	//if the line is not from high to low, change it.
	if((dx<=0 && dy<=0) || (dx>=0 && dy<=0)){
		temp=x2;
		x2=x1;
		x1=temp;
		temp=y2;
		y2=y1;
		y1=temp;
		dx=x2-x1;
		dy=y2-y1;
	}
	//if negative slope, change to positive and get flag
	if(dx<0){
		temp=x2;
		x2=x1;
		x1=temp;
		dx=x2-x1;
		j=1;
	}else{
		j=0;
	}
	//if upper slope, get flag
	if(dx>=dy){
		k=1;	
	}else{
		k=0;
	}
	//Different slope, different default e
	if(k){
		e=-dx;
	}else{
		e=-dy;
	}
	//first point
	x=x1;
	y=y1;
	//if has been finished final point, finish drawing.
	while(x<=x2 && y<=y2){
		//if the original slope is negative slope, should  change points back
		if(j){
			set_dot(x1+x2-x,y);
		}else{
			set_dot(x,y);
		}
		//different slope, different change of e
		if(k){
			e=e+2*dy;
		}else{
			e=e+2*dx;
		}
		//according to e, adjust whether should go upper
		if(e<=0){
			//different slope, different way to go upper
			if(k){
				x++;
			}else{
				y++;
			}
		}else{
			x++;
			y++;
			//different slope, different change of e
			if(k){
				e=e-2*dx;
			}else{
				e=e-2*dy;
			}
		}
	}
}

void draw_box(unsigned char x,unsigned char y,unsigned char num_x,unsigned char num_y,bit fill){
	//x: right upper coner x
	//y: right upper coner y
	//num_x: number of pixels in x
	//num_y: number os pixels in y
	//fill: fill or not
	if(fill){
		unsigned char i;
		for(i=y;i<y+num_y;i++){
			draw_line(x,i,x+num_x-1,i);
		}
	}else{
		draw_line(x,y,x,y+num_y-1);
		draw_line(x,y,x+num_x-1,y);
		draw_line(x+num_x-1,y+num_y-1,x+num_x-1,y);
		draw_line(x+num_x-1,y+num_y-1,x,y+num_y-1);
	}
}

void draw_frame(void){
	draw_box(0,0,128,64,0);
}

void draw_circle(unsigned char x,unsigned char y,unsigned char r,bit fill){
	//x: x of center
	//y: y of center
	//r: radius (number of pixels in radius)
	//fill: fill or not
	unsigned char a,b;
	char d;
	unsigned char i;
	//initial first point
	a=0;
	b=r-1;
	//initial distance
	d=1-r;
	while(a<=b){//Adjust if circle has been finished
		//draw circle using a point of 1/8 circle to draw 8 points in all circle
		if(fill){
			for(i=a+x;i>=x-a;i--){
				set_dot(i,b+y);
				set_dot(i,y-b);
			}
			for(i=b+x;i>=x-b;i--){
				set_dot(i,a+y);
				set_dot(i,y-a);
			}
		}else{
			set_dot(a+x,b+y);
			set_dot(a+x,y-b);
			set_dot(x-a,b+y);
			set_dot(x-a,y-b);
			set_dot(b+x,a+y);
			set_dot(b+x,y-a);
			set_dot(x-b,a+y);
			set_dot(x-b,y-a);	
		}
		//use distance to adjust next point.
		if(d<0){
			d+=2*a+3;
		}else{
			d+=2*(a-b)+5;
			b--;
		}
		a++;
	}
}