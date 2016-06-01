#ifndef _TIME_H
#define _TIME_H
#include <stdio.h>
#include <avr/io.h>
#include "io_usart.h"
#include "io_bit_fields.h"
#include <avr/interrupt.h>


typedef enum
{
  TIME_16MHZ= 16000, 
  TIME_8MHZ =  8000,
  TIME_4MHZ =  4000,
  TIME_2MHZ =  2000,
  TIME_1MHZ =  1000
} time_enums;
typedef struct
{
  unsigned long long ms; //Absolute time
  unsigned long khz;
  unsigned char inc_ms;   //Each clock tick is on inc_ms
  char reserved[3];
} time;

void time_init(unsigned char ms, long mhz);
void time_init_ocie1a(void);
void time_init_ocie0(void);
void time_init_ocie2(void);
void time_update(void);
void time_get(unsigned long long *p_ms);
void time_wait_until(unsigned long long *tWait);
void time_wait_until2(unsigned long long tWait);
void time_get_clock(int *h, int *m, int *s);
void time_string(char *str);
unsigned long time_difference_ms(unsigned long long *tStart, unsigned long long *tEnd );


#endif
