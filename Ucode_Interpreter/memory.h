#pragma once
#include <vector>
#include <iostream>
using namespace std;


class CMemory
{
public:
	int *memory;
	vector<int> block;

public:
	CMemory();
	~CMemory();

	void SetMemory(int size);

	void StoreMemory(int block, int offset, int value);
	void StoreMemory(int index, int value);

	int LoadMemory(int block, int offset);
	int LoadMemory(int index);
	int LoadAddress(int block, int offset);

	void InsertBlock(int m_block);
	int GetBlockIndex(int m_block);
};

