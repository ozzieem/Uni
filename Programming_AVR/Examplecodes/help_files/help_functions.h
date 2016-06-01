#ifndef _HELP_FUNCTIONS_H
#define _HELP_FUNCTIONS_H
#include <avr/io.h>
#include "io_bit_fields.h"

char *ulong2string(unsigned int base, unsigned long x, char *ptr);
char *float2str(float v, int decimals, int sign, char *s);

unsigned int digital_sampling(volatile unsigned char *port, unsigned char bit_mask, unsigned int n );

#endif
