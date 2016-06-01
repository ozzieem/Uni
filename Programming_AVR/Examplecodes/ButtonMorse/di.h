#ifndef _DIGITAL_INPUT_H
#define _DIGITAL_INPUT_H
#include <avr/io.h>
#include "io_bit_fields.h"

class digital_input
{
	public:
	enum PortBitMask
	{
		D7 = 0x80,
		D6 = 0x40,
		D5 = 0x20,
		D4 = 0x10,
		D3 = 0x08,
		D2 = 0x04,
		D1 = 0x02,
		D0 = 0x01
	};
	
	private:
	volatile unsigned char *port;
	volatile unsigned char *ddr;
	volatile unsigned char *pin;
	unsigned char bit_mask;
	unsigned char unused;

public:
	digital_input( volatile unsigned char *port, unsigned char bit_mask);
	int read();
	char *string(char *s);
};
#endif
