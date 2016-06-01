#ifndef _IO_DO_H
#define _IO_DO_H

#include <avr/io.h>
#include "io_bit_fields.h"

typedef enum 
  {
    IO_DO_D7 = 0x80,
    IO_DO_D6 = 0x40,
    IO_DO_D5 = 0x20,
    IO_DO_D4 = 0x10,
    IO_DO_D3 = 0x08,
    IO_DO_D2 = 0x04,
    IO_DO_D1 = 0x02,
    IO_DO_D0 = 0x01
  } io_do_bit_mask;

typedef struct
{
  volatile unsigned char *port;
  volatile unsigned char *ddr;
  volatile unsigned char *pin;
  unsigned char bit_mask;
  unsigned char unused;

} io_do;
#include "io_do.h"

void io_do_init(io_do *this, 
                volatile unsigned char *port,
                unsigned char bit_mask
		);

    int io_do_read(io_do *this);

    void io_do_write(io_do *this, int value );

    int io_do_toggle(io_do *this);

    char *io_do_string(io_do *this, char *s);

    int io_do_set(io_do *this);
    
    int io_do_reset(io_do *this);

#endif
