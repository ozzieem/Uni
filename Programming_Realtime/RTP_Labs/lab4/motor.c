#include "motor.h"

void motor_update()
{
	if (motorState == HUNDRED || motorState == REVERSE || motorState == EMERGENCY_STOP)
	{
		motorState = NEUTRAL;
	}
	else
	{
		motorState++;
	}

	if (activeMotor == RIGHT_ACTIVE || activeMotor == LEFT_ACTIVE)
	{
		activeMotor = BOTH_ACTIVE;
		motorState = TWENTY_FIVE;
	}
}

void motor_led_decider(float speed)
{
	switch (activeMotor)
	{
	case RIGHT_ACTIVE:
		{
			motorLedState = YELLOW_ONE_BLINK;
		}
		break;
	case LEFT_ACTIVE:
		{
			motorLedState = YELLOW_TWO_BLINK;
		}
		break;
	case BOTH_ACTIVE:
		{
			if (speed == 25.0)
			{
				motorLedState = GREEN_TWO;
			}
			else if (speed == 50.0)
			{
				motorLedState = GREEN_FOUR;
			}
			else if (speed == 75.0)
			{
				motorLedState = GREEN_TEN;
			}
			else if (speed == 100.0)
			{
				motorLedState = GREEN_TWENTY;
			}
			else
			{
				motorLedState = GREEN_BREATHE;
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

void motor_speed(Motor* motor, int emergency_break, float speed)
{
	switch (motorState)
	{
	case NEUTRAL:
		{
			speed = 0.0;
			motor_activate(motor, speed, 1);
			motorLedState = GREEN_BREATHE;
			emergency_break = 1;
			break;
		}
	case TWENTY_FIVE:
		{
			speed = 25.0;
			motor_run(motor, speed);
			motor_led_decider(speed);
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
			motorLedState = NONE;
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
			motor_activate(motor, 0.0, 1);
			motorLedState = RED_BLINK;
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

