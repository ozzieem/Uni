/** \defgroup help_functions Collection of useful functions
  */

/** \ingroup help_functions
    Conversion of an unsigned long integer to a null terminated string.
    Conversion to a hexadecimal string not implemented yet.
    \param base Choose base for the conversion ( 2 to 10)
    \param x    The number to be converted to an string in base.
    \param ptr  Pointer to the string.
    \return          Pointer to the end of the string.
  */
char *ulong2string(unsigned int base, unsigned long x, char *ptr)
{
  unsigned long r;

  r = (x % base) + '0';
  x = x / base;
  
  if ( x != 0 )
    { ptr=ulong2string(base,x,ptr); }

  *ptr=r; //Built the string when nesting back
  *(ptr+1)=0;

  return ptr+1;
}

/** \ingroup help_functions
    Simple float to string conversion. 
    Format: integer.fraction
    The conversion routine works correctly when the 
    magnitude of the floating point number is less than
    0xFFFFFFFF
    \param v         The floating point number that should be converted to a string.
    \param decimals  Number of decimals in the fractional part.
    \param sign      If true signum (+/-) is used.
    \param s         Pointer to the string.
    \return          Pointer to the end of the string.
  */
char *float2str(float v, int decimals, int sign, char *s)
{
  unsigned long i,f;

  
  if ( v < 0 )
    {
      *s++ = '-';
      v=-v;
    }
  else if (sign)
    {
      *s++ = '+';
    }

  if ( v >= 1.0 )
    {
      i = (unsigned long) v;
      v = v - (float) i;
      s=ulong2string(10,i,s);
    }
  else
    {
      *s++='0'; 
    }

  if ( decimals > 0 )
    {
      *s++='.';
      for ( ; decimals > 0 ; decimals--)
	{
	  v = v*10;
	  if (v < 1.0) 
	    *s++='0';
	}
      f = (unsigned long) v;
      s=ulong2string(10,f,s);
    }

  *s='\0';
  return s;
}


/** \ingroup help_functions
    Digital sampling routine, counts the number of reading ones
    when sampling a digital signal n times.
    \param port      The port to read
    \param bit_mask  Selected bit in the port to read (0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01)
    \param n         Number of times of reading.
    \return          Number times reading 1.
  */
unsigned int digital_sampling(volatile unsigned char *port, unsigned char bit_mask, unsigned int n )
{
   // unsigned int i;
   // unsigned int ones=0;
   // for (i=0;i<n; i++)
   //  {
   //    if ( *port & bit_mask )
   //       ones++;
   //  }
   // return ones;
   
   // Parameter port is in register pair R25:R24
   // Parameter bit_mask is in register pair R23:R22, only R22 is used because of char data.
   // Parameter n is in register pair R21:R20
   // Local variable i is in register pair R19:R20
   // Local variable ones is in register pair R31:R30
   asm volatile (
               "        movw	r26, r24  " "\n\t"
               "        ldi	r30, 0x00 " "\n\t"
               "        ldi	r31, 0x00 " "\n\t"
               "        movw	r18, r30  " "\n\t"
               "        cp	r30, r20  " "\n\t"
               "        cpc	r31, r21  " "\n\t"
               "        brcc	3f        " "\n\t"
               "1:                        " "\n\t"
               "        ld	r23, X    " "\n\t"
               "        and	r23, r22  " "\n\t"
               "        breq	2f        " "\n\t"
               "        adiw	r30, 0x01 " "\n\t"
               "        rjmp	4f        " "\n\t"
               "2:                        " "\n\t"
               "        nop               " "\n\t"
               "        nop               " "\n\t"
               "        nop               " "\n\t"
               "4:                        " "\n\t"
               "        subi	r18, 0xFF " "\n\t"
               "        sbci	r19, 0xFF " "\n\t"
               "        cp	r18, r20  " "\n\t"
               "        cpc	r19, r21  " "\n\t"
               "        brcs	1b        " "\n\t"
               "3:                        " "\n\t"
               "        movw	r24, r30  " "\n\t"
               "        ret               " "\n\t"
                );
  return 0; //Dummy return 
}

