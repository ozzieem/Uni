#ifndef _IO_ATMEGA16_H
#define _IO_ATMEGA16_H
#include <avr/io.h>

/* Change log:
   2003-12-20 bPINA,bPORTA,bDDRA gets the right adress values
*/

//---------------------------------------------------------
//--- Bit field structure byteRegister --------------------
//---------------------------------------------------------
typedef struct
{
    unsigned char D0 : 1;
    unsigned char D1 : 1;
    unsigned char D2 : 1;
    unsigned char D3 : 1;
    unsigned char D4 : 1;
    unsigned char D5 : 1;
    unsigned char D6 : 1;
    unsigned char D7 : 1;
} byteRegister;

//---------------------------------------------------------
//--- Bit masks--------------------------------------------
//---------------------------------------------------------
#define mD7 0x80 
#define mD6 0x40 
#define mD5 0x20 
#define mD4 0x10 
#define mD3 0x08
#define mD2 0x04 
#define mD1 0x02 
#define mD0 0x01 

//---------------------------------------------------------
//--- TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)
//---------------------------------------------------------

//---------------------------------------------------------
//--- ADC -------------------------------------------------
//---------------------------------------------------------

typedef struct
{
    unsigned char acis  : 2;
    unsigned char acic  : 1;
    unsigned char acie  : 1;
    unsigned char aci   : 1;
    unsigned char aco   : 1;
    unsigned char acbg  : 1;
    unsigned char acd   : 1;
} adcsrRegister;

#define bADCSR	(*(volatile adcsrRegister *) &ADCSR)


typedef struct
{
    unsigned char adp   : 3;
    unsigned char adie  : 1;
    unsigned char adif  : 1;
    unsigned char adate : 1;
    unsigned char adsc  : 1;
    unsigned char aden  : 1;
} adcsraRegister;

#define bADCSRA	(*(volatile adcsraRegister *) &ADCSRA)


typedef struct
{
    unsigned char mux   : 5;
    unsigned char adlar : 1;
    unsigned char refs  : 2;
} admuxRegister;

#define bADMUX	(*(volatile admuxRegister *) &ADMUX)


//---------------------------------------------------------
//--- Analog comparator -----------------------------------
//---------------------------------------------------------

//---------------------------------------------------------
//--- USART -----------------------------------------------
//---------------------------------------------------------

//---------------------------------------------------------
//--- SPI -------------------------------------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char spr0  : 1 ;
  unsigned char spr1  : 1 ;
  unsigned char cpha  : 1 ;
  unsigned char cpol  : 1 ;
  unsigned char mstr  : 1 ;
  unsigned char dord  : 1 ;
  unsigned char spe   : 1 ;
  unsigned char spie  : 1 ;
} spcrRegister;

typedef struct
{
  unsigned char spi2x : 1 ;
  unsigned char unused: 5 ;
  unsigned char wcol  : 1 ;
  unsigned char spif  : 1 ;
} spsrRegister;

typedef struct
{
    unsigned char D0 : 1;
    unsigned char D1 : 1;
    unsigned char D2 : 1;
    unsigned char D3 : 1;
    unsigned char ss   : 1;
    unsigned char mosi : 1;
    unsigned char miso : 1;
    unsigned char sck  : 1;
} portB_SPI_register; 

#define bPINB_SPI	(*(volatile portB_SPI_register  *) &PINB  )
#define bDDRB_SPI	(*(volatile portB_SPI_register  *) &DDRB  )
#define bPORTB_SPI	(*(volatile portB_SPI_register  *) &PORTB )

#define bSPCR	(*(volatile spcrRegister  *) &SPCR)
#define bSPSR	(*(volatile spsrRegister  *) &bSPSR)


//---------------------------------------------------------
//--- Port D ----------------------------------------------
//---------------------------------------------------------

#define bPIND	(*(volatile byteRegister  *) &PIND)
#define bDDRD	(*(volatile byteRegister  *) &DDRD)
#define bPORTD	(*(volatile byteRegister  *) &PORTD)

//---------------------------------------------------------
//--- Port C ---------------------------------------------
//---------------------------------------------------------

#define bPINC	(*(volatile byteRegister  *) &PINC)
#define bDDRC	(*(volatile byteRegister  *) &DDRC)
#define bPORTC	(*(volatile byteRegister  *) &PORTC)


//---------------------------------------------------------
//--- Port B ---------------------------------------------
//---------------------------------------------------------

#define bPINB	(*(volatile byteRegister  *) &PINB)
#define bDDRB	(*(volatile byteRegister  *) &DDRB)
#define bPORTB	(*(volatile byteRegister  *) &PORTB)


//---------------------------------------------------------
//--- Port A ----------------------------------------------
//---------------------------------------------------------

#define bPINA	(*(volatile byteRegister  *) &PINA)
#define bDDRA	(*(volatile byteRegister  *) &DDRA)
#define bPORTA	(*(volatile byteRegister  *) &PORTA)

//---------------------------------------------------------
//--- EEPROM ----------------------------------------------
//---------------------------------------------------------

//---------------------------------------------------------
//--- Watchdog --------------------------------------------
//---------------------------------------------------------


//---------------------------------------------------------
//--- Timer 2 ---------------------------------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char cs2   : 3 ;
  unsigned char wgm21 : 1 ;
  unsigned char com20 : 1 ;
  unsigned char com21 : 1 ;
  unsigned char wgm20 : 1 ;
  unsigned char foc2  : 1 ;
} tccr2Register;

#define bTCCR2	(*(volatile tccr2Register  *) &TCCR2)

//---------------------------------------------------------
//--- Timer 1 ---------------------------------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char wgm10    : 1;
  unsigned char wgm11    : 1;
  unsigned char foc1b    : 1;
  unsigned char foc1a    : 1;
  unsigned char com1b    : 2;
  unsigned char com1a    : 2;
} tccr1aRegister;

#define bTCCR1A	(*(volatile tccr1aRegister *) &TCCR1A)


typedef struct
{
  unsigned char cs1      : 3;
  unsigned char wgm12    : 1;
  unsigned char wgm13    : 1;
  unsigned char reserved : 1;
  unsigned char ices1    : 1;
  unsigned char icnc1    : 1;
} tccr1bRegister;

#define bTCCR1B	(*(volatile tccr1bRegister *) &TCCR1B)


//---------------------------------------------------------
//--- Special Function IO Register ------------------------
//---------------------------------------------------------

//---------------------------------------------------------
//--- Oscillator Calibration Register----------------------
//--- On-Chip Debug Register ------------------------------
//---------------------------------------------------------

//---------------------------------------------------------
//--- Timer 0 ---------------------------------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char cs0   : 3 ;
  unsigned char wgm01 : 1 ;
  unsigned char com00 : 1 ;
  unsigned char com01 : 1 ;
  unsigned char wgm00 : 1 ;
  unsigned char foc0  : 1 ;
} tccr0Register;

#define bTCCR0	(*(volatile tccr0Register  *) &TCCR0)

//---------------------------------------------------------
//--- Micro Control Unit - MCU ----------------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char isc0  : 2 ;
  unsigned char isc1  : 2 ;
  unsigned char sm0   : 1 ;
  unsigned char sm1   : 1 ;
  unsigned char se    : 1 ;
  unsigned char sm2   : 1 ;
} mcucrRegister;

#define bMCUCR	(*(volatile mcucrRegister  *) &MCUCR)


typedef struct
{
  unsigned char porf        : 1 ;
  unsigned char extrf       : 1 ;
  unsigned char borf        : 1 ;
  unsigned char wdrf        : 1 ;
  unsigned char jtrf        : 1 ;
  unsigned char reserved    : 1 ;
  unsigned char isc2        : 1 ;
  unsigned char jtd         : 1 ;
} mcucsrRegister;

#define bMCUCSR	(*(volatile mcucsrRegister  *) &MCUCSR)


//---------------------------------------------------------
//--- Timer Interrupt Flag Register -----------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char tov0  : 1;
  unsigned char ocf0  : 1;
  unsigned char tov1  : 1;
  unsigned char ocf1b : 1;
  unsigned char ocf1a : 1;
  unsigned char icf1  : 1; 
  unsigned char tov2  : 1;
  unsigned char ocf2  : 1;
} tifrRegister;

#define bTIFR	(*(volatile tifrRegister *) &TIFR)

//---------------------------------------------------------
//--- Timer Interrupt MaSk Register -----------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char toie0  : 1;
  unsigned char ocie0  : 1;
  unsigned char toie1  : 1;
  unsigned char ocie1b : 1;
  unsigned char ocie1a : 1;
  unsigned char ticie1 : 1;
  unsigned char toie2  : 1;
  unsigned char ocie2  : 1;
} timskRegister;

#define bTIMSK	(*(volatile timskRegister *) &TIMSK)

//---------------------------------------------------------
//--- Interrupt control -----------------------------------
//---------------------------------------------------------

typedef struct
{
  unsigned char ivce   : 1;
  unsigned char ivsel  : 1;
  unsigned char unused : 3;
  unsigned char int2   : 1;
  unsigned char int0   : 1;
  unsigned char int1   : 1;
} gicrRegister;

#define bGICR	(*(volatile gicrRegister *) &GICR)


//---------------------------------------------------------
//--- Timer/Counter0 Output Compare Register --------------
//---------------------------------------------------------

//---------------------------------------------------------
//--- Stack Pointer and Status REGister -------------------
//---------------------------------------------------------



#endif
