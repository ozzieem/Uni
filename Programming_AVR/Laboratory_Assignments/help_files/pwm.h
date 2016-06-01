#ifndef _PWM_H
#define _PWM_H

#include <avr/io.h>
#include "io_bit_fields.h"

typedef struct 
{
  int duty_cycle;
  
} pwm;

void pwm0_init(pwm *obj);
void pwm0_on(pwm *obj);
void pwm0_off(pwm *obj);
void pwm0_set_duty(pwm *obj, unsigned char duty );


#endif
