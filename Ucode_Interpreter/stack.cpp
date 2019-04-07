#include "stdafx.h"
#include "Stack.h"
#include "ChildView.h"

CStack::CStack()
{
	top = -1;
}


CStack::~CStack()
{
}

int CStack::Pop() // 스택의 꼭대기값 반환
{
	return stack[top--];
}

void CStack::Push(int value) // 스택의 꼭대기에 값 추가
{
	stack[++top] = value;
}

bool CStack::EmptyStack() // 스택이 비었을 경우
{
	return top == -1;
}

int CStack::GetValue(int sp) // 스택 포인터 위치에 값 반환
{
	return stack[sp];
}

int CStack::GetTop() // 스택의 꼭대기 위치 반환
{
	return top;
}

void CStack::SetTop(int sp) // 스택 꼭대기 위치 변경
{
	top = sp;
}