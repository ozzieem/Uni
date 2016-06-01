/* 
* traffic_light.cpp
*
* Created: 2/2/2015 4:13:08 PM
* Author: Kjell
*/


#include "traffic_light.h"

// default constructor
traffic_light::traffic_light()
{
	this->pin = &bPIN_LEDS;
	this->ddr = &bDDR_LEDS;
		ddr->buttonWalker=0b0;
		ddr->ledsCar     =0b111;
		ddr->ledsWalker  =0b111;
	this->port= &bPORT_LEDS;
		port->ledsCar    = (volatile unsigned char) Color::Red;
		port->ledsWalker = (volatile unsigned char) Color::Red;
} //traffic_light


void traffic_light::setWalkerLights(Color c) 
{
	port->ledsWalker = (volatile unsigned char) c;
}

void traffic_light::setCarLights(Color c)
{
	port->ledsCar    = (volatile unsigned char) c;
}
// default destructor
traffic_light::~traffic_light()
{
} //~traffic_light
