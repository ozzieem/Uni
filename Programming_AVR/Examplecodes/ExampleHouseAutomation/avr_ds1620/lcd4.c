#include "lcd4.h"

/** \struct lcd4
    \brief This class implements a four bits data interface to a standard LCD with 2 rows with 16 characters on every row.
*/

/** \defgroup lcd4 LCD operations
    This class implements a four bits data interface to a standard LCD with 2 rows with 16 characters on every row.

    \code #include <lcd4.h>\endcode 
*/

#define MASK_E  0x10
#define MASK_RS 0x20

/**  \ingroup lcd4
    Private method to do an internal delay when accessing the LCD.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4_delay(lcd4 *this)
{
  volatile int i;
  for (i=0; i<this->del; i++)
    ;
}

/** \ingroup lcd4
    Private method to do an internal delay when accessing the LCD.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4_delaye(lcd4 *this)
{
  volatile int i;
  for (i=0; i<this->delE; i++)
    ;
}

/** \ingroup lcd4
    Init of an LCD-object with 4 bits data interface.
    \param this Pointer to an lcd4 object/variable.
    \param port Address to the port connected with the LCD.
    \param ddr  Address to the data direction register associated with the port.
    \param del  Delay parameter, should be tuned, start with 2000.
    \param delE Delay parameter, should be tuned, start with 20.
 */
void lcd4_init(lcd4 *this, volatile unsigned char *port, volatile unsigned char *ddr, int del, int delE)
{
  this->port=port;
  this->ddr =ddr;
  this->del =del;
  this->delE=delE;

  *ddr = *ddr | 0x3F;
  *port= *port & 0xC0;
  lcd4_delay(this);

  *port=(*port & 0xC0) | 0x03; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x03 |  MASK_E; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x03; 
  lcd4_delay(this);

  *port=(*port & 0xC0) | 0x03; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x03 |  MASK_E; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x03;
  lcd4_delay(this);

  *port=(*port & 0xC0) | 0x03; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x03 |  MASK_E; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x03;
  lcd4_delay(this);


  *port=(*port & 0xC0) | 0x02; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x02 |  MASK_E; lcd4_delaye(this);
  *port=(*port & 0xC0) | 0x02 ;
  lcd4_delay(this);

  lcd4_command(this, 0x28);
  lcd4_command(this, 0x0C);
  lcd4_command(this, 0x01);
  lcd4_command(this, 0x06);

}

/** \ingroup lcd4
    Command mode communication with the LCD
    \param this Pointer to an lcd4 object/variable.
    \param c Command to the LCD.
    
 */
void lcd4_command(lcd4 *this, char c)
{
  char t;
 
  // Bits D7-D4
  t=c >> 4;
  t=t & 0x0F;
  *this->port = (*this->port & 0xC0) | t; lcd4_delaye(this);   
  t = t | MASK_E;      // E=High
  *this->port = (*this->port & 0xC0) | t; lcd4_delaye(this);
  t = t & (~MASK_E);   // E=Low
  *this->port = (*this->port & 0xC0) | t;
  lcd4_delay(this);

  // Bits D3-D0
  t = c;
  t=t & 0x0F;
  *this->port =  (*this->port & 0xC0) | t; lcd4_delaye(this);
  t = t | MASK_E;      // E=High
  *this->port =  (*this->port & 0xC0) | t; lcd4_delaye(this);
  t = t & (~MASK_E);   // E=Low
  *this->port =  (*this->port & 0xC0) | t;
  lcd4_delay(this);
  
}

/** \ingroup lcd4
    Write of a character at the current cursor position on the LCD.
    \param this Pointer to an lcd4 object/variable.
    \param c Character to be written at actual cursor position on the LCD.
    
 */
void lcd4_write_char(lcd4 *this, char c)
{
  char t;
 
  // Bits D7-D4
  t=c >> 4;
  t=(t & 0x0F) | MASK_RS;
  *this->port =  (*this->port & 0xC0) | t; lcd4_delaye(this);
  t = t | MASK_E;      // E=High
  *this->port =  (*this->port & 0xC0) | t;           lcd4_delaye(this);
  t = t & (~MASK_E);   // E=Low
  *this->port =  (*this->port & 0xC0) | t;
  lcd4_delay(this);

  // Bits D3-D0
  t = c ;
  t=(t & 0x0F) | MASK_RS;
  *this->port =  (*this->port & 0xC0) | t; lcd4_delaye(this);
  t = t | MASK_E;      // E=High
  *this->port =  (*this->port & 0xC0) | t;           lcd4_delaye(this);
  t = t & (~MASK_E);   // E=Low
  *this->port =  (*this->port & 0xC0) | t;
  lcd4_delay(this);
}


/** \ingroup lcd4
    Write of a string with start from the current cursor position on the LCD.
    \param this Pointer to an lcd4 object/variable.
    \param s Pointer to the start of the string that shall be written on the LCD.
 */
void lcd4_write_string(lcd4 *this, char *s)
{
  int i=0;
  
  while ( s[i] != '\0' )
    {
        lcd4_write_char(this, s[i]);
        i++;
    }
}

/** \ingroup lcd4
    Position of the cursor on the LCD.
    \param this Pointer to an lcd4 object/variable.
    \param y is the row number (integer value 1 or 2).
    \param x is the column number (integer value 1,2, ... , 16)
 */
void lcd4_cup(lcd4 *this,int y, int x)
{ 
  if ( y == 1  )
    lcd4_command(this, CmdCUP+x-1);
  else
    lcd4_command(this, CmdCUP+0x40+x-1); //2004-05-25 constant changed from 56 to 0x40
}

/** \ingroup lcd4
    Position of the cursor to row 1 and column 1.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4_cup_row1(lcd4 *this)
{ lcd4_command(this, CmdCUP+0); }

/** \ingroup lcd4
    Position of the cursor to row 2 and column 1.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4_cup_row2(lcd4 *this)
{ 
  lcd4_command(this, CmdCUP+0x40 );  //2004-05-25 constant changed from 56 to 0x40
}

/** \ingroup lcd4
    Erase of the LCD.
    \param this Pointer to an lcd4 object/variable.
 */
void lcd4_erase(lcd4 *this)
{
  lcd4_cup_row1(this);
  lcd4_write_string(this,"                ");
  lcd4_cup_row2(this);
  lcd4_write_string(this,"                ");
}

/** \ingroup lcd4
    Converts 16 bit unsigned integer to string and write it to the lcd.
    \param this Pointer to an lcd4 object/variable.
    \param i Unsigned integer to print on the LCD-display.
  */
void lcd4_int2str(lcd4 *this, unsigned int i)
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
  lcd4_write_string(this,s);		
}
