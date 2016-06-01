/* 
* smt160.cpp
*
* Created: 2/10/2015 8:55:47 PM
* Author: Kjell
*/

#include "smt160.h"

smt160::isr_timer1 smt160::it1=smt160::isr_timer1(); //smt160::it1 observera knytningen som statisk medlem / global variabel i klasskontext
                                                     //        it1 vanlig global variabel

void smt160::isr_timer1_input_capture(isr_timer1 *it)
{
	unsigned int icr = ICR1;
	
	if ( bTCCR1B.ices1 )
	{
		if ( it->nf < icr )
			it->Tzero = icr-it->nf;
		else
			it->Tzero =0xFFFF-it->nf+icr;
		it->pf = icr;
		bTCCR1B.ices1=0;
	}
	else
	{
		if ( it->pf < icr )
			it->Tone = icr-it->pf;
		else
			it->Tone =0xFFFF-it->pf+icr;
		it->nf = icr;
		bTCCR1B.ices1=1;
	}
	
	it->counter++;
}


ISR(TIMER1_CAPT_vect)
{
	smt160::isr_timer1_input_capture(&smt160::it1);
}

// default constructor
smt160::smt160()
{
	//this->measurementAlgorithm = MeasurementAlgorithm::SoftwareOnePeriod;
	this->measurementAlgorithm = MeasurementAlgorithm::SoftWareMultiplePeriods;
	this->bit_mask=(volatile unsigned char) Dx::D7;
	this->bit_no = mask2number(this->bit_mask);
	this->pin = &PINB;
} //smt160

smt160::smt160(char hw_timer)
{
	this->measurementAlgorithm = MeasurementAlgorithm::HardwareTimer1;
	this->bit_mask=(volatile unsigned char) Dx::D6;
	this->bit_no = 6;
	this->pin = &PIND;
}

smt160::smt160(MeasurementAlgorithm ma, volatile unsigned char *pin, volatile unsigned char bit_mask, volatile unsigned char bit_no )
{
		this->measurementAlgorithm=ma;
		
		switch(this->measurementAlgorithm)
		{
			case MeasurementAlgorithm::HardwareIsrTimer1Capture:
				bTCCR1B.icnc1=0; //Noise Canceler
				//bSFIOR.psr10=1;
				bTCCR1B.cs1=0b010; //1us med 8MHz
				bTCCR1B.ices1=1; //Input Capture Edge Select 1=PFlanc, 0=NFlanc
				bTIMSK.ticie1=1;
				break;
		}
	
		this->pin=pin;
		this->bit_no = bit_no;
		this->bit_mask = bit_mask;
}

float smt160::temperature()
{
	switch(this->measurementAlgorithm)
	{
		case MeasurementAlgorithm::SoftwareOnePeriod:
			read_sw_one_period();
			break;
		case MeasurementAlgorithm::SoftWareMultiplePeriods:
			read_sw_multiple_periods();
			break;
		case MeasurementAlgorithm::HardwareTimer1:
			read_hw_timer();
			break;
		case MeasurementAlgorithm::HardwareIsrTimer1Capture:
			read_hw_timer_isr();
			break;
		case MeasurementAlgorithm::InlineAssembler:
			break;
	}
	
	float dc = (float) this->ones / (float) this->n;
	
	this->temp = (dc-0.32) / 0.00470;
	
	return this->temp;
}

void smt160::read_sw_one_period()
{
	char o;
	char nn;
	
	this->n=0;
	this->ones=0;
	this->zeros=0;
	
	o = nn = (*this->pin & this->bit_mask) != 0;
	
	while ( !(!o && nn) )
	{
		o = nn;
		nn = (*this->pin & this->bit_mask) != 0;
	} 
	
	while ( (*this->pin & this->bit_mask) != 0)
	{
		this->ones++;
		//_delay_us(1);
	}
	
	while ( (*this->pin & this->bit_mask) == 0)
	{
		this->zeros++;
		//_delay_us(1);
	}
	
	this->n = this->ones+this->zeros;
}

char *smt160::get_temperature()
{
	this->temp = this->temperature();
	int t = (int)((temp+0.05f) *10);
	int ipart = t / 10;
	int dpart = t % 10;
	//sprintf(this->str_temp,"t=%d.%d", ipart, dpart);
	sprintf(this->str_temp,"t=%8.1f", this->temp);
	
	return this->str_temp;
}

void smt160::read_sw_multiple_periods()
{
	const unsigned int N=50000;
	this->n=N;
	this->ones=0;
	this->zeros=0;

	while ( this->n-- > 0)
	{
		ones += ((*this->pin & this->bit_mask) >> this->bit_no);
		_delay_us(3); //-> 150ms -> 150 perioder på 1kHz fel 0.5/150  
	}	
	
	this->n=N;
}

void smt160::read_hw_timer_isr()
{
	asm("   CLI   ");
	this->ones = it1.Tone;
	this->zeros= it1.Tzero;
	asm("   SEI   ");
	this->n = this->ones+this->zeros;
}


void smt160::read_hw_timer()
{
	bTCCR1B.icnc1=0; //Noise Canceler
	
	//bSFIOR.psr10=1;
	bTCCR1B.cs1=0b010; //1us med 8MHz
	
	bTCCR1B.ices1=1; //Input Capture Edge Select 1=PFlanc, 0=NFlanc
	bTIFR.icf1=1; //Clear flag
	while ( !bTIFR.icf1 )
		_delay_us(1);
	
	TCNT1=0;
	
	bTCCR1B.ices1=0; //Input Capture Edge Select 1=PFlanc, 0=NFlanc 
	bTIFR.icf1=1; //Clear flag
	while ( !bTIFR.icf1 )
		_delay_us(1);
	this->ones = ICR1;
	
	bTCCR1B.ices1=1; //Input Capture Edge Select 1=PFlanc, 0=NFlanc
	bTIFR.icf1=1; //Clear flag
	while ( !bTIFR.icf1 )
		_delay_us(1);
	this->n=ICR1;
	
	this->zeros= this->n-this->ones;
}


char smt160::mask2number(char mask)
{
	char no=0;
	
	if ( mask == 0)
		return -1;
	
	while ( (mask & 0x01) == 0 )
	{
		no++;
		mask = mask >> 1;
	}
	
	return no;
}

// default destructor
smt160::~smt160()
{
} //~smt160
