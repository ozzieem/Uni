/*
* ring_counter.h
*
* Created: 12/20/2013 11:47:43 AM
*  Author: Kjell
*/


#ifndef RING_COUNTER_H_
#define RING_COUNTER_H_


class ring_counter
{
private:
	unsigned char value;
	volatile unsigned char *port;
public:
	ring_counter(volatile unsigned char *port );
	void run();
} ;


#endif /* RING_COUNTER_H_ */