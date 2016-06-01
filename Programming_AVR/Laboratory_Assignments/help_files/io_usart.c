#include <stdio.h>
#include "io_usart.h"

/** \struct io_usart
    \brief These functions perform various operations on a Universal Sycnhronous Asynchronous Receiver and Transmitter.
*/

/** \defgroup io_usart USART operations
    These functions perform various operations on a Universal Sycnhronous Asynchronous Receiver and Transmitter.

    \code #include <io_usart.h>\endcode 
*/

/** \ingroup io_usart
    Init of the usart.
    Frame format: 1 start bit, 8 data bits and 2 stop bits.
    \param baud Selected baud rate for example 9600.
    \param megahertz CPU clock frequency (IO_USART_16MHZ, .. ,IO_USART_1MHZ ).
  */
	
void io_usart_init( unsigned int baud, unsigned long megahertz)
{
  unsigned int baudreg = (megahertz/(baud*16l)-1);
  //...Set baud rate...
  UBRRH = (unsigned char)(baudreg>>8);
  UBRRL = (unsigned char)baudreg;
  //...Enable receiver and transmitter...
  UCSRB = (1<<RXEN)|(1<<TXEN);
  //...Set frame format: 1 start, 8 data, 2 stop bits...
  UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

}

/** \ingroup io_usart
    Receive of one character.
    Wait loop until one character is received.
    \return Character read from the receiver unit.
  */
unsigned char io_usart_read_char( void )
{
  //...Wait for data to be received...
  while ( !(UCSRA & (1<<RXC)) )
          ; //empty loop
          
  //...Get and return received data from buffer...
  return UDR;
}

/** \ingroup io_usart
    Transmit of one character.
    Wait loop until USART is ready to transmit a new character.
    \param data Character to be written to the transmitter unit.
    \return Always 1 byte is sent.

  */
int io_usart_write_char( char data )
{
  //...Wait for empty transmit buffer...
  while ( !( UCSRA & (1<<UDRE)) )
        ; //empty loop
                          
  //...Put data into buffer, sends the data...
  UDR = data;

  return 1;
}

/** \ingroup io_usart
    Write of a null terminated string.
    \param s Null terminated string to be written to the transmitter unit.
  */
void io_usart_write_string(char *s)
{
  while (*s)
    io_usart_write_char(*s++);
}

/** \ingroup io_usart
    Read of a string terminated with a '\r'-character.
    \param s Read of a string of character from the receiver unit. Reads progress until a '\r' is recieved.
  */
void io_usart_read_string( char *s )
{
  char    c;          
  int     is=0; 
  int     noString=1;
 
  while ( noString )
    {    
      c=io_usart_read_char(); 
      switch ( c ) 
        {
          case '\n':
            break;
          case '\r':
            noString=0;
            io_usart_write_string("\n\r");
            break;  
          case 0x08: //Backspace 
            if (is > 0) 
              is--;
            io_usart_write_string("\b \b");
            s[is]='\0'; 
            break; 
          default:
            if ( c > 0x1F )
              { 
                s[is]=c;
                is +=1;
                s[is]='\0';
                io_usart_write_char(c);
              }//if
        }//switch
    }//while
}

/** \ingroup io_usart
    Cursor positioning in a terminal window with ESCape sequences.
    \param x Column position.
    \param y Row position.
  */
void io_usart_cup(int x, int y)
{
  char s[20];

  io_usart_write_char(0x1B); //ESCape
  sprintf(s,"[%d;%dH",y,x);
  io_usart_write_string(s);
}

