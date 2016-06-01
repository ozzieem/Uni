#include <stdio.h>
#include "io_ai.h"

/** \struct io_ai
    \brief These functions perform various operations analog inports.
*/

/** \defgroup io_ai Analog Input port operations
    These functions perform various operations on the analog inputs port.

    \code #include <io_ai.h>\endcode 
*/

/** \ingroup io_ai
    Init of an analog input port. The port is initiated with an external voltage reference.
    \param obj Pointer to a io_ai object/variable.
    \param channel Choosen analog input port on PORTA (IO_AI_CHANNEL7, .. ,IO_AI_CHANNEL0)
    \param prescale The ADC converter sholud be clocked in the interval 50-200kHz
    select appropiate scale factor to scale down the processor clock, see Technical reference manual.
  */
	
void io_ai_init( io_ai *obj, char channel, char prescale )
{
  obj->channel = channel;
  
  bADCSRA.adp=prescale; //Prescale factor for the A/D
  bADCSRA.aden=1; //Enable of the  A/D
}

/** \ingroup io_ai
    Select of analog voltage reference for the DAC.
    \param obj Pointer to a io_ai object/variable.
    \param aref Type of analog reference:
                IO_AI_ANALOG_REFERENCE_EXTERNAL=0,
                IO_AI_ANALOG_REFERENCE_AVCC,
                IO_AI_ANALOG_REFERENCE_INTERNAL
  */
void io_ai_aref( io_ai *obj, char aref)
{
  bADMUX.refs=aref; 
}

/** \ingroup io_ai
    Read of an analog input port.
    \param obj Pointer to a io_ai object/variable.
  */
unsigned int io_ai_read( io_ai *obj)
{
  bADMUX.mux=obj->channel; 
  bADCSRA.adsc=1; //A/D start of conversion

  while (bADCSRA.adsc==1)
    ;


  return (unsigned int) ADC; //10 bits value
}

/** \ingroup io_ai
    Read of an analog input port and return of it as a string.
    \param obj Pointer to a io_ai object/variable.
  */
void io_ai_string( io_ai *obj, char *s )
{
  unsigned int v=io_ai_read(obj);
  
  sprintf(s,"AI%d=%d\n\r",(int) obj->channel, v);
}




