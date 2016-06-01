#ifndef _LCD4_H
#define _LCD4_H

#include <avr/io.h>
#include "io_bit_fields.h"

typedef struct
{
  volatile unsigned char *port;
  volatile unsigned char *ddr;

  int del;
  int delE;
} lcd4;
 
void lcd4_init(lcd4 *obj, volatile unsigned char *port, volatile unsigned char *ddr, int del, int delE);
void lcd4_command(lcd4 *obj, char c);
void lcd4_write_char(lcd4 *obj, char c);
void lcd4_write_string(lcd4 *obj, char *s);  
void lcd4_cup_row1(lcd4 *obj);
void lcd4_cup_row2(lcd4 *obj);
void lcd4_erase(lcd4 *obj);
 
#define CmdClearLCD        0x01  
#define CmdCursorHomeLCD   0x02  
#define CmdCUP             0x80

#endif


