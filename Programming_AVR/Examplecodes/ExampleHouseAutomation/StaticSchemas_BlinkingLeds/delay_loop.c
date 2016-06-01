#include "delay_loop.h"

/** \struct delay_loop
    \brief A class that creates delay in a wait (delay) loop.
  */
	
/** \defgroup delay_loop
    A class that creates delay in a wait (delay) loop.

    \code #include <delay_loop.h>\endcode 
  */
	
/**  \ingroup delay_loop
     Init of a delay loop object.
     \param this Pointer to a delay_loop object/variable.
     \param value The desired delay time in micro seconds.
     \param clockFrequency The frequency of the clock source for the processor.
 */
void delay_loop_init(delay_loop *this, unsigned long value, int clockFrequency )
{ 
  this->micros=value-8;
  switch ( clockFrequency )
    {
    case DELAY_LOOP_32MHZ:
      this->micros = this->micros*2;
      break;
    case DELAY_LOOP_8MHZ:
      this->micros = this->micros/2;
      break;
    case DELAY_LOOP_4MHZ:
      this->micros = this->micros/4;
      break;
    case DELAY_LOOP_2MHZ:
      this->micros = this->micros/8;
      break;
    case DELAY_LOOP_1MHZ:
      this->micros = this->micros/16;
      break;
    default: //DELAY_LOOP_16MHZ:
      this->micros = this->micros*1;
      break;
    }
}

/** \ingroup delay_loop
    The method to call to make a delay.
		\param this Pointer to a delay_loop object/variable.
 */
void delay_loop_delay(delay_loop *this)
{
  delay_loop_ldelay( this->micros/0x10000, this->micros & 0xFFFF );
}

/** \ingroup delay_loop
    Private internal method used by other public method.
 */
void delay_loop_ldelay(int countMSB, int countLSB)
{
  countMSB++;

  asm volatile 
        (
 		"1:                  nop       ; 1 machine cycle  " "\n\t" 
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "2:      nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        nop       ; 1 machine cycle   " "\n\t"
                "        sbiw %0,1 ; 2 machine cycles  " "\n\t"
 		            "        brne 1b   ; 1/2 machine cycles" "\n\t"
		            "        sbiw %1,1 ; 2 machine cycles  " "\n\t"
		            "        brne 2b   ; 1/2 machine cycles"
 		: "=w" (countLSB) , "=w" (countMSB) 
 		: "0" (countLSB) ,  "1" (countMSB)
 	);
}
