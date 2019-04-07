#include "stdafx.h"
#include "Interpreter.h"
#include "resource.h"
#define OP_SIZE 10
#define BUF_SIZE 512
char* operation[4];


typedef enum opcode {
	nop, bgn, sym, lod, lda, ldc, str, ldi, sti,
	not, neg, inc, decop, dup, add, sub, mult, divop, mod,
	gt, lt, ge, le, eq, ne, and, or, swp, ujp, tjp, fjp,
	call, ret, push, ldp, proc, endop, read, write, lf,
}opcode; // Assemble 함수 case문에서 사용

char *opcodeName1[NO_OPCODE] =
{
	"nop", "bgn", "sym", "lod", "lda", "ldc", "str", "ldi", "sti",
	"not", "neg", "inc", "dec", "dup", "add", "sub", "mult", "div", "mod",
	"gt", "lt", "ge", "le", "eq", "ne", "and", "or", "swp", "ujp", "tjp", "fjp",
	"call", "ret", "push", "ldp", "proc", "end", "read", "write", "lf"
}; // 모든 명령어

int StaticCounts[NO_OPCODE - 3] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
}; // 명령어별 사용횟수

int DynamicCounts[NO_OPCODE - 3] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
}; // 명령어별 실행횟수


CInterpreter::CInterpreter(CString strPathName) : memory_size(0) , pc(0)
{
	memory = new CMemory();
	for (int i = 0; i < 4; i++)
		operation[i] = new char[OP_SIZE];


	filename = strPathName;
	FileRead();
	fin.open(filename, ios::in);

} // 인터프리터 생성자 메모리 동적할당 후 파일 읽는것 까지 수행함


CInterpreter::~CInterpreter()
{
	if (memory)
		delete memory;
	for (int i = 0; i < 4; i++)
	{
			delete operation[i];
	}
}

void CInterpreter::FileRead() // uco 파일을 읽고 라벨에 주소 추가/ 명령어 사용횟수 저장/ Block 저장
{
	char buf[BUF_SIZE];
	char label[OP_SIZE];
	char* ptr;
	int temp_pc;

	fin.open(filename, ios::in);
	if (fin.fail())
		return;

	while (fin.getline(buf, sizeof(buf)))
	{
		if (buf[0] != ' '){
			strcpy(label, strtok(buf, " "));
			strcpy(buf, strtok(NULL, " "));
			lable.AddLable(label, pc);
		}
		else
			strcpy(buf, strtok(buf, " "));

		for (int i = 0; i < NO_OPCODE - 3; i++)
			if (!strcmp(buf, opcodeName1[i])){
				StaticCounts[i]++; break;
			}

		if (!strcmp(buf, "bgn")){
			int opr = atoi(strtok(NULL, " "));
			memory->InsertBlock(opr);
			memory_size += opr;
			temp_pc = pc;
		}
		else if (!strcmp(buf, "proc")){
			strtok(NULL, " ");
			ptr = strtok(NULL, " ");
			int opr = 0;
			if (ptr)
				opr = atoi(ptr);
			memory->InsertBlock(opr);
			memory_size += opr;
		}
		pc++;
	}
	pc = temp_pc;
	fin.close();

	memory->SetMemory(memory_size);
}

int CInterpreter::FileStep() // 한 줄씩 어셈블
{
	char* token;
	char buf[BUF_SIZE];
	line_ = 0;

	if (pc == -1)
		return 0;

	fin.seekg(0, ios::beg);
	fin.getline(buf, sizeof(buf));
	while (pc != line_)
	{
		line_++;
		fin.getline(buf, sizeof(buf));
	}
	
	if (buf[0] != ' ')
	{
		strtok(buf, " ");
		token = strtok(NULL, " ");
	}
	else
		token = strtok(buf, " ");

	int tokenNum = 0;
	while (token && tokenNum < 4)
	{
		strcpy(operation[tokenNum++], token); // 명령어와 값 저장
		token = strtok(NULL, " ");
	}

	for (int i = 0; i < NO_OPCODE; i++)
	{
		if (!strcmp(operation[0], opcodeName1[i]))
		{
			DynamicCounts[i]++; // 명령어 실행횟수 추가
			Assemble(i);
			break;
		}
	}

	return 1;
}

void CInterpreter::Assemble(int opcode_name) // 각 명령어 별 어셈블 과정
{
	int data, temp1, temp2, backup;
	int pcTemp=0;
	char buf[BUF_SIZE];
	char op[OP_SIZE];

	switch (opcode_name)
	{
	case ldp:
		//call이 나올 때까지 pc++
		pcTemp = pc;
		while (1){
			pc++;
			fin.getline(buf, sizeof(buf));
			if (!strcmp("call", strtok(buf, " ")))
				break;
		}
		strcpy(op, strtok(NULL, " "));
		if (strcmp(op, "read") && strcmp(op, "write") && strcmp(op, "lf")){
			//사용자가 지정한 label일 시 돌아올 pc값을 저장
			stack.Push(pc);
			topStack.Push(stack.GetTop());
		}
		//다시 원래의 pc값으로
		pc = pcTemp;
		break;
		//메모리
	case lod: stack.Push(memory->LoadMemory(atoi(operation[1]), atoi(operation[2]))); break;
	case lda: stack.Push(memory->LoadAddress(atoi(operation[1]), atoi(operation[2]))); break;
	case ldc: stack.Push(atoi(operation[1])); break;
	case str: memory->StoreMemory(atoi(operation[1]), atoi(operation[2]), stack.Pop()); break;
	case ldi: stack.Push(memory->LoadMemory(stack.Pop())); break;
	case sti:
		data = stack.Pop();
		memory->StoreMemory(stack.Pop(), data);
		break;
		//단항
	case not: stack.Push(!stack.Pop()); break;
	case neg: stack.Push(-1 * stack.Pop()); break;
	case inc: stack.Push(stack.Pop() + 1); break;
	case decop: stack.Push(stack.Pop() - 1); break;
	case dup:
		data = stack.Pop();
		stack.Push(data);
		stack.Push(data);
		break;
		//이항
	case add: stack.Push(stack.Pop() + stack.Pop()); break;
	case sub:
		data = stack.Pop();
		stack.Push(stack.Pop() - data);
		break;
	case mult: stack.Push(stack.Pop() * stack.Pop()); break;
	case divop:
		data = stack.Pop();
		if (data == 0)
			break;
		stack.Push(stack.Pop() / data);
		break;
	case mod:
		data = stack.Pop();
		if (data == 0)
			break;
		stack.Push(stack.Pop() % data);
		break;
	case gt: stack.Push(stack.Pop() < stack.Pop()); break;
	case lt: stack.Push(stack.Pop() > stack.Pop()); break;
	case ge: stack.Push(stack.Pop() <= stack.Pop()); break;
	case le: stack.Push(stack.Pop() >= stack.Pop()); break;
	case eq: stack.Push(stack.Pop() == stack.Pop()); break;
	case ne: stack.Push(stack.Pop() != stack.Pop()); break;
	case and: stack.Push(stack.Pop() && stack.Pop()); break;
	case or: stack.Push(stack.Pop() || stack.Pop()); break;
	case swp:
		temp1 = stack.Pop();
		temp2 = stack.Pop();
		stack.Push(temp1);
		stack.Push(temp2);
		break;
		//흐름제어
	case ujp:
		pc = lable.GetLableAddress(operation[1]) - 1;
		break;
	case tjp:
		if (stack.Pop() != 0)
			pc = lable.GetLableAddress(operation[1]) - 1;
		break;
	case fjp:
		if (stack.Pop() == 0)
			pc = lable.GetLableAddress(operation[1]) - 1;
		break;
		//함수 정의 및 호출
	case call:
		if (!strcmp(operation[1], "read")){
			while (1)
			{
				int as = 0;
				CDialogRead dlg;
				if (dlg.DoModal() == IDOK) // 다이얼로그로 사용자가 값 입력
				{
					data = dlg.m_read;
					if (!data)
					{
						as++;
					}
					else
					{
						memory->StoreMemory(stack.Pop(), data);
							break;
					}
				}
			}
		}
		else if (!strcmp(operation[1], "write")){
			data = stack.Pop();
			vector<int>::iterator it = resultValue.end(); // 처리된 결과 resultValue 변수에 저장
			resultValue.insert(it, data);
		}
		else if (!strcmp(operation[1], "lf"))
		{
			cout << endl;
		}
		else
		{
			pc = lable.GetLableAddress(operation[1]) - 1;
		}
		break;
	case ret: 
		stack.SetTop(topStack.Pop());
		pc = stack.Pop();
		break;
	case endop:
		if (stack.EmptyStack())
			pc = -2;
		else
			pc = stack.Pop();
		break;
	}
	pc++;
}

void CInterpreter::FileRun() // 파일 스텝을 모두 끝날때까지 반복
{
	while (FileStep());
	fin.close();
}

int CInterpreter::GetPC() // PC값 반환
{
	return pc;
}

int CInterpreter::GetLine() // 현재 줄 위치 반환
{
	return line_;
}

int CInterpreter::GetStatic(int num) // 명령어별 사용횟수 반환
{
	return StaticCounts[num];
}

int CInterpreter::GetDynamic(int num) // 명령어별 수행횟수 반환
{
	return DynamicCounts[num];
}

