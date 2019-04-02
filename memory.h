#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Memory{
protected:
	int *memory;
	vector<int> startBlock;
public:
	Memory();
	~Memory();

	void makeMemory(int size);

	void store(int block, int offset, int value);	//(b,n)�� value
	void store(int index, int value);	//�� �ּҿ� value
	int load(int block, int offset);	//(b,n) value load
	int load(int index);	//�� �ּ� value load
	int loadAddr(int block, int offset);	//(b,n)�� ���ּ� load

	void addBlock(int count);
	int GetBlockIndex(int block);
};
