#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

typedef struct
{
	int volts;
} Potentiometer;

void potentiometer_init(Potentiometer*);
int potentiometer_getvolts(Potentiometer*);
void potentiometer_setvolts(Potentiometer*, int);

#endif /* POTENTIOMETER_H_ */