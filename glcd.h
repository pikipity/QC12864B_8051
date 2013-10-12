/*------------------------------------------------------------------------------
glcd.h

use to control QC12864B LCD. The default pin connections are shwon below:

Rs-P2.5  RW-P2.6  En-P2.7  D0~D7-P0  PSB-P2.3  RST-P2.4

These can be changed below.

-------------------------------------------------------------------------------*/

#ifndef GLCD_H
#define GLCD_H

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
void waiting(void);//Read Busy flag and waiting for Busy flag
void lcd_write_command(unsigned char command);//write command to LCD
void lcd_write_data(unsigned char RWdata);//write data to LCD
unsigned char lcd_read_data(void);//read data from LCD
void lcd_init(void);//LCD initialization
//string functions
void display_string(unsigned char line,unsigned char *string);//display string (default string function)
//figure functions
void first_page(void);//clear CGRAM
void set_dot(unsigned char x,unsigned char y);//draw a pixel
void drawline(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//draw a line


#endif
 