 #include "MorseTime.h"

 morseTime_init(MorseTime* mt)
 {
	mt->tick_counter = 0;
	mt->tick = 10;
	mt->reset_counter = 0;
	mt->reset_morse = 20;
 }