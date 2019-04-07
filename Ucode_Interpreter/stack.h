#pragma once

#define STACKSIZE 1000
class CStack
{
public:
	int stack[STACKSIZE];
	int top;

public:
	CStack();
	~CStack();

	int GetValue(int sp);
	void Push(int value);
	int Pop();
	int GetTop();
	void SetTop(int sp);
	bool EmptyStack();
};

