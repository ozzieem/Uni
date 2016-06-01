#ifndef _UDELAY_H
#define _UDELAY_H

#include <avr/io.h>
#include "io_bit_fields.h"

void udelay_timer0_init_8mhz();
void udelay_timer0_delay(unsigned char del );

#endif
