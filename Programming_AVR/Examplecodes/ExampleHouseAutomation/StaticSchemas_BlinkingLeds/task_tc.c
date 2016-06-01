#include "task_tc.h"

/** \defgroup task_tc Temperature control with the sensor SMT160 and a relay
    The class task_tc is used to control the temperature of a process with a
    temprature sensor SMT160 and an actuator with a digital input.
    
    \code #include <task_tc.h>\endcode 
  */
  
/** \ingroup task_tc
    Init of the a task_tc object.
    \param this Pointer to a task_tc object/variable.
    \param port Pointer to a port register (&PORTA,&PORTB,&PORTC,&PORTD).
    \param bit_mask_sensor Select of one bit in the port to be used as digital input for a SMT160 sensor ((SENSOR_SMT160_D7, .. ,SENSOR_SMT160_D0)).
    \param bit_mask_actuator Select of one bit in the port to be used as digital output to control the actuator (TASK_TC_D7, .. ,TASK_TC_D0).
  */

void task_tc_init(task_tc *this, 
                  volatile unsigned char *port,
                  unsigned char bit_mask_sensor,
                  unsigned char bit_mask_actuator,
                  unsigned char bit_mask_incr,
                  unsigned char bit_mask_decr
                  )
{
  sensor_smt160_init(&this->y_temp, port, bit_mask_sensor);
  io_do_init(&this->u_heater,port,bit_mask_actuator);
  lcd4_init(&this->display, &PORTC, &DDRC, 4000, 50);
  io_di_init(&this->r_inc, port, bit_mask_incr);
  io_di_init(&this->r_dec, port, bit_mask_decr);
  counter_init(&this->r_temp,50,10);
  relay_init(&this->controller,1);;
}


/** \ingroup task_tc
    The main function for the task.
    \param this Pointer to a task_tc object/variable.
  */

void task_tc_main( task_tc *this )
{ 
  if ( io_di_read(&this->r_inc) )
    counter_inc(&this->r_temp);
  
  if ( io_di_read(&this->r_dec) )
    counter_dec(&this->r_temp);
  
  this->r = counter_read(&this->r_temp);
  
  this->y = (int) (sensor_smt160_read(&this->y_temp)+0.5);
  
  this->e = this->r - this->y;
  
  this->u =  relay_run(&this->controller,this->e);
  
  io_do_write(&this->u_heater, this->u);
  
  sprintf(this->s1, "%2d %cC (%2d %cC)    ", this->y, 0xDF, this->r,0xDF);
  lcd4_cup_row1(&this->display);
  lcd4_write_string(&this->display, this->s1); 
  
}

