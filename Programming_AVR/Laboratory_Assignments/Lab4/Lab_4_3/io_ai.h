#ifndef _IO_AI_H 
#define _IO_AI_H
#include <avr/io.h>
#include "io_bit_fields.h"

typedef struct
{
  char channel;
  
} io_ai;

typedef enum
{
  IO_AI_CHANNEL0,
  IO_AI_CHANNEL1,
  IO_AI_CHANNEL2,
  IO_AI_CHANNEL3,
  IO_AI_CHANNEL4,
  IO_AI_CHANNEL5,
  IO_AI_CHANNEL6,
  IO_AI_CHANNEL7	
} io_ai_enums;

typedef enum
{
  IO_AI_PRESCALE_DEF,  // Default = 2
  IO_AI_PRESCALE_2,
  IO_AI_PRESCALE_4,
  IO_AI_PRESCALE_8,
  IO_AI_PRESCALE_16,
  IO_AI_PRESCALE_32,
  IO_AI_PRESCALE_64,
  IO_AI_PRESCALE_128
} io_ai_enums_prescale;

typedef enum
{
  IO_AI_ANALOG_REFERENCE_EXTERNAL=0,
  IO_AI_ANALOG_REFERENCE_AVCC    =1,
  IO_AI_ANALOG_REFERENCE_INTERNAL=3  
} io_ai_enums_aref;

void io_ai_init( io_ai *obj, char channel, char prescale );
void io_ai_aref( io_ai *obj, char aref);
unsigned int io_ai_read( io_ai *obj);
void io_ai_string( io_ai *obj, char *s );

#endif
