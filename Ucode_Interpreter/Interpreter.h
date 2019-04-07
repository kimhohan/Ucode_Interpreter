#pragma once

#include "Memory.h"
#include "Stack.h"
#include "Label.h"
#include <iostream>
#include <fstream>
#include "DialogRead.h"
#include "resource.h"
using namespace std;
#define NO_OPCODE 40

class CInterpreter
{
public:
	CStack stack;
	CStack topStack;
	CMemory* memory;

	ifstream fin;

	vector<int> resultValue;
	vector<char> lf_Value;

	CLabel lable;

	CString filename;

	int line_;



private:
	int pc;
	int memory_size;
	int readValue;



public:
	CInterpreter(CString strPathName);
	~CInterpreter();

	int GetPC();

	void FileRead();
	int FileStep();
	void FileRun();

	void Assemble(int opcode_name);

	int GetLine();

	int GetStatic(int num);
	int GetDynamic(int num);
};