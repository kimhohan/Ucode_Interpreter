#include "stdafx.h"
#include "stack.h"
#include <cstdlib>

Stack::Stack()
{
	top = -1;
}

Stack::~Stack()
{

}

void Stack::push(int value)
{
	if (full())
		exit(0);
	stack[++top] = value;
}

int Stack::pop()
{
	if (empty())
		exit(0);
	return stack[top--];
}

int Stack::getTop()
{
	return top;
}

void Stack::setTop(int sp)
{
	top = sp;
}

bool Stack::full()
{
	return top == STACK_SIZE - 1;
}

bool Stack::empty()
{
	return top == -1;
}

int Stack::getValue(int sp)
{
	return stack[sp];
}
