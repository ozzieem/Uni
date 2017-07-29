#define STACK_MAX 100
#include "stack.h"

void Stack_Init(Stack* S)
{
	S->size = 0;
}

int Stack_Peek(Stack* S)
{
	if (S->size == 0)
	{
		printf("ERROR: Stack empty\n");
		return -1;
	}
	else
	{
		int top_element = S->data[S->size - 1];
		printf("Peeked stack: %d\n", top_element);
		return top_element;
	}
}

int Stack_Size(Stack* S)
{
	if (S->size == 0)
	{
		printf("ERROR: Stack empty\n");
		return -1;
	}
	else
	{
//		printf("Stacksize: %d\n", S->size);
		return S->size;
	}
}

void Stack_Push(Stack* S, int d)
{
	if (S->size < STACK_MAX)
	{
		S->data[S->size++] = d;
//		printf("Pushed %d to stack\n", d);
		Stack_Size(S);
	}
	else
		printf("ERROR: Stack is full\n");
}

int Stack_Pop(Stack* S)
{
	if (S->size == 0)
	{
		printf("ERROR: Stack is empty\n");
		return -1;
	}
	int top_val = S->data[S->size - 1];
	S->data[S->size - 1] = 0;
	S->size--;
//	printf("Popped %d from stack\n", top_val);	//Unnecessary
	return top_val;
}

