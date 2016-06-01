#include <util/delay.h>
#include "spi.h"


//===========================================================================
//=== NIVÅ 1 funktioner =====================================================
//===========================================================================

/**
 * Init of software SPI bus.
 */
void spi_init()
{
	SPI_DDR.si  =1;
	SPI_DDR.clk =1;
	SPI_DDR.cs_n=1;
	SPI_DDR.so  =0;


	

	SPI_PORT.si   =0;
	SPI_PORT.clk  =0;
	SPI_PORT.cs_n =1;
}

/**
 * Set chip select signal.
 */
void spi_cs_n(int value)
{
	SPI_PORT.cs_n = value;
	_delay_us(1);
}

/**
 * Clock pulse generation.
 */
void spi_clock_pulse()
{
	SPI_PORT.clk = 0;
	_delay_us(1);
	SPI_PORT.clk = 1;
	_delay_us(1);
}

/**
 * Clock set to 1
 */
void spi_clock_1(void)
{
	SPI_PORT.clk = 1;
	_delay_us(1);
}


/**
 * Clock set to 0
 */
void spi_clock_0(void)
{
	SPI_PORT.clk = 0;
	_delay_us(1);
}

