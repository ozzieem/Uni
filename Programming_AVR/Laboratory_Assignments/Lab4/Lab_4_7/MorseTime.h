/*
 * MorseTime.h
 *
 * Created: 22/03/2016 11:35:39
 *  Author: Oz
 */ 
 

#ifndef MORSETIME_H_
#define MORSETIME_H_

typedef struct  
{
	unsigned tick_counter;
	unsigned tick;
	unsigned reset_counter;
	unsigned reset_morse;
} MorseTime;

morseTime_init(MorseTime*);



#endif /* MORSETIME_H_ */