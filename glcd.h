/*------------------------------------------------------------------------------
glcd.h

use to control QC12864B LCD. The default pin connections are shwon below:

Rs-P2.5  RW-P2.6  En-P2.7  D0~D7-P0  PSB-P2.3  RST-P2.4

These can be changed below.

-------------------------------------------------------------------------------*/

#ifndef __GLCD_H__
#define __GLCD_H__

//define IO port
#define LCDdata P0
sbit RS=P2^5;
sbit RW=P2^6;
sbit En=P2^7;
sbit PSB=P2^3;
sbit RET=P2^4;

//define command
//basic command
#define BasicCommand 0x30 
//1. clear screen
#define ClearScreen	0x01
//2. Addres go back original
#define AddrBackO 0x02
//3. curser setting
#define CurserLeft 0x06
#define CurserRight 0x04
//4. Open/Off curser
#define CurserOn 0x0E
#define CurserOff 0x0C
//5. Let curser move (Only curser will be moved)
#define CurserGoLeft 0x14
#define CurserGoRight 0x10
//External command
#define ExteCommandOff 0x34 //at the same time, display is off
#define ExteCommandOn 0x36 //at the same time, display if on
//1. waiting command
#define WaitingCommand 0x01
//2. in/out sleeping
#define sleeping 0x08
#define weaking 0x0C


//declare functions

//Basic functions
extern void waiting(void);//Read Busy flag and waiting for Busy flag
extern void lcd_write_command(unsigned char command);//write command to LCD
extern void lcd_write_data(unsigned char RWdata);//write data to LCD
extern unsigned char lcd_read_data(void);//read data from LCD
extern void lcd_init(void);//LCD initialization

//string functions
//English and Chinese
extern void display_string(unsigned char line,unsigned char *string);//display string (default string function.)
//Only English


//figure functions
//basic functions
extern void first_page(void);//clear CGRAM
extern void set_dot(unsigned char x,unsigned char y);//draw a pixel
//basic shapes
extern void draw_line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//draw a line
extern void draw_box(unsigned char x,unsigned char y,unsigned char num_x,unsigned char num_y,bit fill);//draw a box
extern void draw_frame(void);//draw the frame
extern void draw_circle(unsigned char x,unsigned char y,unsigned char r,bit fill);//draw circle
//draw picture
//one line picture
extern void draw_8bits(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis
extern void draw_8bits90(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis	but in 90 degree change system
extern void draw_8bits180(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis but in 180 degree change system
extern void draw_8bits270(unsigned char x,unsigned char y,unsigned char data8bit);//draw 8 bit in x axis but in 270 degree change system
//mutiple line s picture
extern void draw_picture(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture
extern void draw_picture90(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture in 90 degree
extern void draw_picture180(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture in 180 degree
extern void draw_picture270(unsigned char x,unsigned char y,unsigned char x_l,unsigned char y_l,unsigned char *picture);//draw a picture in 270 degree


#endif
 