#include <util/delay.h>
#include "spi.h"
#include "eeprom.h"

/**
 *   Start of write phase, , USED INTERNAL/PRIVATE
 */
void static eeprom_write_start(unsigned int address)
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	unsigned char command=0b00000010;
	int i;

	eeprom_write_enable();

	spi_cs_n(0);

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((command & 0x80) != 0);
		command = command << 1;
		spi_clock_pulse();
	}

	for ( i=0; i<16; i++)
	{
		SPI_PORT.si = ((address & 0x8000) != 0);
		address = address << 1;
		spi_clock_pulse();
	}
}

/**
 * Write one byte, USED INTERNAL/PRIVATE
 */
void static eeprom_write_byte(unsigned char data)
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	int i;

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((data & 0x80) != 0);
		data = data << 1;
		spi_clock_pulse();
	}
}


/**
 * Write command
 */
void eeprom_write_enable()
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	unsigned char command=0b00000110;
	int i;

	spi_cs_n(0);

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((command & 0x80) != 0);
		command = command << 1;
		spi_clock_pulse();
	}

	spi_cs_n(1);
}

/**
 * Write command
 */
void eeprom_write(unsigned int address, unsigned char data)
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	unsigned char command=0b00000010;
	int i;

	eeprom_write_enable();

	spi_cs_n(0);

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((command & 0x80) != 0);
		command = command << 1;
		spi_clock_pulse();
	}

	for ( i=0; i<16; i++)
	{
		SPI_PORT.si = ((address & 0x8000) != 0);
		address = address << 1;
		spi_clock_pulse();
	}

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((data & 0x80) != 0);
		data = data << 1;
		spi_clock_pulse();
	}

	spi_cs_n(1);
}


/**
 * Write vector
 */
void eeprom_write_vector(unsigned int address, unsigned char *data, int n)
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	int j;

	eeprom_write_enable();

	eeprom_write_start(address);

	for ( j=0; j<n; j++)
	{
		eeprom_write_byte(*data);

		if ( (address & 0xF) == 0xF )
		{
			spi_cs_n(1);
			address = address+1;
			_delay_ms(5);
			eeprom_write_start(address);
		}
		else
		{
			address = address+1;
		}
		data = data +1;
	}

	spi_cs_n(1);
}


/**
 * Read command
 */
unsigned char eeprom_read(unsigned int address)
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	unsigned char command=0b00000011;
	unsigned char data=0;
	int i;

	spi_cs_n(0);

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((command & 0x80) != 0);
		command = command << 1;
		spi_clock_pulse();
	}

	for ( i=0; i<16; i++)
	{
		SPI_PORT.si = ((address & 0x8000) != 0);
		address = address << 1;
		spi_clock_pulse();
	}

	for ( i=0; i<8; i++)
	{
		spi_clock_0();
		data = data << 1;
		if ( SPI_PIN.so )
			data = data | 0b000000001;
		spi_clock_1();;
	}

	spi_cs_n(1);

	return data;
}


/**
 * Read status register
 */
unsigned char eeprom_read_sr()
{
	SPI_DDR.si  =1; //Shared pin with wire3-buss. Wire3 operations can set this to zero
	unsigned char command=0b00000101;
	unsigned char data=0;
	int i;

	spi_cs_n(0);

	for ( i=0; i<8; i++)
	{
		SPI_PORT.si = ((command & 0x80) != 0);
		command = command << 1;
		spi_clock_pulse();
	}

	for ( i=0; i<8; i++)
	{
		spi_clock_0();
		data = data << 1;
		_delay_us(1);
		if ( SPI_PIN.so )
			data = data | 0b000000001;
		spi_clock_1();;
	}

	spi_cs_n(1);

	return data;
}



