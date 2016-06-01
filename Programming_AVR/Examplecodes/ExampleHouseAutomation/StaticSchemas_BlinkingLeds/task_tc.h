#ifndef _TASK_TC_H
#define _TASK_TC_H
#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

#include "io_do.h"
#include "io_di.h"
#include "lcd4.h"
#include "counter.h"
#include "relay.h"
#include "sensor_smt160.h"
#include "help_functions.h"

typedef enum
{
  TASK_TC_D7=0x80,
  TASK_TC_D6=0x40,
  TASK_TC_D5=0x20,
  TASK_TC_D4=0x10,
  TASK_TC_D3=0x08,
  TASK_TC_D2=0x04,
  TASK_TC_D1=0x02,
  TASK_TC_D0=0x01,
  
}task_tc_enums;

typedef struct
{
  char s1[32];
  char s2[16];
  char s3[16];
  
  sensor_smt160  y_temp;
  io_di          r_inc;
  io_di          r_dec;
  counter        r_temp;
  io_do          u_heater;
  lcd4           display;
  relay          controller;
  
  int y; //Measured temperature
  int r; //Reference temperature
  int e; //Error in temperature, e=r-y
  int u; //Control signal (1/0)
  
} task_tc;

void task_tc_init(task_tc *this, 
                  volatile unsigned char *port,
                  unsigned char bit_mask_sensor,
                  unsigned char bit_mask_actuator,
                  unsigned char bit_mask_incr,
                  unsigned char bit_mask_decr
                  );

void task_tc_main( task_tc *this );

#endif

