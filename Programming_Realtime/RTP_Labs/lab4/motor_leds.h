#pragma once
#include "pwm.h"

typedef enum
{
	NONE,
	GREEN_BREATHE,
	GREEN_TWO,
	GREEN_FOUR,
	GREEN_TEN,
	GREEN_TWENTY,
	RED_BLINK,
	YELLOW_ONE_BLINK,
	YELLOW_TWO_BLINK
} MotorLedStates;

typedef struct
{
	PWM red_led;
	PWM green_led;
	PWM yellow_led_one;
	PWM yellow_led_two;
} MotorLed;

MotorLedStates motorLedState = NONE;

void motor_led_breathing(PWM led);

void motor_led_blink(PWM led, float nBlink);

void motor_led_create(MotorLed* this,
                      enum Pin green_led,
                      enum Pin red_led,
                      enum Pin yellow_led_one,
                      enum Pin yellow_led_two);

void motor_led_destroy(MotorLed* this);

