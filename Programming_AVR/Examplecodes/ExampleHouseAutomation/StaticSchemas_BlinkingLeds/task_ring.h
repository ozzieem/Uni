#ifndef _TASK_RING_H
#define _TASK_RING_H

typedef struct
{
  char value;
  volatile unsigned char *port; 
  volatile unsigned char *ddr; 
  
} task_ring;

void task_ring_init(task_ring *this, 
                  volatile unsigned char *port
                  );

void task_ring_main( task_ring *this );

#endif
