#pragma once

#define NAME_SIZE 20

#include <string>

class Table{
protected:
	typedef struct lableT {
		char name[NAME_SIZE];
		int address;
		struct lableT *next;
	}lableT;

	lableT *table;	//���̺� ���� ����

public:
	Table();	//������ write=-1,read=-2�� �̸� ����
	~Table();
	void AddLable(char *name, int address);
	int GetLableAddress(char *name);

	int getLableCount();
	CString getLableInfo(int num);
};

