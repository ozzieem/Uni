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

void motor_led_breathe(PWM led)
{
	unsigned const cycles = 50;
	for (float i = 0; i < cycles; i++)
	{
		pwmPulse(led, i / 100);
	}
	for (float i = cycles; i > 0; i--)
	{
		pwmPulse(led, i / 100);
	}
}

void motor_led_blink(PWM led, float nBlink)
{
	led.frequency = nBlink;
	pwmPulse(led, 0.5);
}

void motor_led_run(MotorLed* this)
{
	switch (motorLedState)
	{
	case NONE:
		{
			motor_led_blink(this->green_led, 0);
			break;
		}
	case GREEN_BREATHE:
		{
			motor_led_breathe(this->green_led);
			break;
		}
	case GREEN_TWO:
		{
			motor_led_blink(this->green_led, 2.0);
			break;
		}
	case GREEN_FOUR:
		{
			motor_led_blink(this->green_led, 4.0);
			break;
		}
	case GREEN_TEN:
		{
			motor_led_blink(this->green_led, 10.0);
			break;
		}
	case GREEN_TWENTY:
		{
			motor_led_blink(this->green_led, 20.0);
			break;
		}
	case YELLOW_ONE_BLINK:
		{
			motor_led_blink(this->yellow_led_one, 2.0);
			break;
		}
	case YELLOW_TWO_BLINK:
		{
			motor_led_blink(this->yellow_led_two, 2.0);
			break;
		}
	case RED_BLINK:
		{
			motor_led_blink(this->red_led, 10.0);
			break;
		}
	default:
		break;
	}
}

void motor_led_create(MotorLed* this, enum Pin green_led, enum Pin red_led, enum Pin yellow_led_one, enum Pin yellow_led_two)
{
	this->green_led = pwmCreate(green_led, 100);
	this->red_led = pwmCreate(red_led, 100);
	this->yellow_led_one = pwmCreate(yellow_led_one, 100);
	this->yellow_led_two = pwmCreate(yellow_led_two, 100);
}

void motor_led_destroy(MotorLed* this)
{
	pwmDestroy(this->red_led);
	pwmDestroy(this->green_led);
	pwmDestroy(this->yellow_led_one);
	pwmDestroy(this->yellow_led_two);
}
