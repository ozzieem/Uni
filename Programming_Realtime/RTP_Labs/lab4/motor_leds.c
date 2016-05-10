#include "motor_leds.h"

void motor_led_breathing(PWM led)
{
	unsigned const cycles = 100;
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

