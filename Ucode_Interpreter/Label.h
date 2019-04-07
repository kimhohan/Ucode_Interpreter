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

	Label *m_label;	//테이블 관리 헤드

public:
	CLabel();	//생성자 write=-1,read=-2,if=-3 로 미리 지정
	~CLabel();
	void AddLable(char *name, int address);
	int GetLableAddress(char *name);
};
