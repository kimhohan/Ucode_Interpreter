
#include "stdafx.h"
#include "Label.h"
#include <stdlib.h>
#include <string.h>

CLabel::CLabel() // 시스템 함수 미리 지정
{
	m_label = NULL;

	AddLable("read", -1);
	AddLable("write", -2);
	AddLable("lf", -3);
}

CLabel::~CLabel()
{
	if (m_label != NULL)
	{
		delete m_label;
	}

}

void CLabel::AddLable(char *name, int address) // 노드를 활용하여 라벨 추가
{
	Label *head = m_label;
	Label *node = new Label;

	strcpy(node->name, name);
	node->address = address;
	node->next = NULL;

	if (!head)
		m_label = node;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = node;
	}

}

int CLabel::GetLableAddress(char *name) // 해당 라벨의 주소값 반환
{
	Label *head = m_label;

	while (strcmp(head->name, name) != 0){
		head = head->next;
		if (!head)
			return -10;
	}
	return head->address;
}