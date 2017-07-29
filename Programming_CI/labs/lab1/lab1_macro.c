#include <stdio.h>

#define FACTORIAL(n) (n == 0 ? 1 : n * FACTORIAL(n - 1))

//Efter översättning i preprocessor:
//num = (3 == 0 ? 1 : 3 * FACTORIAL(3 - 1))

int main() {
	
    int num = 4;
    printf("%d", num);
    num = FACTORIAL(3);
    printf("%d", num);
}
