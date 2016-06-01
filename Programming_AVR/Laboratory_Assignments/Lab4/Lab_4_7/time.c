#include "time.h"

volatile time _gTime;

void _time_string(void)
{
  char s[20];
  unsigned long long t;
  
  time_get(&t);
  sprintf(s,"%8lx",(long) t );
  io_usart_write_string(s);
}

/** \defgroup time Time measurement
    These functions perform som time measurement functions

    \code #include <time.h>\endcode 
*/

/** \ingroup time
    Init of the time measurement singleton object.
    \param ms Each clock tick interrupt should time counter ms be updated with inc_ms
  */
void time_init(unsigned char ms, long mhz)
{
  _gTime.khz = mhz;
  _gTime.inc_ms = ms;
  _gTime.ms = 0;
}

/** \ingroup time
    Init of timer 0 for Output Compare Interrupt with a period time on inc_ms
    Condition inc_ms=2ms or 1ms and 8 Mhz clock frequency
    The structure of the interrupt routine is as the code below:
    
    SIGNAL(SIG_OUTPUT_COMPARE0)
    {
      time_update();
    }
  */
void time_init_ocie0(void)
{
  bTCCR0.cs0   =3;//Clock prescaler CK/64
  bTCCR0.wgm01 =1;
  bTIMSK.ocie0 =1;
  if (_gTime.inc_ms==2)
    OCR0= (unsigned char) 250;
  else
    OCR0= (unsigned char) 125;
}

/** \ingroup time
    Init of timer 1 for Output Compare 1A Interrupt with a period time on inc_ms, 
    where inc_ms should be in the interval 1 to 5ms.
    The structure of the interrupt routine is as the code below:
    
    SIGNAL(SIG_OUTPUT_COMPARE1A)
    {
      time_update();
    }
  */
void time_init_ocie1a(void)
{
  bTCCR1B.cs1   =1;//Clock prescaler CK/1
  bTCCR1B.wgm12 =1;
  bTCCR1B.wgm13 =0;
  bTCCR1A.wgm10 =0;
  bTCCR1A.wgm11 =0;
  bTIMSK.ocie1a=1;
  OCR1A= (int) (_gTime.khz * _gTime.inc_ms );  
}

/** \ingroup time
    Init of timer 2 for Output Compare Interrupt with a period time on inc_ms
    Condition inc_ms=2ms or 1ms and 8 Mhz clock frequency
    The structure of the interrupt routine is as the code below:
    
    SIGNAL(SIG_OUTPUT_COMPARE2)
    {
      time_update();
    }
  */
void time_init_ocie2(void)
{
  bTCCR2.cs2   =4;//Clock prescaler CK/64
  bTCCR2.wgm21 =1;
  bTIMSK.ocie2 =1;
    if (_gTime.inc_ms==2)
    OCR2= (unsigned char) 250;
  else
    OCR2= (unsigned char) 125; 
}

/** \ingroup time
    This function should be called in an interrupt service routine.
  */
void time_update(void)
{
  _gTime.ms = _gTime.ms + _gTime.inc_ms;
}

/** \ingroup time
    Read of the clocks actual time.
    \param p_ms Pointer to the variable which should be assigned the actual time value.
  */
  
void time_get(unsigned long long *p_ms)
{
  unsigned char sreg;
  sreg = SREG;
  cli();
  *p_ms = _gTime.ms;
  SREG = sreg;
}

/** \ingroup time
    Looping until the clock time is *tWait.
    \param tWait Pointer to the variable which holds the time we are waiting until.
  */

void time_wait_until( unsigned long long *tWait)
{
  unsigned long long t;
  
  do
    {
      time_get(&t);
      //_time_string(); //test
    }
  while ( *tWait >  t );
}

//~ /** \ingroup time
    //~ Read of the clock in format hh:mm:ss.
    //~ \param h Pointer to the variable to put the hours.
    //~ \param m Pointer to the variable to put the minutes.
    //~ \param s Pointer to the variable to put the seconds.
  //~ */
//~ void time_get_clock(int *h, int *m, int *s)
//~ {
  //~ long long t;

  //~ time_get(&t);
  
  //~ t = t/1000;
  //~ *s = t % 60;
  //~ t = t / 60;
  //~ *m = t % 60;
  //~ t = t / 60;
  //~ *h = t % 24;
//~ }


//~ /** \ingroup time
    //~ Set of the clock in format hh:mm:ss.
    //~ \param h Hours.
    //~ \param m Minutes.
    //~ \param s Seconds.
  //~ */
//~ void time_set_clock(int h, int m, int s)
//~ {
  //~ long long r = h*60LL*60LL*1000LL+m*60LL*1000LL+s*1000LL;

  //~ unsigned char sreg;
  //~ sreg = SREG;
  //~ cli();
  
  //~ _gTime.ms = r;

  //~ SREG = sreg;
//~ }

/** \ingroup time
    Set of the clock in format hh:mm:ss.
    \param tStart Pointer to the start time value.
    \param tEnd Pointer to the end time value.
  */
unsigned long time_difference_ms(unsigned long long *tStart, unsigned long long *tEnd )
{
  unsigned long long r = *tEnd - *tStart;

  if ( (r / 0x100000000LL) != 0 )
    return 0xFFFFFFFF;
  else
    return r;
}

//~ //... timeDifferenceS ...............................................
//~ unsigned long timeDifferenceS(long long *tStart, long long *tEnd )
//~ {
  //~ long long r = (*tEnd - *tStart + 500LL) / 1000LL;
  //~ long rl;
  
  //~ if ( *(long *) &r != 0 )
    //~ rl = 0xFFFFFFFF;
  //~ else
    //~ rl = * ((long *) &r + 1);

  //~ return rl;
//~ }

//~ /** \ingroup time
    //~ Read of the clock in a string with the format "hh:mm:ss"
    //~ \param s Pointer to the string.
  //~ */
//~ void time_string(char *str)
//~ {
  //~ long long t;
  //~ int m,s,i,h;

  //~ time_get(&t);
  
  //~ t = t/1000;
  //~ s = t % 60;
  //~ t = t / 60;
  //~ m = t % 60;
  //~ t = t / 60;
  //~ h = t;
  //~ sprintf(str,"%2d:%2d:%2d",h,m,s);
//~ }


//~ //... timeStringClock ................................................
//~ void timeStringClock(char *str)
//~ {

  //~ int m,s,i,h;

  //~ timeGetClock(&h,&m,&s);

  //~ uint2string(10,h,str);
  //~ i=str2len(str);
  //~ str[i]=':';
  //~ str[i+1]='\0';
  
  //~ uint2string(10,m,str+i+1);
  //~ i=str2len(str);
  //~ str[i]=':';
  //~ str[i+1]='\0';

  //~ uint2string(10,s,str+i+1);
//~ }


