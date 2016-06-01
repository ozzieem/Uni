#include <util/delay.h>
#include "wire3.h"

/*
	Presentation
	Lökmodell:
	      Nivå 0: Hårdvaran i AVR plus anslutna chip  t.ex. DS1620
		  			WIRE3_PORT av typen wire3_pins
					WIRE3_DDR  av typen wire3_pins
					WIRE3_PIN  av typen wire3_pins
		  Nivå 1: Bussignaler och funktioner som arbetar mot dessa.
		  			wire3_init
					wire3_rst_0
					wire3_rst_1
					wire3_clock_pulse
					wire3_clock_0
					wire3_clock_1
		  Nivå 2: Skriving och läsning 
		  			wire3_command
					wire3_write8
					wire3_write9
		  			wire3_read9
		  Nivå 3: Applikationspecifika funktioner
		  		  DS1620
				  DS1307
 */


//===========================================================================
//=== NIVÅ 1 funktioner =====================================================
//===========================================================================

/**
 * Init of 3 WIRE port on the AVR.
 * \param n_rst Numbers of RST-signals to activate.
 */
void wire3_init(int n_rst)
{
	WIRE3_DDR.dq  =1;
	WIRE3_DDR.clk =1;

	if ( n_rst >= 1 ) WIRE3_DDR.rst0=1;
	if ( n_rst >= 2 ) WIRE3_DDR.rst1=1;
	if ( n_rst >= 3 ) WIRE3_DDR.rst2=1;
	if ( n_rst >= 4 ) WIRE3_DDR.rst3=1;
	if ( n_rst >= 5 ) WIRE3_DDR.rst4=1;
	if ( n_rst >= 6 ) WIRE3_DDR.rst5=1;

	WIRE3_PORT.dq  =0;
	WIRE3_PORT.clk =0;

	if ( n_rst >= 1 ) WIRE3_PORT.rst0=0;
	if ( n_rst >= 2 ) WIRE3_PORT.rst1=0;
	if ( n_rst >= 3 ) WIRE3_PORT.rst2=0;
	if ( n_rst >= 4 ) WIRE3_PORT.rst3=0;
	if ( n_rst >= 5 ) WIRE3_PORT.rst4=0;
	if ( n_rst >= 6 ) WIRE3_PORT.rst5=0;


}

/**
 * RST signal is set to 0.
 */
void wire3_rst_0(int no)
{
	switch ( no )
	{
		case 0: WIRE3_PORT.rst0=0; break;
		case 1: WIRE3_PORT.rst1=0; break;
		case 2: WIRE3_PORT.rst2=0; break;
		case 3: WIRE3_PORT.rst3=0; break;
		case 4: WIRE3_PORT.rst4=0; break;
		case 5: WIRE3_PORT.rst5=0; break;
	}
}

/**
 * RST signal is set to 1
 */
void wire3_rst_1(int no)
{
	wire3_clock_0(); //DS1302 needs this
	_delay_us(5);
	switch ( no )
	{
		case 0: WIRE3_PORT.rst0=1; break;
		case 1: WIRE3_PORT.rst1=1; break;
		case 2: WIRE3_PORT.rst2=1; break;
		case 3: WIRE3_PORT.rst3=1; break;
		case 4: WIRE3_PORT.rst4=1; break;
		case 5: WIRE3_PORT.rst5=1; break;
	}
}


/**
 * Clock pulse generation.
 */
void wire3_clock_pulse()
{
	WIRE3_PORT.clk = 0;
	_delay_us(1);
	WIRE3_PORT.clk = 1;
	_delay_us(1);
}

/**
 * Clock set to 1
 */
void wire3_clock_1(void)
{
	WIRE3_PORT.clk = 1;
	_delay_us(1);
}


/**
 * Clock set to 0
 */
void wire3_clock_0(void)
{
	WIRE3_PORT.clk = 0;
	_delay_us(1);
}


//===========================================================================
//=== NIVÅ 2 funktioner =====================================================
//===========================================================================

/**
 * Write command
 */
void wire3_command(unsigned char command)
{

	int i;

	WIRE3_DDR.dq=1;

	for ( i=0; i<8; i++)
	{
		WIRE3_PORT.dq = ((command & 1) != 0);
		command = command >> 1;
		wire3_clock_pulse();
	}
}


/**
 * Write 8 bits data
 */
void wire3_write8(unsigned char data)
{

	int i;

	WIRE3_DDR.dq=1;

	for ( i=0; i<8; i++)
	{
		WIRE3_PORT.dq = ((data & 1) != 0);
		data = data >> 1;
		wire3_clock_pulse();
	}
}


/**
 * Write 9 bits data
 */
void wire3_write9(unsigned int data)
{

	int i;

	WIRE3_DDR.dq=1;

	for ( i=0; i<9; i++)
	{
		WIRE3_PORT.dq = ((data & 1) != 0);
		data = data >> 1;
		wire3_clock_pulse();
	}
}


/**
 * Read 9 bits data
 */
void wire3_read9(unsigned int *data_out)
{
	unsigned int data=0;
	int i;

	WIRE3_DDR.dq=0;
	//WIRE3_PORT.dq=0; //Enable pull up

	for ( i=0; i<9; i++)
	{
		wire3_clock_0();
		data = data >> 1;
		if ( WIRE3_PIN.dq )
			data = data | 0b100000000;
		wire3_clock_1();
	}

	*data_out = data;
}

/**
 * Read 8 data bits
 */
unsigned char  wire3_read8(void)
{
	unsigned int data=0;
	int i;

	WIRE3_DDR.dq=0;
	//WIRE3_PORT.dq=0; //Enable pull up

	for ( i=0; i<8; i++)
	{
		wire3_clock_0();
		data = data >> 1;
		if ( WIRE3_PIN.dq )
			data = data | 0b10000000;
		wire3_clock_1();
	}

	return data;
}




