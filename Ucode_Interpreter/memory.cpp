#include "stdafx.h"
#include "Memory.h"


CMemory::CMemory()
{
	memory = NULL;
}


CMemory::~CMemory()
{
	if (memory != NULL)
		delete memory;
}

void CMemory::SetMemory(int size) // ���� �а� ���� �����ŭ �޸� �����Ҵ�
{
	if (memory == NULL)
		memory = new int[size];
}

void CMemory::StoreMemory(int block, int offset, int value) // ��� �����¿� �� ����
{
	memory[GetBlockIndex(block) + offset] = value;
}

void CMemory::StoreMemory(int index, int value) // �� �ּҿ� �� ����
{
	memory[index] = value;
}

int CMemory::LoadMemory(int block, int offset) // ��� �����¿� ����� �� ��ȯ
{
	return memory[GetBlockIndex(block) + offset];
}

int CMemory::LoadMemory(int index) // �� �ּҿ� �� ��ȯ
{
	return memory[index];
}

int CMemory::LoadAddress(int block, int offset) // ��� �������� �� �ּ� ��ȯ
{
	return GetBlockIndex(block) + offset;
}

void CMemory::InsertBlock(int m_block) // 1 �������� 2 �������� �̹Ƿ� ���� �����鼭 ��� �迭 �߰�
{
	vector<int>::iterator it = block.end();
	block.insert(it, m_block);
}

int CMemory::GetBlockIndex(int m_block)  // 1 �������� 2 �������� ����� ������ �Ǵ� ��ġ ��ȯ
{
	if (!m_block)
		return 0;
	else
	{
		int address = 0;
		for (int i = 0; i < m_block; i++)
			address += block[i];
		return address;
	}
}
