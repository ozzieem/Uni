#include "pwm.h"

/** \struct pwm
    \brief Implements a PWM output using TIMER0 and pin PB3
*/

/** \defgroup pwm Pulse Width Modulation
    Generation of PWM-outputs using the TIMERs

    \code #include <pwm.h>\endcode 
*/

/** \ingroup pwm
    Init of at pwm object using TIMER0.
    \param obj Pointer to a pwm object/variable.
  */
void pwm0_init(pwm *obj)
{
  //Fast PWM
  bTCCR0.wgm00=1;
  bTCCR0.wgm01=1;

  //Clear OC0 on compare match, set OC0 at TOP
  bTCCR0.com00=0;
  bTCCR0.com01=1;

  //Clock prescaler
  //bTCCR0.cs0=1; //Clock/1
  bTCCR0.cs0=2; //Clock/8
  //bTCCR0.cs0=5; //Clock/1024

  //PB3=OC0
  bDDRB.D3=1;
  //bPORTB.D3=1;
  
  pwm0_set_duty(obj,255); //off

}
/** \ingroup pwm
    The PWM is activated.
    \param obj Pointer to a pwm object/variable.
  */
void pwm0_on(pwm *obj)
{
  OCR0 = obj->duty_cycle;
}

/** \ingroup pwm
    The PWM output is deactivated.
    \param obj Pointer to a pwm object/variable.
  */
void pwm0_off(pwm *obj)
{
  OCR0 = 255;
}

/** \ingroup pwm
    The PWM output is programmed with a new duty cycle.
    The dutcy cycle is selected as a integer number in the 
    interval 0 (0%) to 255 (100%).
    \param obj Pointer to a pwm object/variable.
  */
void pwm0_set_duty(pwm *obj, unsigned char duty )
{
  obj->duty_cycle=duty;
  OCR0 = duty;
}
