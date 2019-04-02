#include "stdafx.h"
#include "interp.h"
#include "ReadDlg.h"

#define NO_OPCODE 40
#define OP_SIZE 10
#define BUF_SIZE 512

char *operation[4];
int Result = 0;

typedef enum opcode {
	nop, bgn, sym, lod, lda, ldc, str, ldi, sti,
	not, neg, inc, decop, dup, add, sub, mult, divop, mod,
	gt, lt, ge, le, eq, ne, and, or, swp, ujp, tjp, fjp,
	call, ret, retv, ldp, proc, endop, read, write, lf
}opcode;

char *opcodeName[NO_OPCODE] =
{
	"nop", "bgn", "sym", "lod", "lda", "ldc", "str", "ldi", "sti",
	"not", "neg", "inc", "dec", "dup", "add", "sub", "mult", "div", "mod",
	"gt", "lt", "ge", "le", "eq", "ne", "and", "or", "swp", "ujp", "tjp", "fjp",
	"call", "ret", "retv", "ldp", "proc", "end", "read", "write", "lf"
};

int StaticCounts[NO_OPCODE - 3] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

int DynamicCounts[NO_OPCODE - 3] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

Interp::Interp(string file) : memory_size(0), pc(0)
{
	memory = new Memory();
	for (int i = 0; i < 4; i++)
		operation[i] = new char[OP_SIZE];

	filename = file;
	File1pass();
	fin.open((filename + ".uco").c_str(), ios::in);
}

Interp::~Interp()
{

}

int Interp::getPc()
{
	return pc;
}

void Interp::File1pass()
{
	char buf[BUF_SIZE];
	char label[OP_SIZE];
	char *ptr;

	fin.open((filename + ".uco").c_str(), ios::in);
	if (fin.fail())
		return;

	while (fin.getline(buf, sizeof(buf))){
		if (buf[0] != ' '){
			strcpy_s(label, strtok_s(buf, " ", (char**)buf));
			strcpy_s(buf, strtok_s(NULL, " ", NULL));
			lable.AddLable(label, pc);
		}
		else
			strcpy_s(buf, strtok_s(buf, " ", (char**)buf));

		for (int i = 0; i < NO_OPCODE - 3; i++)
			if (!strcmp(buf, opcodeName[i])){
				StaticCounts[i]++; break;
			}

		if (!strcmp(buf, "bgn")){
			int opr = atoi(strtok_s(NULL, " ", NULL));
			memory->addBlock(opr);
			memory_size += opr;
		}
		else if (!strcmp(buf, "proc")){
			strtok_s(NULL, " ", NULL);
			ptr = strtok_s(NULL, " ", NULL);
			int opr = 0;
			if (ptr)
				opr = atoi(ptr);
			memory->addBlock(opr);
			memory_size += opr;
		}
		pc++;
	}
	pc = 0;
	fin.close();
	//메모리 동적할당
	memory->makeMemory(memory_size);
}

int Interp::FileStepPass()
{
	char *token;
	char buf[BUF_SIZE];
	int line = 0;

	if (pc == -1)
		return 0;

	fin.seekg(0, ios::beg);
	fin.getline(buf, sizeof(buf));
	while (pc != line){
		line++;
		fin.getline(buf, sizeof(buf));
	}
	//연산
	if (buf[0] != ' '){
		strtok_s(buf, " ", (char**)buf);
		token = strtok_s(NULL, " ", NULL);
	}
	else 
		token = strtok_s(buf, " ", (char**)buf);

	int tokenNum = 0;
	while (token && tokenNum < 4){
		strcpy_s(operation[tokenNum++], sizeof(operation), token);
		token = strtok_s(NULL, " ", NULL);
	}
	for (int i = 0; i < NO_OPCODE; i++)
		if (!strcmp(operation[0], opcodeName[i])){
			DynamicCounts[i]++;
			accemble(i);
			break;
		}
	return 1;
}
void Interp::FileAllpass()
{
	while (FileStepPass());
	fin.close();
	fileWrite();
}


void Interp::accemble(int name)
{
	int data, temp1, temp2, backup;
	int pcTemp;
	char buf[BUF_SIZE];
	char op[OP_SIZE];

	switch (name)
	{
	case ldp:
		//call이 나올 때까지 pc++
		pcTemp = pc;
		while (1){
			pc++;
			fin.getline(buf, sizeof(buf));
			if (!strcmp("call", strtok_s(buf, " ", (char**)buf)))
				break;
		}
		strcpy_s(op, strtok_s(NULL, " ", NULL));
		if (strcmp(op, "read") && strcmp(op, "write") && strcmp(op, "lf")){
			//call이 불리는 돌아올 pc값을 저장
			stack.push(pc);
			topStack.push(stack.getTop());
		}
		//다시 원래의 pc값으로 
		pc = pcTemp;
		break;
		//데이터 이동 연산
	case lod: stack.push(memory->load(atoi(operation[1]), atoi(operation[2]))); break;
	case lda: stack.push(memory->loadAddr(atoi(operation[1]), atoi(operation[2]))); break;
	case ldc: stack.push(atoi(operation[1])); break;
	case str: memory->store(atoi(operation[1]), atoi(operation[2]), stack.pop()); break;
	case ldi: stack.push(memory->load(stack.pop())); break;
	case sti:
		data = stack.pop();
		memory->store(stack.pop(), data);
		break;
		//단항 연산
	case not: stack.push(!stack.pop()); break;
	case neg: stack.push(-1 * stack.pop()); break;
	case inc: stack.push(stack.pop() + 1); break;
	case decop: stack.push(stack.pop() - 1); break;
	case dup:
		data = stack.pop();
		stack.push(data);
		stack.push(data);
		break;
		//이항 연산
	case add: stack.push(stack.pop() + stack.pop()); break;
	case sub:
		data = stack.pop();
		stack.push(stack.pop() - data);
		break;
	case mult: stack.push(stack.pop() * stack.pop()); break;
	case divop:
		data = stack.pop();
		if (data == 0)
			break;	//error
		stack.push(stack.pop() / data);
		break;
	case mod:
		data = stack.pop();
		if (data == 0)
			break;
		stack.push(stack.pop() % data);
		break;
	case gt: stack.push(stack.pop() < stack.pop()); break;
	case lt: stack.push(stack.pop() > stack.pop()); break;
	case ge: stack.push(stack.pop() <= stack.pop()); break;
	case le: stack.push(stack.pop() >= stack.pop()); break;
	case eq: stack.push(stack.pop() == stack.pop()); break;
	case ne: stack.push(stack.pop() != stack.pop()); break;
	case and: stack.push(stack.pop() && stack.pop()); break;
	case or: stack.push(stack.pop() || stack.pop()); break;
	case swp:
		temp1 = stack.pop();
		temp2 = stack.pop();
		stack.push(temp1);
		stack.push(temp2);
		break;
		//흐름제어
	case ujp:
		pc = lable.GetLableAddress(operation[1]) - 1;
		break;
	case tjp:
		if (stack.pop())
			pc = lable.GetLableAddress(operation[1]) - 1;
		break;
	case fjp:
		if (!stack.pop())
			pc = lable.GetLableAddress(operation[1]) - 1;
		break;
		//함수 정의 및 호출
	case call:
		if (!strcmp(operation[1], "read")){
			//사용자에게 입력받는 dialog
			CReadDlg dlg;
			if (dlg.DoModal() == IDOK)
			{
				data = dlg.readValue;
				memory->store(stack.pop(), data);
			}
		}
		else if (!strcmp(operation[1], "write")){
			data = stack.pop();
			vector<int>::iterator it = resultValue.end();
			resultValue.insert(it, data);
		}
		else if (!strcmp(operation[1], "lf"))
			cout << endl;
		else
			pc = lable.GetLableAddress(operation[1]) - 1;
		break;
	case ret: stack.setTop(topStack.pop()); break;
	case retv:
		data = stack.pop();
		stack.setTop(topStack.pop());
		backup = stack.pop();
		stack.push(data);
		stack.push(backup);
		break;
	case endop:
		if (stack.empty())
			pc = -2;
		else
			pc = stack.pop();
		break;
	}
	pc++;
}

void Interp::fileWrite()
{
	char buf[BUF_SIZE];

	fin.open((filename + ".uco").c_str(), ios::in);
	fout.open((filename + ".list").c_str(), ios::out);

	fout << " \t------------ source ------------ " << endl;

	while (fin.getline(buf, sizeof(buf)))
		fout << buf << endl;

	fout << endl;

	fout << " ------------ Result ------------ " << endl << "\t";
	vector<int>::iterator it;
	for (it = resultValue.begin(); it < resultValue.end(); it++)
		fout << *it << " ";
	fout << endl;
	fout << " --------------------------------" << endl;
	fout << endl;

	fout << "\t\t" << "#### Statistics ####" << endl << endl;
	fout << " ------------ Static Instruction Counts ------------ " << endl;

	int j = 0;
	for (int i = 0; i < NO_OPCODE - 3; i++){
		if (StaticCounts[i] != 0){
			fout << opcodeName[i] << " = " << StaticCounts[i] << "\t";
			j++;
			if (j % 4 == 0)
				fout << endl;
		}
	}
	fout << endl;

	j = 0;
	fout << " ------------ Dynamic Instruction Counts ------------ " << endl;
	for (int i = 0; i < NO_OPCODE - 3; i++){
		if (DynamicCounts[i] != 0){
			fout << opcodeName[i] << " = " << DynamicCounts[i] << "\t";
			j++;
			if (j % 4 == 0)
				fout << endl;
		}
	}

	fin.close();
	fout.close();
}
