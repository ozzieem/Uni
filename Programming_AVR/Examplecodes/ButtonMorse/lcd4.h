#ifndef _LCD4_H
#define _LCD4_H

#include <avr/io.h>
#include "io_bit_fields.h"

class lcd4
{
	private:
		enum Symbol
		{
			CmdClearLCD      =0x01,
			CmdCursorHomeLCD =0x02,
			CmdCUP           =0x80,
			MASK_E           =0x10,
			MASK_RS          =0x20,
		};

	private:
		volatile unsigned char *port;
		volatile unsigned char *ddr;
		int del;
		int delE;
		
	public:
		__attribute__((noinline))
		lcd4()
		{
			
		}
		lcd4(volatile unsigned char *port, int del, int delE);
		void command(char c);
		void write_char(char c);
		void write_string(char *s);
		void int2str(unsigned int i);
		void cup(int x, int y);
		void cup_row1();
		void cup_row2();
		void erase();
		
	private:
		void delay();
		void delaye();
};

#endif