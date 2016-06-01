#include "task_ring.h"

/** \defgroup task_ring Ring counter
    The class task_ring is used to implement a ring counter.

  \code #include <task_ring.h>\endcode 
  */
  
/** \ingroup task_ring
    Init of a task_ring object.
    \param this Pointer to a task_ring object/variable.
    \param port Pointer to a port register (&PORTA,&PORTB,&PORTC,&PORTD).
  */

void task_ring_init(task_ring *this, 
                    volatile unsigned char *port
                    )
{
  this->value=0x01;
  this->port = port;
  this->ddr = port-1;
  *(this->ddr)=0xFF; //Px7-Px0 are outputs
}


/** \ingroup task_ring
    The main function for the task.
    \param this Pointer to a task_ring object/variable.
  */

void task_ring_main( task_ring *this )
{ 
 
  this->value = this->value << 1;
  if ( this->value == 0 )
    this->value=0x01;
  *this->port = ~this->value;
}
