#define STACK_MAX 100
#include <stdio.h>
#include <conio.h>

typedef struct
{
	int data[STACK_MAX];
	int size;
} Stack;

Stack stack;


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
		printf("Stacksize: %d\n", S->size);
		return S->size;
	}
}

void Stack_Push(Stack* S, int d)
{
	if (S->size < STACK_MAX)
	{
		S->data[S->size++] = d;
		printf("Pushed %d to stack\n", d);
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
	printf("Popped %d from stack\n", top_val);
	Stack_Size(S);
	return top_val;
}

int main()
{
	Stack_Init(&stack);

	Stack_Size(&stack);

	Stack_Push(&stack, 32);
	Stack_Push(&stack, 23);
	Stack_Push(&stack, 49);
	Stack_Push(&stack, 68);

	Stack_Peek(&stack);
	Stack_Pop(&stack);
	Stack_Pop(&stack);
	Stack_Pop(&stack);
	Stack_Pop(&stack);

	_getch();
}

