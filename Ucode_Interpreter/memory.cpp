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

void CMemory::SetMemory(int size) // 파일 읽고 나온 사이즈만큼 메모리 동적할당
{
	if (memory == NULL)
		memory = new int[size];
}

void CMemory::StoreMemory(int block, int offset, int value) // 블록 오프셋에 값 저장
{
	memory[GetBlockIndex(block) + offset] = value;
}

void CMemory::StoreMemory(int index, int value) // 실 주소에 값 저장
{
	memory[index] = value;
}

int CMemory::LoadMemory(int block, int offset) // 블록 오프셋에 저장된 값 반환
{
	return memory[GetBlockIndex(block) + offset];
}

int CMemory::LoadMemory(int index) // 실 주소에 값 반환
{
	return memory[index];
}

int CMemory::LoadAddress(int block, int offset) // 블록 오프셋의 실 주소 반환
{
	return GetBlockIndex(block) + offset;
}

void CMemory::InsertBlock(int m_block) // 1 전역변수 2 지역변수 이므로 파일 읽으면서 블록 배열 추가
{
	vector<int>::iterator it = block.end();
	block.insert(it, m_block);
}

int CMemory::GetBlockIndex(int m_block)  // 1 전역변수 2 지역변수 블록의 구분이 되는 위치 반환
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
