#ifndef _SENSOR_SMT160_H
#define _SENSOR_SMT160_H

#include "help_functions.h"

typedef enum 
  {
    SENSOR_SMT160_D7 = 0x80,
    SENSOR_SMT160_D6 = 0x40,
    SENSOR_SMT160_D5 = 0x20,
    SENSOR_SMT160_D4 = 0x10,
    SENSOR_SMT160_D3 = 0x08,
    SENSOR_SMT160_D2 = 0x04,
    SENSOR_SMT160_D1 = 0x02,
    SENSOR_SMT160_D0 = 0x01
  } sensor_smt160_bit_mask;
  
typedef struct
{
  volatile unsigned char *port; 
  volatile unsigned char *ddr;
  volatile unsigned char *pin;  //PORT in
  unsigned char bit_mask;
  unsigned char unused;
} sensor_smt160;

void sensor_smt160_init(sensor_smt160 *this, 
                        volatile unsigned char *port,
                        unsigned char bit_mask
                       );
                       
float sensor_smt160_read(sensor_smt160 *this);


#endif
