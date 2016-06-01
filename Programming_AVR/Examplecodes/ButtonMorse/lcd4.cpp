#include "util/delay.h"
#include "lcd4.h"

/** \struct lcd4
    \brief this class implements a four bits data interface to a standard LCD with 2 rows with 16 characters on every row.
*/

/** \defgroup lcd4 LCD operations
    this class implements a four bits data interface to a standard LCD with 2 rows with 16 characters on every row.

    \code #include <lcd4.h>\endcode 
*/



/**  \ingroup lcd4
    Private method to do an internal delay when accessing the LCD.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4::delay()
{
  volatile int i;
  for (i=0; i<this->del; i++)
    _delay_us(1);
}

/** \ingroup lcd4
    Private method to do an internal delay when accessing the LCD.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4::delaye()
{
  volatile int i;
  for (i=0; i<this->delE; i++)
    _delay_us(1);
}

/** \ingroup lcd4
    Init of an LCD-thisect with 4 bits data interface.
    \param this Pointer to an lcd4 thisect/variable.
    \param port Address to the port connected with the LCD.
    \param del  Delay parameter, should be tuned, start with 2000.
    \param delE Delay parameter, should be tuned, start with 20.
 */
lcd4::lcd4(volatile unsigned char *port, int del, int delE)
{
  this->port=port;
  this->ddr = port-1;
  this->del =del;
  this->delE=delE;

  *ddr = *ddr | 0x3F;
  *port= *port & 0xC0;
  delay();

  *port=(*port & 0xC0) | 0x03; 
  delaye();
  *port=(*port & 0xC0) | 0x03 |  Symbol::MASK_E; 
  delaye();
  *port=(*port & 0xC0) | 0x03; 
  delay();

  *port=(*port & 0xC0) | 0x03; 
  delaye();
  *port=(*port & 0xC0) | 0x03 |  Symbol::MASK_E; 
  delaye();
  *port=(*port & 0xC0) | 0x03;
  delay();

  *port=(*port & 0xC0) | 0x03; 
  delaye();
  *port=(*port & 0xC0) | 0x03 |  Symbol::MASK_E; 
  delaye();
  *port=(*port & 0xC0) | 0x03;
  delay();


  *port=(*port & 0xC0) | 0x02; 
  delaye();
  *port=(*port & 0xC0) | 0x02 |  Symbol::MASK_E; 
  delaye();
  *port=(*port & 0xC0) | 0x02 ;
  delay();

  command(0x28);
  command(0x0C);
  command(0x01);
  command(0x06);

}

/** \ingroup lcd4
    Command mode communication with the LCD
    \param this Pointer to an lcd4 thisect/variable.
    \param c Command to the LCD.
    
 */
void lcd4::command(char c)
{
  char t;
 
  // Bits D7-D4
  t=c >> 4;
  t=t & 0x0F;
  *this->port = (*this->port & 0xC0) | t; 
  delaye();   
  t = t | Symbol::MASK_E;      // E=High
  *this->port = (*this->port & 0xC0) | t; 
  delaye();
  t = t & (~Symbol::MASK_E);   // E=Low
  *this->port = (*this->port & 0xC0) | t;
  delay();

  // Bits D3-D0
  t = c;
  t=t & 0x0F;
  *this->port =  (*this->port & 0xC0) | t; 
  delaye();
  t = t | Symbol::MASK_E;      // E=High
  *this->port =  (*this->port & 0xC0) | t; 
  delaye();
  t = t & (~Symbol::MASK_E);   // E=Low
  *this->port =  (*this->port & 0xC0) | t;
  delay();
  
}

/** \ingroup lcd4
    Write of a character at the current cursor position on the LCD.
    \param this Pointer to an lcd4 thisect/variable.
    \param c Character to be written at actual cursor position on the LCD.
    
 */
void lcd4::write_char(char c)
{
  char t;
 
  // Bits D7-D4
  t=c >> 4;
  t=(t & 0x0F) | Symbol::MASK_RS;
  *this->port =  (*this->port & 0xC0) | t; delaye();
  t = t | Symbol::MASK_E;      // E=High
  *this->port =  (*this->port & 0xC0) | t;           delaye();
  t = t & (~Symbol::MASK_E);   // E=Low
  *this->port =  (*this->port & 0xC0) | t;
  delay();

  // Bits D3-D0
  t = c ;
  t=(t & 0x0F) | Symbol::MASK_RS;
  *this->port =  (*this->port & 0xC0) | t; delaye();
  t = t | Symbol::MASK_E;      // E=High
  *this->port =  (*this->port & 0xC0) | t;           delaye();
  t = t & (~Symbol::MASK_E);   // E=Low
  *this->port =  (*this->port & 0xC0) | t;
  delay();
}


/** \ingroup lcd4
    Write of a string with start from the current cursor position on the LCD.
    \param this Pointer to an lcd4 object/variable.
    \param s Pointer to the start of the string that shall be written on the LCD.
 */
void lcd4::write_string(char *s)
{
  int i=0;
  
  while ( s[i] != '\0' )
    {
        write_char(s[i]);
        i++;
    }
}

/** \ingroup lcd4
    Position of the cursor on the LCD.
    \param this Pointer to an lcd4 thisect/variable.
    \param y is the row number (integer value 1 or 2).
    \param x is the column number (integer value 1,2, ... , 16)
 */
void lcd4::cup(int y, int x)
{ 
  if ( y == 1  )
    command(Symbol::CmdCUP+x-1);
  else
    command(Symbol::CmdCUP+0x40+x-1); //2004-05-25 constant changed from 56 to 0x40
}

/** \ingroup lcd4
    Position of the cursor to row 1 and column 1.
    \param this Pointer to an lcd4 thisect/variable.
 */
void lcd4::cup_row1()
{ command(Symbol::CmdCUP+0); }

/** \ingroup lcd4
    Position of the cursor to row 2 and column 1.
    \param this Pointer to an lcd4 thisect/variable.
 */
void lcd4::cup_row2()
{ 
  command(Symbol::CmdCUP+0x40 );  //2004-05-25 constant changed from 56 to 0x40
}

/** \ingroup lcd4
    Erase of the LCD.
    \param this Pointer to an lcd4 thisect/variable.
 */
void lcd4::erase()
{
  cup_row1();
  write_string("                ");
  cup_row2();
  write_string("                ");
}

/** \ingroup lcd4
    Converts 16 bit unsigned integer to string and write it to the lcd.
    \param this Pointer to an lcd4 thisect/variable.
    \param i Unsigned integer to print on the LCD-display.
  */
void lcd4::int2str(unsigned int i)
{
  unsigned int divisor = 10000;
  unsigned int n=0;
  char c;
  char s[10];

  do 
    {
      c = (char)(i/divisor);
      s[n++] = c + '0';
      i -= c*divisor;
      divisor /= 10;
    } 
  while (divisor);
  
  s[n] = 0;
  write_string(s);		
}
