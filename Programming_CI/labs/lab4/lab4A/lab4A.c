#include <stdio.h>

enum State
{
	S1,
	S2,
	S3,
	S4
};

int main() {
	enum State state = S1; // start-state
	printf("State: %d\n", state + 1);
	char c;
	while (1) {
		c = getchar(); 
		if(c != '\n') {
			switch (state) {
			case S1:
				if (c == 'a') state = S2;
				else state = S4;
				break;
			case S2:
				if (c == 'a') state = S3;
				else if (c == 'b') state = S1;
				else state = S4;
				break;
			case S3:
			case S4:
			default: break;
			}
			printf("State: %d\n", state + 1);
		}
	}
}



