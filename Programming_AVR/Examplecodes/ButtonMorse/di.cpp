#include "di.h"

/** \struct io_di
    \brief The io_di class is used to model physical objects connected to a digital input port.
  */

/** \defgroup io_di Digital input operations
    The io_di class is used to model physical objects connected to a digital input port.
		
    \code #include <io_di.h>\endcode 
  */


/** \ingroup io_di
    Init of the port bit as a dgital input.
    \param obj Pointer to a io_di object/variable.
    \param port Pointer to a port register (&PORTA,&PORTB,&PORTC,&PORTD).
    \param bit_mask Select of one bit in the port (D7, .. ,D0).
  */
digital_input::digital_input(volatile unsigned char *port, unsigned char bit_mask )
{
  this->port= port;
  this->ddr = port-1;
  this->pin = port-2;
  this->bit_mask = bit_mask;

  //Programming of the data direction register and the selected bit.
  *this->ddr = *this->ddr & ~this->bit_mask;
}


/** \ingroup io_di 
    Read of the digital input port bit.
    \param obj Pointer to a io_di object/variable.
  */
int digital_input::read()
{
  return (*this->pin & this->bit_mask) != 0; 
}

/** \ingroup io_di 
    Conversion the digital input port bit value to a string.
    \param obj Pointer to a io_di object/variable.
    \param s String pointer.
  */
char *digital_input::string( char *s)
{
  *s++ = read() + '0';
  *s   = '\0';
  return s;
}
