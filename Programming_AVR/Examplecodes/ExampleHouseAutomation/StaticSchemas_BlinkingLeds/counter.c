#include "counter.h"

/**  counter_init
  */
void counter_init(counter *this,int max, int min)
{
  this->max=max;
  this->min=min;
  this->value=min;
}

/** counter_inc
  */
int counter_inc(counter *this)
{
  int carry=0;
  
  this->value++;
  
  if ( this->value > this->max )
    {
      this->value=this->min;
      carry=1;
    }
  return carry;
}

/** counter_dec
  */
int counter_dec(counter *this)
{
  int carry=0;
  
  this->value--;
  
  if ( this->value < this->min )
    {
      this->value=this->max;
      carry=1;
    }
  return carry;
}

/** counter_read
  */
int counter_read(counter *this)
{
  return this->value;
}
