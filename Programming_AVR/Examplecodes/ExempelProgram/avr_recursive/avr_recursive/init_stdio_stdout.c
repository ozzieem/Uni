#include <stdio.h>
#include "io_usart.h"



void init_stdio_stdout (void) __attribute__ ((naked)) __attribute__ ((section (".init8")));
void init_stdio_stdout (void)
{
	int (*PUT)(char, FILE*) = (int (*)(char, FILE*)) &io_usart_write_char;
	int (*GET)(FILE*) = (int (*)(FILE*)) &io_usart_read_char;

  	io_usart_init( 9600, IO_USART_8MHZ);
  	fdevopen( PUT, GET );
}
