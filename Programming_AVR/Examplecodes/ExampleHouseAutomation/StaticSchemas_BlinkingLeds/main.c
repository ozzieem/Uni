#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

#include "task_tc.h"
#include "task_dice.h"
#include "task_ring.h"
#include "time.h"

//=== Global objects ====================================
task_tc   t_temp;
task_dice t_dice;
task_ring t_ring;

unsigned long long t=0;
const unsigned long long Tminor=50; //50ms

//=== Interrupt handler for OutputCompare2 match (OC2) interrupt

//SIGNAL(SIG_OUTPUT_COMPARE2)
ISR(TIMER2_COMP_vect)
{
  time_update();
}

/*=== main ==============================================

  Task execution loop.
  
  task_dice: T=50ms
  task_ring: T=300ms
  task_tc:   T=21s=210000ms
  
  ========================================================*/
 
int main(void)
{
  int i_minor=0;
  int i_ring;
  
  time_init( 2, TIME_8MHZ);
  time_init_ocie2();

  io_usart_init(9600,IO_USART_8MHZ);
  
  //--- Init of objects ---
  task_tc_init(&t_temp, 
               &PORTA,
               SENSOR_SMT160_D7,
               TASK_TC_D6,
               TASK_TC_D5,
               TASK_TC_D4
              );
  task_dice_init(&t_dice,&PORTA,0x01);
  task_ring_init(&t_ring,&PORTB);

  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  task_ring_main(&t_ring);
  
  time_get(&t);

  sei();
  
  while ( 1 )
    { 
      i_ring = 2; //Minor cycle 2
      for (i_minor=0; i_minor < 420; i_minor++)
        {
          task_dice_main(&t_dice); //Every minor cycle
          
          if ( i_minor == i_ring ) //Every 6th minor cycle
            {
              task_ring_main(&t_ring);
              i_ring +=6;
            }
          if ( i_minor == 1 )
            task_tc_main(&t_temp);   //Every major cycle
          
          t=t+Tminor; 
          time_wait_until(&t);
        }
    }

  return 0;
}
