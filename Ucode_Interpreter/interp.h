#pragma once

#include "memory.h"
#include "stack.h"
#include "table.h"
#include "Resource.h"
#include <iostream>
#include <fstream>
using namespace std;

class Interp{
public:

	Table lable;
	Stack stack;
	Stack topStack;
	Memory *memory;

	ifstream fin;
	ofstream fout;

	vector<int> resultValue;

	string filename;
private:
	int pc;
	int memory_size;
public:
	Interp(string file);
	~Interp();

	int getPc();
	void File1pass();	//memory ����
	int FileStepPass();
	void FileAllpass();

	void accemble(int name);
	void fileWrite();

};
