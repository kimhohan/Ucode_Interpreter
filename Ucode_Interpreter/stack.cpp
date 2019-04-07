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

int CStack::Pop() // ������ ����Ⱚ ��ȯ
{
	return stack[top--];
}

void CStack::Push(int value) // ������ ����⿡ �� �߰�
{
	stack[++top] = value;
}

bool CStack::EmptyStack() // ������ ����� ���
{
	return top == -1;
}

int CStack::GetValue(int sp) // ���� ������ ��ġ�� �� ��ȯ
{
	return stack[sp];
}

int CStack::GetTop() // ������ ����� ��ġ ��ȯ
{
	return top;
}

void CStack::SetTop(int sp) // ���� ����� ��ġ ����
{
	top = sp;
}