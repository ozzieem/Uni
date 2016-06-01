#include "Potentiometer.h"

void potentiometer_init(Potentiometer* pm)
{
	pm->volts = 0;
}

int potentiometer_getvolts(Potentiometer* pm)
{
	return pm->volts;
}

void potentiometer_setvolts(Potentiometer* pm, int volts)
{
	pm->volts = volts / 200;
}