#include "stdafx.h"
#include "memory.h"

#include <stdlib.h>

Memory::Memory()
{
	memory = NULL;
}

Memory::~Memory()
{
	if (memory != NULL)
		delete memory;
}

void Memory::makeMemory(int size)
{
	if (memory == NULL)
		memory = new int[size];
}

void Memory::store(int block, int offset, int value)
{
	memory[GetBlockIndex(block) + offset] = value;
}

void Memory::store(int index, int value)
{
	memory[index] = value;
}

int Memory::load(int block, int offset)
{
	return memory[GetBlockIndex(block) + offset];
}

int Memory::load(int index)
{
	return memory[index];
}

int Memory::loadAddr(int block, int offset)
{
	return GetBlockIndex(block) + offset;
}

void Memory::addBlock(int count)
{
	vector<int>::iterator it = startBlock.end();
	startBlock.insert(it, count);
}

int Memory::GetBlockIndex(int block)
{
	if (!block)
		return 0;
	else
	{
		int address = 0;
		for (int i = 0; i < block; i++)
			address += startBlock[i];
		return address;
	}
}

