#include "sensor_smt160.h"

/** \defgroup sensor_smt160 Temperature sensor SMT160
    The sensor_smt160 class is used to encapsulate the behavoir of the 
    temperature sensor SMT160.
    \code #include <sensor_smt160.h>\endcode 
  */
  
/** \ingroup sensor_smt160
    Init of the port bit as a digital input to be able to read a sensor of
    type SMT160 with a PWM output
    \param this Pointer to a sensor_smt160 object/variable.
    \param port Pointer to a port register (&PORTA,&PORTB,&PORTC,&PORTD).
    \param bit_mask Select of one bit in the port (SENSOR_SMT160_D7, .. ,SENSOR_SMT160_D0).
  */
void sensor_smt160_init(sensor_smt160 *this, 
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

 
/** \ingroup sensor_smt160
    Read of the temperature as a float number.
    \param this Pointer to a sensor_smt160 object/variable.
    \return The temperature.
  */
float sensor_smt160_read(sensor_smt160 *this)
{
  float duty,temp;
  duty = (float) digital_sampling(this->pin, this->bit_mask, 30000 ) / 30000;
  temp = (duty-0.32)/0.00470;
  return temp;
}
