#include "io_di.h"

/** \struct io_di
    \brief The io_di class is used to model physical objects connected to a digital input port.
  */

/** \defgroup io_di Digital input operations
    The io_di class is used to model physical objects connected to a digital input port.
		
    \code #include <io_di.h>\endcode 
  */


/** \ingroup io_di
    Init of the port bit as a dgital input.
    \param this Pointer to a io_di object/variable.
    \param port Pointer to a port register (&PORTA,&PORTB,&PORTC,&PORTD).
    \param bit_mask Select of one bit in the port (IO_DI_D7, .. ,IO_DI_D0).
  */
void io_di_init(io_di *this, 
                volatile unsigned char *port,
                unsigned char bit_mask
		)
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
    \param this Pointer to a io_di object/variable.
  */
int io_di_read(io_di *this)
{
  return (*this->pin & this->bit_mask) != 0; 
}

/** \ingroup io_di 
    Conversion the digital input port bit value to a string.
    \param this Pointer to a io_di object/variable.
    \param s String pointer.
  */
char *io_di_string(io_di *this, char *s)
{
  *s++ = io_di_read(this) + '0';
  *s   = '\0';
  return s;
}
