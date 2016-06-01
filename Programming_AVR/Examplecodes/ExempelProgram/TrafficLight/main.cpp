/*
 * TrafficLight.cpp
 *
 * Created: 2/2/2015 4:03:53 PM
 *  Author: Kjell
 */ 


#include <avr/io.h>

#include "traffic_light.h"

int main(void)
{
	traffic_light tl;
	
	tl.setCarLights(traffic_light::Color::Green);
	tl.setCarLights(traffic_light::Color::Yellow);
	tl.setCarLights(traffic_light::Color::RedYellow);
	tl.setCarLights(traffic_light::Color::Red);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}