/*
* ring_counter.cpp
*
* Created: 12/20/2013 11:46:36 AM
*  Author: Kjell
*/

#include "ring_counter.h"

ring_counter::ring_counter( volatile unsigned char *port )
{
	volatile unsigned char *ddr = port-1;
	this->value=1;
	this->port=port;

	*ddr = 0xFF;
	*(this->port) = ~this->value; //Ökar tydligheten, kompilatorn sköter optimeringen
}

void ring_counter::run()
{
	this->value = (this->value << 1);
	if ( this->value == 0)
	this->value=1;

	*(this->port) = ~this->value;
}