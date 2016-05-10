#include <stdio.h>
#include <pThread.h>
#include <time.h>
#include "piodirect.h"
#include "pwm.h"

#if 0

typedef struct
{
	int led;
	int brightness;
} Light;

pthread_mutex_t mutex;
Light light;

void run_led(PWM* pwm, int led_number)
{
	float led_brightness = 0;
	while (1)
	{
		pthread_mutex_trylock(&mutex);
		if (light.led == led_number)
			led_brightness = (float)light.brightness / 100;
		pthread_mutex_unlock(&mutex);

		pwmPulse(*pwm, led_brightness);
	}
}

void* t1_function(GPIO* output)
{
	PWM pwm = pwmCreate(output->pin, 100);
	run_led(&pwm, 1);
}

void* t2_function(GPIO* output)
{
	PWM pwm = pwmCreate(output->pin, 100);
	run_led(&pwm, 2);
}

void* t3_function()
{
	while (1)
	{
		Light temp_light;
		printf("Enter led number and brightness: ");
		char trash;
		scanf("%d%c%d", &temp_light.led, &trash, &temp_light.brightness);
		if (temp_light.led < 1 || temp_light.led == 0)
		{
			break;
		}
		else if (temp_light.led > 2)
		{
			printf("Enter 1 or 2 for led choice. 0 exits.\n");
		}
		else
		{
			pthread_mutex_trylock(&mutex);
			light = temp_light;
			pthread_mutex_unlock(&mutex);
		}
	}
}

int main()
{
	gpioSetup();
	GPIO led_4, led_5;
	led_4 = create(_4, OUT_PIN);
	led_5 = create(_5, OUT_PIN);

	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, t1_function, &led_4);
	pthread_create(&t2, NULL, t2_function, &led_5);
	pthread_create(&t3, NULL, t3_function, NULL);

	pthread_join(t3, NULL);
	pthread_cancel(t1);
	pthread_cancel(t2);

	destroy(led_4);
	destroy(led_5);
}
#endif // 0