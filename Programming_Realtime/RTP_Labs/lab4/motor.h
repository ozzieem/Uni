#pragma once

#include <stdio.h>
#include "pwm.h"
#include "piodirect.h"
#include "motor_leds.h"

typedef enum
{
	RIGHT,
	LEFT
} MotorSide;

typedef enum
{
	NEUTRAL,
	TWENTY_FIVE,
	FIFTY,
	SEVENTY_FIVE,
	HUNDRED,
	REVERSE,
	EMERGENCY_STOP
} MotorStates;

typedef enum
{
	RIGHT_ACTIVE,
	LEFT_ACTIVE,
	BOTH_ACTIVE
} ActiveMotors;

typedef struct
{
	MotorSide side;
	GPIO direction_pin_fwd;
	GPIO direction_pin_back;
	PWM pwm_pin;
} Motor;

ActiveMotors activeMotor = BOTH_ACTIVE;
MotorStates motorState = NEUTRAL;

void motor_update();
void motor_led_decider(float speed);
char motor_direction(GPIO* button);
void motor_activate(Motor* motor, float speed, int direction);
void motor_run(Motor* motor, float speed);
void motor_create(Motor* motor, enum Pin forward_pin, enum Pin back_pin, enum Pin speed_pin, MotorSide side);
void motor_destroy(Motor* motor);
void motor_speed(Motor* motor, int emergency_break, float speed);

