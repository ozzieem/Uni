#ifndef _DELAY_LOOP
#define _DELAY_LOOP
#include <avr/io.h>
#include "io_bit_fields.h"

typedef struct
{
  unsigned long micros;
} delay_loop;

typedef enum
{
  DELAY_LOOP_32MHZ,
  DELAY_LOOP_16MHZ,
  DELAY_LOOP_8MHZ,
	DELAY_LOOP_4MHZ,
	DELAY_LOOP_2MHZ,
	DELAY_LOOP_1MHZ
} delay_loop_enum;


void delay_loop_init(delay_loop *obj, unsigned long value, int clockFrequency);
void delay_loop_delay(delay_loop *obj);
void delay_loop_ldelay(int __countMSB, int __countLSB);

#endif
