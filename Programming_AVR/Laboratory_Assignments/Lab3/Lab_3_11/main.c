#include <avr/io.h>
#include "TrafficLights.h"

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	Traffic = GoSouth;

	while (1)
	{
		char TrafficOnSouth = !(PINA & 0x01);
		char TrafficOnWest = !(PINA & 0x02);
		switch (Traffic)
		{
			case GoSouth:
			{
				ActivateSouthLane(TrafficOnWest, TrafficOnSouth);

			} break;
			case WaitSouth:
			{
				TransitionSouthToWest();

			} break;
			case GoWest:
			{
				ActivateWestLane(TrafficOnSouth, TrafficOnWest);

			} break;
			case WaitWest:
			{
				TransitionWestToSouth();

			} break;
			default:
			break;
		}
	}
}

