#ifndef _IO_USART_ISR_H 
#define _IO_USART_ISR_H

#include "qrb.h"


typedef struct
{
  qrb  rq;      /*Recive data ring buffert queue.*/
  qrb  tq;      /*Transmit data ring buffert queue.*/  
} io_usart_isr;

typedef enum 
  {
    IO_USART_ISR_16MHZ = 16000000L,
    IO_USART_ISR_8MHZ  =  8000000L,
    IO_USART_ISR_4MHZ  =  4000000L,
    IO_USART_ISR_2MHZ  =  2000000L,
    IO_USART_ISR_1MHZ  =  1000000L
  } IO_USART_ISR_enum;


// USART Baud rate calculation
#define IO_USART_ISR_CPU             8000000      // 8Mhz 
#define IO_USART_ISR_BAUD_19200      (IO_USART_ISR_CPU/(19200*16l)-1)
#define IO_USART_ISR_BAUD_9600       (IO_USART_ISR_CPU/(9600*16l)-1)
#define IO_USART_ISR_BAUD_2400       (IO_USART_ISR_CPU/(2400*16l)-1)
#define IO_USART_ISR_BAUD_1200       (IO_USART_ISR_CPU/(1200*16l)-1)

void io_usart_isr_init(unsigned int baud, unsigned long megahertz);
 int io_usart_isr_getChar();
char io_usart_isr_getC();
void io_usart_isr_read(char *buf, int size);
void io_usart_isr_readString(char *buf, int size, char terminationCharacter);
void io_usart_isr_putC(char c);
void io_usart_isr_write(char *buf, int size);
void io_usart_isr_print(char *buf);
 int io_usart_isr_event_termination_character(char terminationCharacter);
char io_usart_isr_tx_buffert_full();

extern io_usart_isr usart0;
 
#endif
