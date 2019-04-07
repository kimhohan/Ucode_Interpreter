#pragma once

#define NAME_SIZE 20

#include <string>
#include <atlstr.h>

class CLabel{
protected:
	typedef struct label {
		char name[NAME_SIZE];
		int address;
		struct label *next;
	}Label;

	Label *m_label;	//���̺� ���� ���

public:
	CLabel();	//������ write=-1,read=-2,if=-3 �� �̸� ����
	~CLabel();
	void AddLable(char *name, int address);
	int GetLableAddress(char *name);
};
