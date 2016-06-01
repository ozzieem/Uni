#ifndef TRAFFICLIGHTS_H_
#define TRAFFICLIGHTS_H_

enum {
	GoSouth,
	WaitSouth,
	GoWest,
	WaitWest
} Traffic;

struct TrafficLights {
	char Red;
	char Yellow;
	char Green;
};

struct TrafficLights SouthTrafficLight = {0xFF - 0x20, 0xFF - 0x40, 0xFF - 0x80};
struct TrafficLights WestTrafficLight = {0xFF - 0x10, 0xFF - 0x08, 0xFF - 0x04};

// How to make this work?
//#define SouthLight (*(SouthTrafficLight)* &PORTB)
//#define WestLight (*(WestTrafficLight)* &PORTB)

int oneSec = 1000, threeSec = 3000;

void ActivateSouthLane(char TrafficOnWest, char TrafficOnSouth)
{
	PORTB = SouthTrafficLight.Green;
	PORTB += WestTrafficLight.Red;
	if(TrafficOnWest && !TrafficOnSouth)
	{
		wait_milliseconds(oneSec);
		Traffic = WaitSouth;
	}
	if(TrafficOnWest && TrafficOnSouth)
	{
		wait_milliseconds(threeSec);
		Traffic = WaitSouth;
	}
}

void TransitionSouthToWest()
{
	PORTB = WestTrafficLight.Red;
	PORTB += WestTrafficLight.Yellow;
	PORTB += SouthTrafficLight.Yellow + 1;
	wait_milliseconds(oneSec);
	Traffic = GoWest;
}

void ActivateWestLane(char TrafficOnSouth, char TrafficOnWest)
{
	PORTB = WestTrafficLight.Green;
	PORTB += SouthTrafficLight.Red - 1;
	if(TrafficOnSouth && !TrafficOnWest)
	{
		wait_milliseconds(oneSec);
		Traffic = WaitWest;
	}
	if(TrafficOnSouth && TrafficOnWest)
	{
		wait_milliseconds(threeSec);
		Traffic = WaitWest;
	}
}

void TransitionWestToSouth()
{
	PORTB = WestTrafficLight.Yellow;
	PORTB += SouthTrafficLight.Red;
	PORTB += SouthTrafficLight.Yellow;
	wait_milliseconds(oneSec);
	Traffic = GoSouth;
}

#endif /* TRAFFICLIGHTS_H_ */