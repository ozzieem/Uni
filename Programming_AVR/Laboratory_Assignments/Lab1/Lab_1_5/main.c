/*
 * Lab_1_5.c
 *
 * Created: 26/01/2016 12:04:43
 * Author : Oz
 */ 

#include <avr/io.h>


int main(void)
{
	init_func();
	
    while (1) 
    {
		loop_func();
		wait_milliseconds(300);
    }
}

