#include "time.h"


/** \defgroup time Time measurement
    These functions perform som time measurement functions

    \code #include <time.h>\endcode 
*/

/** \ingroup time
    Init of the time measurement singleton object.
    \param ms Each clock tick interrupt should time counter ms be updated with inc_ms
  */
time::time(unsigned char ms, unsigned char timer_x)
{
  this->inc_ms = ms;
  this->ms = 0;
  
  switch(timer_x)
  {
	  case TIMER0:
	  init_ocie0();
	  break;
	  case TIMER2:
	  init_ocie2();
	  break;
  }
  
}

/** \ingroup time
    Init of timer 0 for Output Compare Interrupt with a period time on inc_ms
    Condition inc_ms=2ms or 1ms and 8 Mhz clock frequency
    The structure of the interrupt routine is as the code below:
	
	ISR(TIMER0_COMP_vect)
	{
		update();
	}
  */

void time::init_ocie0(void)
{
  bTCCR0.cs0   =3;//Clock prescaler CK/64
  bTCCR0.wgm01 =1;
  bTIMSK.ocie0 =1;
  if (this->inc_ms==2)
    OCR0= (unsigned char) 250;
  else
    OCR0= (unsigned char) 125;
}

/** \ingroup time
    Init of timer 2 for Output Compare Interrupt with a period time on inc_ms
    Condition inc_ms=2ms or 1ms and 8 Mhz clock frequency
    The structure of the interrupt routine is as the code below:
    
    ISR(TIMER2_COMP_vect)
    {
	    update();
    }
  */

void time::init_ocie2(void)
{
  bTCCR2.cs2   =4;//Clock prescaler CK/64
  bTCCR2.wgm21 =1;
  bTIMSK.ocie2 =1;
    if (this->inc_ms==2)
    OCR2= (unsigned char) 250;
  else
    OCR2= (unsigned char) 125; 
}

/** \ingroup time
    This function should be called in an interrupt service routine.
  */
void time::update(void)
{
  this->ms = this->ms + this->inc_ms;
}

/** \ingroup time
    Read of the clocks actual time.
    \param p_ms Pointer to the variable which should be assigned the actual time value.
  */
  
void time::get(unsigned long long *p_ms)
{
  unsigned char sreg;
  sreg = SREG;
  cli();
  *p_ms = this->ms;
  SREG = sreg;
}

/** \ingroup time
    Looping until the clock time is *tWait.
    \param tWait Pointer to the variable which holds the time we are waiting until.
  */

void time::wait_until( unsigned long long *tWait)
{
  unsigned long long t;
  
  do
    {
      get(&t);
      //_string(); //test
    }
  while ( *tWait >  t );
}

//~ /** \ingroup time
    //~ Read of the clock in format hh:mm:ss.
    //~ \param h Pointer to the variable to put the hours.
    //~ \param m Pointer to the variable to put the minutes.
    //~ \param s Pointer to the variable to put the seconds.
  //~ */
//~ void get_clock(int *h, int *m, int *s)
//~ {
  //~ long long t;

  //~ get(&t);
  
  //~ t = t/1000;
  //~ *s = t % 60;
  //~ t = t / 60;
  //~ *m = t % 60;
  //~ t = t / 60;
  //~ *h = t % 24;
//~ }


////~ /** \ingroup time
    ////~ Set of the clock in format hh:mm:ss.
    ////~ \param h Hours.
    ////~ \param m Minutes.
    ////~ \param s Seconds.
  ////~ */
////~ void set_clock(int h, int m, int s)
////~ {
  ////~ long long r = h*60LL*60LL*1000LL+m*60LL*1000LL+s*1000LL;
//
  ////~ unsigned char sreg;
  ////~ sreg = SREG;
  ////~ cli();
  //
  ////~ this->ms = r;
//
  ////~ SREG = sreg;
////~ }
//
/** \ingroup time
    Set of the clock in format hh:mm:ss.
    \param tStart Pointer to the start time value.
    \param tEnd Pointer to the end time value.
  */
unsigned long time::difference_ms(unsigned long long *tStart, unsigned long long *tEnd )
{
  unsigned long long r = *tEnd - *tStart;

  if ( (r / 0x100000000LL) != 0 )
    return 0xFFFFFFFF;
  else
    return r;
}


//... timeDifferenceS ...............................................
unsigned long time::difference_seconds(long long *tStart, long long *tEnd )
{
	long long r = (*tEnd - *tStart + 500LL) / 1000LL;
	long rl;
  
	if ( *(long *) &r != 0 )
		rl = 0xFFFFFFFF;
	else
		rl = * ((long *) &r + 1);

	return rl;
}

////~ /** \ingroup time
    ////~ Read of the clock in a string with the format "hh:mm:ss"
    ////~ \param s Pointer to the string.
  ////~ */
////~ void string(char *str)
////~ {
  ////~ long long t;
  ////~ int m,s,i,h;
//
  ////~ get(&t);
  //
  ////~ t = t/1000;
  ////~ s = t % 60;
  ////~ t = t / 60;
  ////~ m = t % 60;
  ////~ t = t / 60;
  ////~ h = t;
  ////~ sprintf(str,"%2d:%2d:%2d",h,m,s);
////~ }
//
//
////~ //... timeStringClock ................................................
////~ void timeStringClock(char *str)
////~ {
//
  ////~ int m,s,i,h;
//
  ////~ timeGetClock(&h,&m,&s);
//
  ////~ uint2string(10,h,str);
  ////~ i=str2len(str);
  ////~ str[i]=':';
  ////~ str[i+1]='\0';
  //
  ////~ uint2string(10,m,str+i+1);
  ////~ i=str2len(str);
  ////~ str[i]=':';
  ////~ str[i+1]='\0';
//
  ////~ uint2string(10,s,str+i+1);
////~ }
//
//
