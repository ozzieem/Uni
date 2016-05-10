#include <pThread.h>
#include <mqueue.h>
#include <time.h>
#include "motor.h"
#include "motor_leds.h"
#include <stdio.h>

#define WAIT_TIME 100000000
#define QUEUE_NAME "/myqueue"
#define MESSAGE_SIZE 20

void busy_wait(const long);

void* motor_led_thread(MotorLed* this)
{
	while (1)
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
				motor_led_breathing(this->green_led);
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
			}
			break;
		case YELLOW_TWO_BLINK:
			{
				motor_led_blink(this->yellow_led_two, 2.0);
			}
			break;
		case RED_BLINK:
			{
				motor_led_blink(this->red_led, 10.0);
			}
			break;
		default:
			break;
		}
	}
}

void* motor_thread(Motor* motor)
{
	int emergency_break = 1;
	float speed = 0;

	while (1)
	{
		motor_speed(motor, emergency_break, speed);
	}
}

void* motor_manager_thread()
{
	mqd_t q2;
	struct mq_attr q1Attr;
	unsigned int prio;
	q1Attr.mq_msgsize = MESSAGE_SIZE;
	q1Attr.mq_maxmsg = 50;
	q2 = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0700, &q1Attr);

	char message;
	char prev_message = ' ';
	int active = 1;

	while (active)
	{
		mq_receive(q2, &message, MESSAGE_SIZE, &prio);
		switch (message)
		{
		case 'g': // GREEN - MOTORSPEED CONTROL
			{
				if (prev_message == 's') // Prevent reverse from instantly stop after button-release
					break;
				motor_update();
			}
			break;
		case 's': // REVERSE
			{
				motorState = REVERSE;
			}
			break;
		case 'r': // RED - EMERGENCY STOP
			{
				if (prev_message == 'r')
					active = 0; // Breaks out of loop and shuts down program
				motorState = EMERGENCY_STOP;
			}
			break;
		case 'w': // WHITE - RIGHT
			{
				activeMotor = RIGHT_ACTIVE;
			}
			break;
		case 'b': // BLUE - LEFT
			{
				activeMotor = LEFT_ACTIVE;
			}
			break;
		default:
			break;
		}
		prev_message = message;
	}
}

void* input_thread()
{
	mqd_t mq;
	struct mq_attr q1Attr;
	q1Attr.mq_msgsize = MESSAGE_SIZE;
	q1Attr.mq_maxmsg = 50;
	mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0700, &q1Attr);

	char message = ' ';
	char old_message = ' ';
	GPIO green, blue, red, white;

	green = createWithPullUpDown(_20, PUD_UP);
	white = createWithPullUpDown(_12, PUD_UP);
	blue = createWithPullUpDown(_21, PUD_UP);
	red = createWithPullUpDown(_16, PUD_UP);

	struct timespec ts1, ts2;
	ts1.tv_sec = 0;
	ts1.tv_nsec = WAIT_TIME;

	while (1)
	{
		if (!readIn(green))
		{
			message = motor_direction(&green);
		}
		else if (!readIn(blue))
		{
			message = 'b';
		}
		else if (!readIn(white))
		{
			message = 'w';
		}
		else if (!readIn(red))
		{
			message = 'r';
		}
		if (message != old_message)
		{
			if (message == 'r')
			{
				mq_send(mq, &message, MESSAGE_SIZE, 10);
			}
			else
			{
				mq_send(mq, &message, MESSAGE_SIZE, 0);
			}
			printf("%c", message); // DEBUG
			if (message == 'g' || message == 's' || message == 'r')
				message = 'i'; // Placeholder char for making multiple green pressing possible
			while (!readIn(red))
			{ /*Busy-wait*/
			}
		}
		old_message = message;
		nanosleep(&ts1, &ts2);
	}
}

int main()
{
	gpioSetup();
	mq_unlink(QUEUE_NAME);

	MotorLed motor_led;
	motor_led_create(&motor_led, _5, _4, _6, _13);

	Motor motor_right, motor_left;
	motor_create(&motor_right, _22, _27, _17, RIGHT);
	motor_create(&motor_left, _23, _24, _18, LEFT);

	//	struct sched_param sp1, sp2, sp3, sp4, sp5;
	//	sp1.__sched_priority = 40;
	//	sp2.__sched_priority = 20;
	//	sp3.__sched_priority = 10;
	//	sp4.__sched_priority = 5;

	pthread_t motor_right_t, motor_left_t, input_t, manager_t, motor_led_t;

	pthread_create(&input_t, NULL, input_thread, NULL);
	//	pthread_setschedparam(input_t, SCHED_FIFO, &sp1);

	pthread_create(&manager_t, NULL, motor_manager_thread, NULL);
	//	pthread_setschedparam(input_t, SCHED_FIFO, &sp2);

	pthread_create(&motor_left_t, NULL, motor_thread, &motor_left);
	//	pthread_setschedparam(motor_left_t, SCHED_FIFO, &sp3);

	pthread_create(&motor_right_t, NULL, motor_thread, &motor_right);
	//	pthread_setschedparam(motor_left_t, SCHED_FIFO, &sp3);

	pthread_create(&motor_led_t, NULL, motor_led_thread, &motor_led);
	//	pthread_setschedparam(motor_left_t, SCHED_FIFO, &sp4);

	//	pthread_join(input_t, NULL);
	pthread_join(manager_t, NULL);

	motor_destroy(&motor_right);
	motor_destroy(&motor_left);
	motor_led_destroy(&motor_led);

	pthread_cancel(motor_right_t);
	pthread_cancel(motor_left_t);
	pthread_cancel(input_t);
	pthread_cancel(manager_t);
	pthread_cancel(motor_led_t);

	mq_unlink(QUEUE_NAME);
}

void busy_wait(const long nsec)
{
	long diffns = 0;
	int diffs = 0;

	struct timespec ts1, ts2;
	clock_gettime(0, &ts1);
	clock_gettime(0, &ts2);

	while (diffns < nsec)
	{
		clock_gettime(0, &ts2);
		diffns = ts2.tv_nsec - ts1.tv_nsec;
		diffs = ts2.tv_sec - ts1.tv_sec;
		diffns += diffs * 1000000000;
	}
}

