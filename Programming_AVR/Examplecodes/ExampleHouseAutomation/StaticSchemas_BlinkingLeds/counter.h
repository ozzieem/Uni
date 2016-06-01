#ifndef _COUNTER_H
#define _COUNTER_H

typedef struct
{

  int max;  //max value of the counter
  int min;  //min value of the counter
  int value;//actual value of the counter
  
} counter;

void counter_init(counter *this,int max, int min);
 int counter_inc(counter *this);
 int counter_dec(counter *this);
 int counter_read(counter *this);


#endif
