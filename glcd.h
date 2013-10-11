/*------------------------------------------------------------------------------
glcd.h

use to control QC12864B LCD. The default pin connections are shwon below:

Rs-P2.5  RW-P2.6  En-P2.7  D0~D7-P0  PSB-P2.3  RST-P2.4

These can be changed below.

-------------------------------------------------------------------------------*/

#ifndef GLCD_H
#define GLCD_H

#define LCDdata P0
#define busy 0x80

sbit RS=P2^5;
sbit RW=P2^6;
sbit En=P2^7;
sbit PSB=P2^3;
sbit RET=P2^4;

void waiting(void);
void lcd_write_command(unsigned char command);
void lcd_write_data(unsigned char RWdata);
void lcd_init(void);
//void delay5ms(void);
void Display_String(unsigned char line,unsigned char *string);


#endif
 