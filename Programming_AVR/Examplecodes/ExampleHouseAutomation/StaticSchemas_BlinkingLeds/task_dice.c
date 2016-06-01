#include "task_dice.h"

/** \defgroup task_dice Electronic dice
    The class task_dice is used to implement an electronic dice.

  \code #include <task_dice.h>\endcode 
  */
  
/** \ingroup task_dice
    Init of a task_dice object.
    \param this Pointer to a task_dice object/variable.
    \param port Pointer to a port register (&PORTA,&PORTB,&PORTC,&PORTD).
  */

void task_dice_init(task_dice *this, 
                    volatile unsigned char *port,
                    unsigned char bit_mask
                    )
{
  this->value=1;
  io_di_init(&this->throwButton, port, bit_mask);
}


/** \ingroup task_dice
    The main function for the task.
    \param this Pointer to a task_dice object/variable.
  */

void task_dice_main( task_dice *this )
{ 
   if ( io_di_read(&this->throwButton) )
    {
      this->value++;
      if (this->value > 6)
        this->value=1;
    }
  
    sprintf(this->s,"%d",this->value);
    io_usart_cup(20,20);
    io_usart_write_string(this->s);
}
