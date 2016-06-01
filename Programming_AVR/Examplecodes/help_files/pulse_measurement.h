#ifndef _PULSE_MEASUREMENT_H
#define _PULSE_MEASUREMENT_H
#include <avr/io.h>
#include "io_bit_fields.h"
#include <avr/interrupt.h>
typedef enum
{
  PM_TIMER1_CLOCK_DIVIDE_FACTOR_1   = 1,
  PM_TIMER1_CLOCK_DIVIDE_FACTOR_8   = 2,
  PM_TIMER1_CLOCK_DIVIDE_FACTOR_64  = 3,
  PM_TIMER1_CLOCK_DIVIDE_FACTOR_256 = 4,
  PM_TIMER1_CLOCK_DIVIDE_FACTOR_1024= 5,
  PM_TIMER1_CLOCK_EXTERNAL_FEDGE    = 6,
  PM_TIMER1_CLOCK_EXTERNAL_REDGE    = 7,
  
  PM_TIMER1_ONE_PULSE = 11,
  PM_TIMER1_ONE_PERIOD= 12,
  PM_TIMER1_ONE_DUTY  = 13
  
} pm_timer1_clock_prescaler;

typedef struct 
{
  unsigned int pflanc;   //Value read from timer on positive flanc. 
  unsigned int pflanc2;  //Value read from timer on positive flanc. 
  unsigned int nflanc;   //Value read from timer on negative flanc.
  unsigned int cycles;   //Number of clock cycles between positive and negative flanc.
  unsigned int n;        //Counts number of measurements
          char type;     //Type of measurement
          char one_shot;  
} pm_timer1;

extern volatile pm_timer1 _pm1;

void pm_timer1_init(int prescaler );
 int pm_timer1_one_pulse(void);
 int pm_timer1_one_period(void);
 int pm_timer1_one_duty(void);
#endif
