#include <reg52.h>
#include "glcd.h"

unsigned char testunit=0;
unsigned char frame=0;
unsigned char code title[]={" QC12864B Test"};
unsigned char code author[]={"  by pikipity"};
unsigned char code string_line[]={"Line Testing"};
unsigned char code string_box[]={"Box Testing"};
unsigned char code string_circle[]={"Circle Testing"};
unsigned char code string_font1[]={"Font Testing"};
unsigned char code test_string_l[]={"ABCDEFGHIJKLMNOPQRSTU"};
unsigned char code test_string_l_2[]={"VWXYZ"};
unsigned char code test_string_s[]={"abcdefghijklmnopqrstu"};
unsigned char code test_string_s_2[]={"vwxyz"};
unsigned char code test_string[]={"ABCD"};
unsigned char code finish[]={"     Finish"};

void draw(){
	if(testunit==0){
		display_string(2,title);
		display_string(3,author);
	}else if(testunit==1){
		display_string(1,string_line);
		draw_line(20+frame*4,20,40+frame*4,40);
		draw_line(40+frame*4,20,20+frame*4,40);
		draw_line(30+frame*4,20,30+frame*4,40);
		draw_line(20+frame*4,30,40+frame*4,30);
	}else if(testunit==2){
		display_string(1,string_box);
		draw_box(20,20,20,20,0);
		draw_box(30+frame*4,30,20,20,1);
	}else if(testunit==3){
		display_string(1,string_circle);
		draw_circle(30,30,10,0);
		draw_circle(40+frame*4,40,10,1);
	}else if(testunit==4){
		display_string(1,string_font1);
		display_string_58(0,15,test_string_l,0,1);
		display_string_58(0,24,test_string_l_2,0,1);
		display_string_58(0,33,test_string_s,0,1);
		display_string_58(0,42,test_string_s_2,0,1);
	}else if(testunit==5){
		display_string(1,string_font1);
		display_string_58(20+frame*2,20,test_string,90,1);
	}else if(testunit==6){
		display_string(1,string_font1);
		display_string_58(40+frame*2,30,test_string,180,1);
	}else if(testunit==7){
		display_string(1,string_font1);
		display_string_58(20+frame*2,40,test_string,270,1);
	}else if(testunit==8){
		display_string(2,finish);
	}
	if(frame==15){
		frame=0;
		if(testunit==8){
			;
		}else{
			testunit++;
		}
	}else{
		frame++;
	}
	delayms(100);
}

void main(){
	lcd_init();
	while(1){
		first_page();
		draw();
	}
}