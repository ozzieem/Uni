#include <stdio.h>


#define STACK_MAX 100

typedef struct
{
	int data[STACK_MAX];
	int size;
} Stack;


void Stack_Init(Stack* S);
int Stack_Peek(Stack* S);
int Stack_Size(Stack* S);
void Stack_Push(Stack* S, int d);
int Stack_Pop(Stack* S);
