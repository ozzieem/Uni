#include "io_do.h"
/** \struct io_do
  The io_do class is used to model physical objects connected to a digital output port.
*/

/** \defgroup io_do Digital output operations
    The io_do class is used to model physical objects connected to a digital output port.

    \code #include <io_di.h>\endcode 
*/

/** \ingroup io_do
    Init of a port bit as a digital output.
    \param obj Pointer to a io_do object/variable.
    \param port Pointer to a port register (&PORTx)
    \param bit_mask Choosen bit in the port is indicated with a 1 (0x80,0x40,..,0x01)
*/

void io_do_init(io_do *obj, 
                volatile unsigned char *port,
                unsigned char bit_mask
		)
{
  obj->port           = port;
  obj->ddr = port-1;
  obj->pin              = port-2;
  obj->bit_mask                 = bit_mask;

  //Programming of the data direction register and the selected bit.
  *obj->ddr = *obj->ddr | obj->bit_mask;
}

/** \ingroup io_do
    Read back of the the digital output port bit.
    \param obj Pointer to a io_do object/variable.
  */
int io_do_read(io_do *obj)
{
  return (*obj->port & obj->bit_mask) != 0; 
}

/** \ingroup io_do
    Write a logical 0 or 1 to the port bit.
    \param obj Pointer to a io_do object/variable.
    \param value Value 0/1 to be written on the output port.
  */
  
void io_do_write(io_do *obj, int value )
{
  if ( value )
    *obj->port = *obj->port  | obj->bit_mask;
  else
     *obj->port = *obj->port  & ~obj->bit_mask;
}

/** \ingroup io_do
    Sets the digital output signal to 1.
    \param obj Pointer to a io_do object/variable.
  */
int io_do_set(io_do *obj)
{
  return  (*obj->port = *obj->port | obj->bit_mask);
}

/** \ingroup io_do
    Sets the digital output signal to 0.
    \param obj Pointer to a io_do object/variable.
  */
int io_do_reset(io_do *obj)
{
  return  (*obj->port = *obj->port & ~obj->bit_mask);
}

/** \ingroup io_do
    Toggles the digital output signal.
    \param obj Pointer to a io_do object/variable.
  */
int io_do_toggle(io_do *obj)
{
  return  (*obj->port = *obj->port ^ obj->bit_mask);
}


/** \ingroup io_do
    Reads the port value and convert it to a string.
    \param obj Pointer to a io_do object/variable.
    \param s Null terminated string.
  */
char *io_do_string(io_do *obj, char *s)
{
  *s++ = io_do_read(obj) + '0';
  *s   = '\0';
  return s;
}
