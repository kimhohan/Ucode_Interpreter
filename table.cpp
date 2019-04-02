#include "stdafx.h"
#include "table.h"

#include <stdlib.h>
#include <string.h>

Table::Table()
{
	table = NULL;

	AddLable("read", -1);
	AddLable("write", -2);
	AddLable("lf", -3);
}

Table::~Table()
{
	if (!table)
		delete table;
}

void Table::AddLable(char *name, int address)
{
	lableT *head = table;
	lableT *node = new lableT;

	strcpy_s(node->name, name);
	node->address = address;
	node->next = NULL;

	if (!head)
		table = node;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = node;
	}

}

int Table::GetLableAddress(char *name)
{
	lableT *head = table;

	while (strcmp(head->name, name) != 0){
		head = head->next;
		if (!head)
			return -10;
	}
	return head->address;
}

int Table::getLableCount()
{
	lableT *head = table;
	int count = 0;

	while (head != NULL){
		count++;
		head = head->next;
	}

	return count;
}

/*CString Table::getLableInfo(int num)
{
	lableT *head = table;
	CString str;
	int count = 0;

	while (num != count){
		head = head->next;
		count++;
	}

	str.Format(_T("%S\t%d"), head->name, head->address);

	return str;
}*/
