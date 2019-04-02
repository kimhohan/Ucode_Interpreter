
#pragma once

#define STACK_SIZE 1000

class Stack{
protected:
	int stack[STACK_SIZE];
	int top;

public:
	Stack();
	~Stack();

	int getValue(int sp);
	void push(int value);
	int pop();
	int getTop();	//���� top�� ��������
	void setTop(int sp);	//top = sp
	bool full();
	bool empty();
};
