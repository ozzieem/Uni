#ifndef _TASK_DICE_H
#define _TASK_DICE_H

#include <stdio.h>
#include "io_di.h"
#include "io_usart.h"

typedef struct
{
  io_di throwButton;
  
  char value;
  
  char s[7];
  
} task_dice;

void task_dice_init(task_dice *this, 
                    volatile unsigned char *port,
                    unsigned char bit_mask
                    );
void task_dice_main( task_dice *this );

#endif
