/*
* traffic_light.h
*
* Created: 2/2/2015 4:13:09 PM
* Author: Kjell
*/


#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include <avr/io.h>
#include <util/delay.h>


class traffic_light
{

	public:
	enum class Color
	{
		Red       = 0b011,
		Yellow    = 0b101,
		Green     = 0b110,
		RedYellow = 0b001
	};
	
	/*
	                                LLLL
					                LLLL
	               ------------------------------------
				             LL     ----
					                ----    LL Lights for the vehicles
				   ------------------------------------
				                    LLLL
					                LLLL 
									     Lights for the walker
									     Button walker
	 */
	struct bit_field
	{
		unsigned char buttonWalker   : 1;
		unsigned char ledsWalker     : 3;
		unsigned char ledsCar        : 3;
		unsigned char unused         : 1;
	};
	
	
	protected:
	private:
	volatile bit_field *pin;
	volatile bit_field *ddr;
	volatile bit_field *port;
	
	//functions
	public:
	traffic_light();
	void setWalkerLights(Color c) ;
	void setCarLights(Color c) ;
	
	~traffic_light();
	protected:
	private:
	traffic_light( const traffic_light &c );
	traffic_light& operator=( const traffic_light &c );

}; //traffic_light

#define bPORT_LEDS ( * (volatile traffic_light::bit_field *) &PORTB)
#define bDDR_LEDS  ( * (volatile traffic_light::bit_field *) &DDRB)
#define bPIN_LEDS  ( * (volatile traffic_light::bit_field *) &PINB)

#endif //__TRAFFIC_LIGHT_H__
