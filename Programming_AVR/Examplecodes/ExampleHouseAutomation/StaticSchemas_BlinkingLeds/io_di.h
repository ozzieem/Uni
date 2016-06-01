#ifndef _IO_DI_H
#define _IO_DI_H
#include <avr/io.h>
#include "io_bit_fields.h"

typedef enum 
  {
    IO_DI_D7 = 0x80,
    IO_DI_D6 = 0x40,
    IO_DI_D5 = 0x20,
    IO_DI_D4 = 0x10,
    IO_DI_D3 = 0x08,
    IO_DI_D2 = 0x04,
    IO_DI_D1 = 0x02,
    IO_DI_D0 = 0x01
  } io_di_bit_mask;

typedef struct
{
  volatile unsigned char *port;
  volatile unsigned char *ddr;
  volatile unsigned char *pin;
  unsigned char bit_mask;
  unsigned char unused;

} io_di;

void io_di_init(io_di *this, 
                volatile unsigned char *port,
                unsigned char bit_mask
		);
int io_di_read(io_di *this);

char *io_di_string(io_di *this, char *s);

#endif
