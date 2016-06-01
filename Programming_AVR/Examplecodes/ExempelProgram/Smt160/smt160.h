/*
* smt160.h
*
* Created: 2/10/2015 8:55:47 PM
* Author: Kjell
*/


#ifndef __SMT160_H__
#define __SMT160_H__

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "io_bit_fields.h"


class smt160
{
	public:
	enum class Dx
	{
		D0=0x01,
		D1=0x02,
		D2=0x04,
		D3=0x08,
		D4=0x10,
		D5=0x20,
		D6=0x40,
		D7=0x80
	};
	
	enum class MeasurementAlgorithm
	{
		SoftwareOnePeriod,
		SoftWareMultiplePeriods,
		HardwareTimer1,
		HardwareIsrTimer1Capture,
		InlineAssembler
	};
	
	public:
	struct isr_timer1
	{
		isr_timer1()
		{
			this->counter=0;
			this->Tone = 0;
			this->Tzero = 0;
			this->nf=0;
			this->pf=0;
		}
		
		unsigned int Tone;
		unsigned int Tzero;
		unsigned int nf;
		unsigned int pf;
		unsigned int counter;
	};
	
	static isr_timer1 it1;

	static void isr_timer1_input_capture(isr_timer1 *it);
	
	char *get_str_isr_timer1_capture()
	{
		sprintf(this->str_temp,"%6u %d",it1.counter, (int) this->measurementAlgorithm);
		return this->str_temp;
	}
	
	private:

	//Attribute characteristic variables
	MeasurementAlgorithm measurementAlgorithm;
	
	volatile unsigned char *pin;
	volatile unsigned char bit_mask;
	volatile unsigned char bit_no;

	//Help variables
	volatile unsigned int n;
	volatile unsigned int ones;
	volatile unsigned int zeros;
	float temp;
	char str_temp[24];
	//functions
	public:
	smt160();
	smt160(char hw_timer);
	smt160(MeasurementAlgorithm ma, volatile unsigned char *pin, volatile unsigned char bit_mask, volatile unsigned char bit_no );
	float temperature();
	
	char *get_temperature();
	unsigned int get_n() { return n; }
	unsigned int get_ones() { return ones; }
	unsigned int get_zeros() { return zeros; }
	
	~smt160();
	protected:
	
private:
	void read_sw_one_period();
	void read_sw_multiple_periods();
	void read_hw_timer();
	void read_hw_timer_isr();
	char mask2number(char mask);
	smt160( const smt160 &c );
	smt160& operator=( const smt160 &c );

}; //smt160

#endif //__SMT160_H__
