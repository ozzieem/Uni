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
 
extern void lcd4_init(lcd4 *this, volatile unsigned char *port, volatile unsigned char *ddr, int del, int delE);
extern void lcd4_command(lcd4 *this, char c);
extern void lcd4_write_char(lcd4 *this, char c);
extern void lcd4_write_string(lcd4 *this, char *s);  
extern void lcd4_cup_row1(lcd4 *this);
extern void lcd4_cup_row2(lcd4 *this);
extern void lcd4_erase(lcd4 *this);
 
#define CmdClearLCD        0x01  
#define CmdCursorHomeLCD   0x02  
#define CmdCUP             0x80

#endif


