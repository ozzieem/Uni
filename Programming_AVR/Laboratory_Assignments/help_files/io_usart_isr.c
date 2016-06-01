#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io_usart_isr.h"
#include "io_bit_fields.h"
#include "qrb.h"

/** \struct io_usart_isr
    \brief These functions perform various operations on a Universal Sycnhronous Asynchronous Receiver and Transmitter. 
    The transmit and receive of characters are implemented with interrupt service routines.
*/

/** \defgroup io_usart_isr USART operations with Tx- and Rx interrupts
    These functions perform various operations on a Universal Sycnhronous Asynchronous Receiver and Transmitter. 
    The transmit and receive of characters are implemented with interrupt service routines.
    
    \code #include <io_usart_isr.h>\endcode 
*/

//===GLOBAL OBJECTS=============================================================

/** \ingroup io_usart_isr
    Object for handling USART 0, in an ATmega16 we have only one USART.
  */

io_usart_isr usart0;

//=== INTERRUPT ROUTINES =======================================================

/** \ingroup io_usart_isr
    Transmit data register empty interrupt. When this interrrupt occurs
    there is time to send a next character. If no more characters are available
    to send then disable this interrupt.
  */
SIGNAL( SIG_UART_DATA  )
{
  char c;
  
  if ( qrbEmpty(&usart0.tq) )
    { 
      bUCSRB.udrie=0; //Disable Tx-interrupt
    }
  else
    {      
      c = qrbDequeue(&usart0.tq);
      UDR = c; 
    }//else
}

/** \ingroup io_usart_isr
    Receive data register interrupt. When this interrupt occurs it is time to read 
    a character from the Rx register.
  */
SIGNAL( SIG_UART_RECV )
{
  char c;
  c = UDR;;
  qrbEnqueue(&usart0.rq, c); 
}

/** \ingroup io_usart_isr
    Init of the usart.
    Frame format: 1 start bit, 8 data bits and 2 stop bits.
    \param this Pointer to an io_usart_isr object.
    \param baud Selected baud rate for example 9600.
    \param megahertz CPU clock frequency (IO_USART_16MHZ, .. ,IO_USART_1MHZ ).
  */
	
void io_usart_isr_init(unsigned int baud, unsigned long megahertz)
{
  unsigned int baudreg = (megahertz/(baud*16l)-1);
  //...Set baud rate...
  UBRRH = (unsigned char)(baudreg>>8);
  UBRRL = (unsigned char)baudreg;
  //...Enable receiver and transmitter...
  UCSRB = (1<<RXEN)|(1<<TXEN);
  //...Set frame format: 1 start, 8 data, 2 stop bits...
  UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

  //... Init if receive and transmit buffers
  qrbInit(&usart0.rq);  
  qrbInit(&usart0.tq);

  //TRANSMIT COMPLETE INTERRUPT DISABLED
  bUCSRB.udrie=0;
  
  //RECEIVE COMPLETE INTERRUPT ENABLED
  bUCSRB.rxcie=1;
}

/** \ingroup io_usart_isr
    Tries to read a character. If one is available it read the character and
    return it otherwise if no character is available it returns -1.
    \return If a character is available it return this, otherwise -1.
  */
int io_usart_isr_getChar()
{ 
  int c;   
  c = qrbDequeue(&usart0.rq);
  return c;
}

/** \ingroup io_usart_isr
    Read one character and  return it.
    \return The character read.
  */
char io_usart_isr_getC()
{ 
  char c;
  
  while ( qrbEmpty(&usart0.rq) )
      ; /*while*/      
     
  c = qrbDequeue(&usart0.rq);
  return c;
}

/** \ingroup io_usart_isr
    Reads size characters before returning.
    \param buf Pointer to the character buffert.
    \param size Number of characters to read.
  */
void io_usart_isr_read(char *buf, int size)
{      
  volatile int i=0; 
  
  do
    {
      buf[i]=io_usart_isr_getC(&usart0);          
      i++;         
    }  
  while (i<size);

}

/** \ingroup io_usart_isr
    Reads characters until it reach the termination character
    \param buf The characters read are put in the buf vector.
    \param size Maximum number of characters to read if no '\n' character comes.
	\param terminationCharacter Character that ends the string.
  */
void io_usart_isr_readString(char *buf, int size, char terminationCharacter)
{      
  volatile int i=0; 
  
  do
    {
      buf[i]=io_usart_isr_getC(&usart0);          
      i++;         
    }  
    while ( (i<size) && (buf[i-1]!=terminationCharacter) );

  buf[i]='\0';
}
 
/** \ingroup io_usart_isr
    Write of one character to the transmitter.
    \param c The character to write.
  */
void io_usart_isr_putC(char c)
{  
  while ( qrbFull(&usart0.tq) ) 
    {  ; }//while 
     
  qrbEnqueue(&usart0.tq, c);
  
  //Enable transmit complete interrupt
  bUCSRB.udrie=1;
}

/** \ingroup io_usart_isr
    Writes size characters from buf.
    \param buf The character buffert.
    \parama size Number of characters to write.
  */
void io_usart_isr_write(char *buf, int size)
{ 
  int i=0;              

  while ( i<size )
    {       
      io_usart_isr_putC(buf[i]); 
      i++;
    }/*while*/     
}


/** \ingroup io_usart_isr
    Writes characters from the buffert buf until a NULL character 
    occurs.
  */
void io_usart_isr_print(char *buf)
{ 
  int i=0;              

  while ( buf[i]!='\0' )
    {       
      io_usart_isr_putC(buf[i]); 
      i++;
    }/*while*/
}
 
 

/** \ingroup io_usart_isr
    Test if the termination character is in the buffert.
	\return True (1) if the character is in the Rx buffert, else false (0).
  */
int io_usart_isr_event_termination_character(char terminationCharacter)
{ 
  return qrbFindCharacter(&usart0.rq, terminationCharacter);
}

 


