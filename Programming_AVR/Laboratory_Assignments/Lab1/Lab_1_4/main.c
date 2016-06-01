/*
 * Lab_1_4.c
 *
 * Created: 21/01/2016 12:15:46
 * Author : Oz
 */ 

#include <avr/io.h>


int main(void)
{
	init_func();
    /* Replace with your application code */
    while (1) 
    {
		loop_func();
		wait_milliseconds(300);
    }
}

