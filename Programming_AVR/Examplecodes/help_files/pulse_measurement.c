#include "pulse_measurement.h"

/** \struct pm_timer1
    \brief Measure the time for a pulse.
*/

/** \defgroup pm_timer1 Pulse mesurement functions.
    Time mesurements done on a logic signal.

    \code #include <pm_timer1.h>\endcode 
*/

volatile pm_timer1 _pm1; //Volatile because the membership variable
                         //is used both in the interrupt routine and 
                         //the one shot function to communicate between
                         //them.

/** \ingroup pm_timer1
    Interrupt service routine for input capture 1 interrupts.
  */
SIGNAL(SIG_INPUT_CAPTURE1)
{
                                           //============
  if ( _pm1.type == PM_TIMER1_ONE_PERIOD ) //===PERIOD===
  {                                        //============
    if ( _pm1.one_shot == 1 )
    {
      _pm1.pflanc = ICR1;
      _pm1.one_shot=2;
    }
    else
    {
      _pm1.pflanc2 = ICR1;      
      _pm1.one_shot = 0;
      
      //Interrupt disable.
      bTIMSK.ticie1 = 0;
      
      if ( _pm1.pflanc2 >= _pm1.pflanc )
        _pm1.cycles = _pm1.pflanc2 - _pm1.pflanc;
      else
        _pm1.cycles = 0xFFFF - _pm1.pflanc + _pm1.pflanc2+1;
    }
    bTIFR.icf1 = 1;
  }                                            //===========
  else if ( _pm1.type == PM_TIMER1_ONE_PULSE ) //===PULSE===
  {                                            //===========
    if ( bTCCR1B.ices1 )
    {
      _pm1.pflanc = ICR1;
      bTCCR1B.ices1 = 0;
    }
    else
    {
      _pm1.nflanc = ICR1;
      bTCCR1B.ices1 = 1;
      
      _pm1.one_shot = 0;
      //Interrupt disable.
      bTIMSK.ticie1 = 0;
      
      if ( _pm1.nflanc >= _pm1.pflanc )
        _pm1.cycles = _pm1.nflanc - _pm1.pflanc;
      else
        _pm1.cycles = 0xFFFF - _pm1.pflanc + _pm1.nflanc+1;
    }
    bTIFR.icf1 = 1;
  }                                           //==========
  else if ( _pm1.type == PM_TIMER1_ONE_DUTY ) //===DUTY===
  {                                           //==========
    if ( _pm1.one_shot==1 )
    {
      _pm1.pflanc = ICR1;
      bTCCR1B.ices1 = 0;
      _pm1.one_shot = 2;
    }
    else if ( _pm1.one_shot==2 )
    {
      _pm1.nflanc = ICR1;
      bTCCR1B.ices1 = 1;
      _pm1.one_shot = 3;
    }
    else
    {
      _pm1.pflanc2 = ICR1;
      _pm1.one_shot = 0;
      //Interrupt disable.
      bTIMSK.ticie1 = 0;
    }
    bTIFR.icf1 = 1;
  }
  else
  {
    bTIFR.icf1 = 1;
  }
}

/** \ingroup pm_timer1
    Init of a pm_timer1 object using TIMER1.
    \param prescaler Clock prescaler. The system clock could be divided by a factor 1,8,64 or 256.
                     Use the predefined constants PULSE_MEASUREMENT_CLOCK_DIVIDE_FACTOR_1, 
                     PULSE_MEASUREMENT_CLOCK_DIVIDE_FACTOR_8, PULSE_MEASUREMENT_CLOCK_DIVIDE_FACTOR_64 or
                     PULSE_MEASUREMENT_CLOCK_DIVIDE_FACTOR_256.
  */
void pm_timer1_init(int prescaler )
{
  //Noise canceler 
  bTCCR1B.icnc1=1;
  
  //Input capture edge select, starts with positive edge.
  bTCCR1B.ices1 =1;
  
  //Clock prescaler
  bTCCR1B.cs1=prescaler;

  //PD6=ICP, input capture pin 
  bDDRD.D6=0;
  
  //Interrupt disable.
  bTIMSK.ticie1 = 0;
  
  _pm1.n=0;
  _pm1.pflanc=0;
  _pm1.nflanc=0;
  _pm1.cycles=0;
  _pm1.one_shot=0;
}

/** \ingroup pm_timer1
    On very short pulses the one pulse method is preferred.
    \return Returns the number clock cycles for the pulse.
  */
int pm_timer1_one_pulse()
{
  _pm1.type = PM_TIMER1_ONE_PULSE;
  _pm1.one_shot=1;

  //Noise canceler off
  bTCCR1B.icnc1=0;

  //Input capture edge select, starts with positive edge.
  bTCCR1B.ices1 =1;
  bTIFR.icf1 = 1;

  //Interrupt enable.
  bTIMSK.ticie1 = 1;

  while ( _pm1.one_shot ) //Measurement is activated,wait until done.
    ;
  
  _pm1.n++;
  
  return _pm1.cycles;
}


/** \ingroup pm_timer1
    Mesurement of one period
    \return Returns the number clock cycles for the period.
  */
int pm_timer1_one_period()
{
  _pm1.type = PM_TIMER1_ONE_PERIOD;
  _pm1.one_shot=1;

  //Noise canceler off
  bTCCR1B.icnc1=0;

  //Input capture edge select, starts with positive edge.
  bTCCR1B.ices1 =1;
  bTIFR.icf1 = 1;

  //Interrupt enable.
  bTIMSK.ticie1 = 1;

  while ( _pm1.one_shot != 0 ) //Measurement is activated,wait until done.
    ;
  
  _pm1.n++;
  
  return _pm1.cycles;
}


/** \ingroup pm_timer1
    Mesurement of the duty cycle in promille
    \return Returns the duty cycle in promille.
  */
int pm_timer1_one_duty()
{
  unsigned long pulse;
  unsigned int period;
  unsigned int duty;
  
  _pm1.type = PM_TIMER1_ONE_DUTY;
  _pm1.one_shot=1;

  //Noise canceler off
  bTCCR1B.icnc1=0;

  //Input capture edge select, starts with positive edge.
  bTCCR1B.ices1 =1;
  bTIFR.icf1 = 1;

  //Interrupt enable.
  bTIMSK.ticie1 = 1;

  while ( _pm1.one_shot != 0 ) //Measurement is activated,wait until done.
    ;
  
  _pm1.n++;
  
  if ( _pm1.nflanc >= _pm1.pflanc )
    _pm1.cycles = _pm1.nflanc - _pm1.pflanc;
  else
    _pm1.cycles = 0xFFFF - _pm1.pflanc + _pm1.nflanc+1;

  pulse = 1000L*_pm1.cycles;

  if ( _pm1.pflanc2 >= _pm1.pflanc )
    _pm1.cycles = _pm1.pflanc2 - _pm1.pflanc;
  else
    _pm1.cycles = 0xFFFF - _pm1.pflanc + _pm1.pflanc2+1;
  
  period = _pm1.cycles;
  
  duty = pulse / period;
  
  return duty;
}
