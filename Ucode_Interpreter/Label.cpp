
#include "stdafx.h"
#include "Label.h"
#include <stdlib.h>
#include <string.h>

CLabel::CLabel() // �ý��� �Լ� �̸� ����
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

void CLabel::AddLable(char *name, int address) // ��带 Ȱ���Ͽ� �� �߰�
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

int CLabel::GetLableAddress(char *name) // �ش� ���� �ּҰ� ��ȯ
{
	Label *head = m_label;

	while (strcmp(head->name, name) != 0){
		head = head->next;
		if (!head)
			return -10;
	}
	return head->address;
}