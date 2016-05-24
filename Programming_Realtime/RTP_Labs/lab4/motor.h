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
MotorStates motorState = NEUTRAL, prevMotorState = NEUTRAL;
int emergency_break = 1;

void motor_gear_shift()
{
	if (motorState == HUNDRED || motorState == REVERSE || motorState == EMERGENCY_STOP)
	{
		prevMotorState = motorState;
		motorState = NEUTRAL;
	}
	else
	{
		prevMotorState = motorState;
		motorState++;
	}

	if (activeMotor == RIGHT_ACTIVE || activeMotor == LEFT_ACTIVE)
	{
		activeMotor = BOTH_ACTIVE;
		motorState = prevMotorState;
	}
}

void motor_led_decider(float speed)
{
	switch (activeMotor)
	{
	case RIGHT_ACTIVE:
		motorLedState = YELLOW_ONE_BLINK;
		break;
	case LEFT_ACTIVE:
		motorLedState = YELLOW_TWO_BLINK;
		break;
	case BOTH_ACTIVE:
		{
			switch (motorState)
			{
			case NEUTRAL:
				motorLedState = GREEN_BREATHE;
				break;
			case TWENTY_FIVE:
				motorLedState = GREEN_TWO;
				break;
			case FIFTY:
				motorLedState = GREEN_FOUR;
				break;
			case SEVENTY_FIVE:
				motorLedState = GREEN_TEN;
				break;
			case HUNDRED:
				motorLedState = GREEN_TWENTY;
				break;
			case REVERSE:
				motorLedState = NONE;
				break;
			case EMERGENCY_STOP:
				motorLedState = RED_BLINK;
				break;
			default:
				break;
			}
		}
		break;
	}
}

char motor_direction(GPIO* button)
{
	struct timespec ts1, ts2;
	clock_gettime(0, &ts1);
	clock_gettime(0, &ts2);

	while (!readIn(*button))
	{
		clock_gettime(0, &ts2);

		int diffs = ts2.tv_sec - ts1.tv_sec;
		if (diffs > 2)
			return 's'; // Reverse
	}
	return 'g'; // Accelerate
}

void motor_activate(Motor* motor, float speed, int direction)
{
	if (direction)
	{
		onOff(motor->direction_pin_fwd, ON);
		onOff(motor->direction_pin_back, OFF);
	}
	else
	{
		onOff(motor->direction_pin_fwd, OFF);
		onOff(motor->direction_pin_back, ON);
	}
	pwmPulse(motor->pwm_pin, speed / 100);
}

void motor_run(Motor* motor, float speed)
{
	switch (activeMotor)
	{
	case RIGHT_ACTIVE:
		{
			if (motor->side == RIGHT)
			{
				motor_activate(motor, speed, 1);
			}
			if (motor->side == LEFT)
			{
				motor_activate(motor, 0.0, 1);
			}
		}
		break;
	case LEFT_ACTIVE:
		{
			if (motor->side == LEFT)
			{
				motor_activate(motor, speed, 1);
			}
			if (motor->side == RIGHT)
			{
				motor_activate(motor, 0.0, 1);
			}
		}
		break;
	case BOTH_ACTIVE:
		{
			motor_activate(motor, speed, 1);
		}
		break;
	}
}

void motor_speed(Motor* motor, float speed)
{
	switch (motorState)
	{
	case NEUTRAL:
		{
			speed = 0.0;
			motor_run(motor, speed);
			motor_led_decider(speed);
			break;
		}
	case TWENTY_FIVE:
		{
			speed = 25.0;
			motor_run(motor, speed);
			motor_led_decider(speed);
			emergency_break = 1;
			break;
		}
	case FIFTY:
		{
			speed = 50.0;
			motor_run(motor, speed);
			motor_led_decider(speed);
			break;
		}
	case SEVENTY_FIVE:
		{
			speed = 75.0;
			motor_run(motor, speed);
			motor_led_decider(speed);
			break;
		}
	case HUNDRED:
		{
			speed = 100.0;
			motor_run(motor, speed);
			motor_led_decider(speed);
			break;
		}
	case REVERSE:
		{
			speed = 50.0;
			motor_activate(motor, speed, 0);
			motor_led_decider(speed);
			emergency_break = 1;
			break;
		}
	case EMERGENCY_STOP:
		{
			if (emergency_break)
			{
				for (unsigned i = 0; i < 7; i++)
				{
					motor_activate(motor, 100.0, 0);
				}
				emergency_break = 0;
			}
			motor_led_decider(speed);
			motor_activate(motor, 0.0, 1);
			break;
		}
	default:
		break;
	}
}

void motor_create(Motor* motor, enum Pin forward_pin, enum Pin back_pin, enum Pin speed_pin, MotorSide side)
{
	motor->direction_pin_fwd = create(forward_pin, OUT_PIN);
	motor->direction_pin_back = create(back_pin, OUT_PIN);
	motor->pwm_pin = pwmCreate(speed_pin, 100);
	motor->side = side;
}

void motor_destroy(Motor* motor)
{
	pwmDestroy(motor->pwm_pin);
	destroy(motor->direction_pin_fwd);
	destroy(motor->direction_pin_back);
}