#include <avr/io.h>

enum
{
	Closed,
	Open,
	PushKey,
	ReleaseKey
} Locker;

void CheckIfWrongCombination(int*, char, int*, char, char, int*, const int);
int CheckTrueCombination(int, char, int*, char, char );

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;

	const int timeout = 20;
	int time_counter = 0;
	int iCode = 0;
	int code[6] = {1,2,3,1,1,2};
	Locker = Closed;

	while (1)
	{
		char eventKey1 = !(PINA & 0x80);
		char eventKey2 = !(PINA & 0x40);
		char eventKey3 = !(PINA & 0x20);
		PORTB = PINA;

		switch(Locker)
		{
			case Closed:
			{
				if((eventKey1 && (code[iCode] == 1))
				|| (eventKey2 && (code[iCode] == 2))
				|| (eventKey3 && (code[iCode] == 3)))
				{
					iCode++;
					Locker = PushKey;
				}
				PORTB = 254;
			} break;	// Closed
			case Open:
			{
				if(time_counter > timeout)
				{
					Locker = Closed;
					time_counter = 0;
					iCode = 0;
				}

				time_counter++;
				PORTB = 255 - time_counter;	//20 sec
				wait_milliseconds(500);
			} break;	// Open
			case PushKey:
			{
				if(!eventKey1
				&& !eventKey2
				&& !eventKey3)
				{
					Locker = ReleaseKey;
					time_counter++;
				}
				if(iCode >= 6)
				{
					Locker = Open;
					time_counter = 0;
				}
			} break;	// PushKey
			case ReleaseKey:
			{
				CheckIfWrongCombination(
				&iCode, eventKey1, code,
				eventKey2, eventKey3,
				&time_counter, timeout
				);

				iCode = CheckTrueCombination(
				iCode, eventKey1, code,
				eventKey2, eventKey3
				);

				PORTB = 254;
			} break;	// ReleaseKey
			default:
			break;
		}	// Switch
		wait_milliseconds(50);
	}
}

void CheckIfWrongCombination(
	int *iCode, char eventKey1, int * code,
	char eventKey2, char eventKey3, 
	int *time_counter, const int timeout)
{
	if (*iCode < 3)
	{
		if((eventKey1 && (code[*iCode] != 1))
		|| (eventKey2 && (code[*iCode] != 2))
		|| (eventKey3 && (code[*iCode] != 3))
		|| *time_counter > timeout)
		{
			Locker = Closed;
			*time_counter = 0;
			*iCode = 0;
		}
		else
		{
			if ((eventKey1 && (code[*iCode] != 1))
			|| (eventKey2 && (code[*iCode] != 2)))
			{
				Locker = Closed;
				*time_counter = 0;
				*iCode = 0;
			}
		}
	}
}

int CheckTrueCombination(
	int iCode, char eventKey1, int * code,
	char eventKey2, char eventKey3)
{
	if (iCode < 3)
	{
		if((eventKey1 && (code[iCode] == 1))
		|| (eventKey2 && (code[iCode] == 2))
		|| (eventKey3 && (code[iCode] == 3)))
		{
			iCode++;
			Locker = PushKey;
		}
	}
	else
	{
		if ((eventKey1 && (code[iCode] == 1))
		|| (eventKey2 && (code[iCode] == 2)))
		{
			iCode++;
			Locker = PushKey;
		}
	}				return iCode;
}