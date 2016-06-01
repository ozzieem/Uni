#ifndef _IO_USART_H 
#define _IO_USART_H
#include <avr/io.h>

#include <avr/io.h>
#include "io_bit_fields.h"

typedef struct
{

} io_usart;

typedef enum 
  {
    IO_USART_16MHZ = 16000000L,
    IO_USART_8MHZ  =  8000000L,
    IO_USART_4MHZ  =  4000000L,
    IO_USART_2MHZ  =  2000000L,
    IO_USART_1MHZ  =  1000000L
  } io_usart_enum;


// USART Baud rate calculation
#define IO_USART_CPU             8000000      // 8Mhz 
#define IO_USART_BAUD_19200      (IO_USART_CPU/(19200*16l)-1)
#define IO_USART_BAUD_9600       (IO_USART_CPU/(9600*16l)-1)
#define IO_USART_BAUD_2400       (IO_USART_CPU/(2400*16l)-1)
#define IO_USART_BAUD_1200       (IO_USART_CPU/(1200*16l)-1)

          void io_usart_init( unsigned int baud, unsigned long megahertz);
 unsigned char io_usart_read_char( void );
          int io_usart_write_char( char data );
          void io_usart_write_string(char *s);
          void io_usart_read_string( char *s );
          void io_usart_cup(int x, int y);
#endif
