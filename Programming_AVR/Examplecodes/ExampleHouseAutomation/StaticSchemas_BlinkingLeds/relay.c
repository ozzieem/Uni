#include "relay.h"

/** \defgroup relay Class that implements a relay function
    
    \code #include <relay.h>\endcode 
  */
  
/** \ingroup relay
    Init of the a relay object.
    \param this Pointer to a relay object/variable.
    \param de 
    */
void relay_init(relay *this, int de )
{
  this->out=0;
  this->delta=de;
}


/** \ingroup relay
    Method that calls periodical.
    \param this Pointer to a relay object/variable.
    \param e Input error signal. 
    */

int relay_run(relay *this, int e)
{
  if ( e > this->delta )
    this->out=1;
  else if ( e < -this->delta )
    this->out=0;

  return this->out;
}



