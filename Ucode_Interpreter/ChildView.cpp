
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC_Ucode_2.h"
#include "ChildView.h"
#include <afxcmn.h>
#include "MainFrm.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include "Interpreter.h"
typedef enum opcode {
	nop, bgn, sym, lod, lda, ldc, str, ldi, sti,
	not, neg, inc, decop, dup, add, sub, mult, divop, mod,
	gt, lt, ge, le, eq, ne, and, or, swp, ujp, tjp, fjp,
	call, ret, push, ldp, proc, endop, read, write, lf
}opcode;
using namespace std;

int just = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define NO_OPCODE 40

char *opcodeName[40] =
{
	"nop", "bgn", "sym", "lod", "lda", "ldc", "str", "ldi", "sti",
	"not", "neg", "inc", "dec", "dup", "add", "sub", "mult", "div", "mod",
	"gt", "lt", "ge", "le", "eq", "ne", "and", "or", "swp", "ujp", "tjp", "fjp",
	"call", "ret", "push", "ldp", "proc", "end", "read", "write", "lf"
};

// CChildView

CChildView::CChildView()
{
	m_pBtn_start = NULL;
	m_pBtn_quit = NULL;
	m_pBtn_step = NULL;
	m_pBtn_run = NULL;
	m_pBtn_lst = NULL;
	m_pList = NULL;
	m_pList_stack = NULL;
	m_pList_assem = NULL;
	m_pList_memory = NULL;
	m_pFile = NULL;
	m_pEdit = NULL;
	m_pEdit2 = NULL;
}

CChildView::~CChildView()
{
	if (m_pBtn_start != NULL)
	{
		m_pBtn_start->DestroyWindow();
		delete m_pBtn_start;
	}

	if (m_pBtn_quit != NULL)
	{
		m_pBtn_quit->DestroyWindow();
		delete m_pBtn_quit;
	}

	if (m_pBtn_step != NULL)
	{
		m_pBtn_step->DestroyWindow();
		delete m_pBtn_step;
	}

	if (m_pBtn_lst != NULL)
	{
		m_pBtn_lst->DestroyWindow();
		delete m_pBtn_lst;
	}

	if (m_pBtn_run != NULL)
	{
		m_pBtn_run->DestroyWindow();
		delete m_pBtn_run;
	}

	if (m_pList_stack)
	{
		m_pList_stack->DestroyWindow();
		delete m_pList_stack;
	}
	if (m_pList)
	{
		m_pList->DestroyWindow();
		delete m_pList;
	}
	if (m_pList_assem)
	{
		m_pList_assem->DestroyWindow();
		delete m_pList_assem;
	}
	if (m_pList_memory)
	{
		m_pList_memory->DestroyWindow();
		delete m_pList_memory;
	}

	if (m_pFile)
	{
		m_pFile->DestroyWindow();
		delete m_pFile;
	}
	if (m_pEdit)
	{
		m_pEdit->DestroyWindow();
		delete m_pEdit;
	}
	if (m_pEdit2)
	{
		m_pEdit2->DestroyWindow();
		delete m_pEdit2;
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(START, &CChildView::OnBnClickedStart)
	ON_BN_CLICKED(QUIT, &CChildView::OnBnClickedQuit)
	ON_COMMAND(ID_32771, &CChildView::OnFileOpen)
	ON_BN_CLICKED(STEP, &CChildView::OnBnClickedStep)
	ON_BN_CLICKED(RUN, &CChildView::OnBnClickedRun)
	ON_BN_CLICKED(LST, &CChildView::OnBnClickedCreatelst)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (m_pBtn_start == NULL)
	{
		m_pBtn_start = new CButton();
		CRect rect;
		rect.left = 1000;
		rect.right = 1150;
		rect.top = 300;
		rect.bottom = 320;
		m_pBtn_start->Create(L"START",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			rect,
			this,
			START);
	}

	if (m_pBtn_step == NULL)
	{
		m_pBtn_step = new CButton();
		CRect rect;
		rect.left = 1000;
		rect.right = 1150;
		rect.top = 325;
		rect.bottom = 345;
		m_pBtn_step->Create(L"STEP",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			rect,
			this,
			STEP);
	}

	if (m_pBtn_run == NULL)
	{
		m_pBtn_run = new CButton();
		CRect rect;
		rect.left = 1000;
		rect.right = 1150;
		rect.top = 350;
		rect.bottom = 370;
		m_pBtn_run->Create(L"RUN",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			rect,
			this,
			RUN);
	}



	if (m_pBtn_lst == NULL)
	{
		m_pBtn_lst = new CButton();
		CRect rect;
		rect.left = 1000;
		rect.right = 1150;
		rect.top = 375;
		rect.bottom = 395;
		m_pBtn_lst->Create(L"CREATE lst",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			rect,
			this,
			LST);
	}

	if (m_pBtn_quit == NULL)
	{
		m_pBtn_quit = new CButton();
		CRect rect;
		rect.left = 1000;
		rect.right = 1150;
		rect.top = 400;
		rect.bottom = 420;
		m_pBtn_quit->Create(L"QUIT",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			rect,
			this,
			QUIT);
	}


	if (m_pList == NULL)
	{
		m_pList = new CListCtrl();
		CRect rect;
		rect.left = 20;
		rect.right = 820;
		rect.top = 20;
		rect.bottom = 430;
		m_pList->Create(WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT,
			rect, this, 997);

		m_pList->InsertColumn(0, L"LINE", LVCFMT_LEFT, 50);
		m_pList->InsertColumn(1, L"LABEL", LVCFMT_LEFT, 50);
		m_pList->InsertColumn(2, L"SOURCE", LVCFMT_LEFT, 100);
		m_pList->InsertColumn(3, L"VAL1", LVCFMT_LEFT, 70);
		m_pList->InsertColumn(4, L"VAL2", LVCFMT_LEFT, 70);
		m_pList->InsertColumn(5, L"VAL3", LVCFMT_LEFT, 70);
		m_pList->InsertColumn(6, L" ", LVCFMT_LEFT, 25);
		m_pList->InsertColumn(7, L"OBJECT", LVCFMT_LEFT, 100);
		m_pList->InsertColumn(8, L"OBJ1", LVCFMT_LEFT, 100);
		m_pList->InsertColumn(9, L"OBJ2", LVCFMT_LEFT, 100);
		m_pList->InsertColumn(9, L"OBJ3", LVCFMT_LEFT, 100);
	}
	if (m_pList_stack == NULL)
	{
		m_pList_stack = new CListCtrl();
		CRect rect;
		rect.left = 860;
		rect.right = 960;
		rect.top = 20;
		rect.bottom = 430;
		m_pList_stack->Create(WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT,
			rect, this, LIST_STACK);

		m_pList_stack->InsertColumn(0, L"STACK", LVCFMT_LEFT, 100);
	}
	if (m_pList_assem == NULL)
	{
		m_pList_assem = new CListCtrl();
		CRect rect;
		rect.left = 20;
		rect.right = 1150;
		rect.top = 450;
		rect.bottom = 620;
		m_pList_assem->Create(WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT,
			rect, this, LIST_ASSEMBLE);
		m_pList_assem->InsertColumn(0, L" ", LVCFMT_LEFT, 400);
	}
	if (m_pList_memory == NULL)
	{
		m_pList_memory = new CListCtrl();
		CRect rect;
		rect.left = 1000;
		rect.right = 1150;
		rect.top = 20;
		rect.bottom = 280;
		m_pList_memory->Create(WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT,
			rect, this, LIST_MEMORY);

		m_pList_memory->InsertColumn(0, L"LABEL", LVCFMT_LEFT, 50);
		m_pList_memory->InsertColumn(1, L"ADDRESS", LVCFMT_LEFT, 80);
	}
	if (m_pEdit == NULL)
	{
		m_pEdit = new CEdit();
		CRect rect;
		rect.left = 1170;
		rect.right = 1320;
		rect.top = 50;
		rect.bottom = 140;
		m_pEdit->Create(WS_VISIBLE | WS_BORDER | WS_CHILD | ES_MULTILINE | ES_READONLY, rect, this, EDITBOX);
	}

	if (m_pEdit2 == NULL)
	{
		m_pEdit2 = new CEdit();
		CRect rect;
		rect.left = 1170;
		rect.right = 1320;
		rect.top = 20;
		rect.bottom = 40;
		m_pEdit2->Create(WS_VISIBLE | WS_BORDER | WS_CHILD, rect, this, EDITBOX1);
	}
	return 0;
}

void CChildView::OnBnClickedStart()
{
	if (just)
		delete itp;
	just = 0;
	char buf[512]; // 파일을 한줄을 저장하기위한 배열
	char* p_label;// buf 에저장된 문자열을 분리해서 하나씩 저장
	ifstream fin;
	fin.open(strPathName, ios::in); // 위에 스위치 문에 따라 열리는 파일이 달라진다.
	if (fin.fail())
	{
		MessageBox(L"불러온 파일이 없습니다.");
	}
	else
	{
		char* p_exit; // 주석의시작을 알리는 "%"를 저장 
		char p_buf[5] = "%";// p_exit에 "%"를 저장하기위해서 사용하는 배열
		p_exit = strtok(p_buf, " ");// p_buf 로부터 "%" 공백을 뺴고 분리해서 저장
		count = 1;
		char label[200];
		memory_count = 3;
		m_pList->DeleteAllItems();
		m_pList_memory->DeleteAllItems();
		m_pList_assem->DeleteAllItems();
		m_pList_stack->DeleteAllItems();

		str.Format(_T("%S"), "read");
		m_pList_memory->InsertItem(0, str, 0);
		str.Format(_T("%d"), -1);
		m_pList_memory->SetItemText(0, 1, str);
		str.Format(_T("%S"), "write");
		m_pList_memory->InsertItem(1, str, 0);
		str.Format(_T("%d"), -2);
		m_pList_memory->SetItemText(1, 1, str);
		str.Format(_T("%S"), "lf");
		m_pList_memory->InsertItem(2, str, 0);
		str.Format(_T("%d"), -3);
		m_pList_memory->SetItemText(2, 1, str);
		for (int i = 0; fin.getline(buf, sizeof(buf)); i++) // uco 파일의 줄수 만큼 반복
		{
			str.Format(_T("%d"), count);
			nInsertedIndex[i] = m_pList->InsertItem(i, str, 0); // 명령어 줄 수만큼 라인 수 출력
			count++;
			p_label = strtok(buf, " "); // uco 파일 한줄을 읽은 문자열들에서 공백을 제외한 첫 문자열을 p_label에 저장
			if (buf[0] != ' ') // 첫 글자가 공백아니면
			{
				for (int n = 1; p_label != 0 && strcmp(p_label, p_exit); n++) // 글자가 없거나 %(주석)가 나오면 다음 반복진행
				{
					str.Format(_T("%S"), p_label);
					m_pList->SetItemText(nInsertedIndex[i], n, str); // n 번째 열에 문자열 출력
					if (n == 1)
					{
						str.Format(_T("%S"), p_label);
						m_pList_memory->InsertItem(memory_count, str, 0);
						str.Format(_T("%d"), count - 1);
						m_pList_memory->SetItemText(memory_count, 1, str);
						memory_count++;
					}
					p_label = strtok(NULL, " "); // 공백을 제외하고 다음 문자열 p_label에 저장
				}

			}
			else // 첫 글자가 공백이면
			{
				for (int n = 2; p_label != 0 && strcmp(p_label, p_exit); n++)
				{
					str.Format(_T("%S"), p_label);
					m_pList->SetItemText(nInsertedIndex[i], n, str);
					p_label = strtok(NULL, " ");

				}
			}
		}
		fin.close(); // 파일 닫음

		CString lable2;
		CStringA asdasd;
		CStringA asd;
		char* zzz;
		char* compare;
		char* compareint;
		int a = 0;
		int b = 0;

		for (int j = 0; j < count; j++) // 정수화 된 UCODE를 출력
		{
			asdasd = m_pList->GetItemText(j, 2);
			zzz = asdasd.GetBuffer();
			for (int i = 0; i < 40; i++)
			{
				if (!strcmp(opcodeName[i], zzz))
				{
					str.Format(_T("%d"), i);
					m_pList->SetItemText(nInsertedIndex[j], 7, str);
				}
			}

			asdasd = m_pList->GetItemText(j, 3);
			zzz = asdasd.GetBuffer();
			b = 0;
			while (b < m_pList_memory->GetItemCount())
			{
				asd = m_pList_memory->GetItemText(b, 0);
				compare = asd.GetBuffer();
				if (!strcmp(compare, zzz))
				{
					asd = m_pList_memory->GetItemText(b, 1);
					compareint = asd.GetBuffer();
					zzz = compareint;
					break;
				}
				b++;
			}

			str.Format(_T("%S"), zzz); m_pList->SetItemText(nInsertedIndex[j], 8, str);
			asdasd = m_pList->GetItemText(j, 4);
			zzz = asdasd.GetBuffer();
			str.Format(_T("%S"), zzz);
			m_pList->SetItemText(nInsertedIndex[j], 9, str);
			str.Format(_T("%S"), " ");
		}

		itp = new CInterpreter(strPathName);
		just++;
	}
}

void CChildView::OnBnClickedStep()
{
	if (just == 0)
	{
		MessageBox(L"Start 버튼이 생행되지 않았습니다.");
	}
	else
	{
		CString m_str1;
		m_str1.Format(_T("%S"), " ");
		m_pList_assem->DeleteAllItems();
		m_pList_stack->DeleteAllItems();
		int n = itp->FileStep();
		str.Format(_T("%S"), "A");
		for (int f = 0; f < itp->GetLine(); f++)  // 현재 pc 위치를 출력
		{
			m_pList->SetItemText(nInsertedIndex[f], 6, m_str1);
		}
		m_str1.Format(_T("%S"), "  ");
		m_pList->SetItemText(nInsertedIndex[temp_line], 6, m_str1);
		m_pList->SetItemText(nInsertedIndex[itp->GetLine()], 6, str);
		temp_line = itp->GetLine();
		m_pList_stack->DeleteAllItems();
		str.Format(_T("%S"), " ");
		for (int i = 0; i <= itp->stack.GetTop(); i++)
		{
			m_str1.Format(_T("%d"), itp->stack.GetValue(i));

			m_pList_stack->InsertItem(nInsertedIndex[i], str, 0);
			m_pList_stack->SetItemText(nInsertedIndex[i], 0, m_str1); // 스택 상황 출력
		}
		if (n == 0)
		{
			int as = 0, bs = 0;
			int cc = 0;
			CString m_str2;
			m_str2.Format(_T("%S"), " ");
			for (int cc = 0; cc < count; cc++)
			{
				m_pList->SetItemText(nInsertedIndex[cc], 6, m_str2);
			}
			cc = 0;
			m_str2.Format(_T("%S"), "-------------RESULT-------------");
			m_pList_assem->InsertItem(nInsertedIndex[cc], m_str2);
			while (cc < itp->resultValue.size())
			{
				m_str2.Format(_T("%d"), itp->resultValue[cc++]);
				m_pList_assem->InsertItem(nInsertedIndex[cc], m_str2);
			}
			m_str2.Format(_T("%S"), "------------STATIC COUNT-----------");
			m_pList_assem->InsertItem(nInsertedIndex[cc + 1], m_str2);
			cc = cc + 2;
			m_str2.Format(_T("nop : %d     bgn : %d     sym : %d     lod : %d"),
				itp->GetStatic(0), itp->GetStatic(1), itp->GetStatic(2), itp->GetStatic(3));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("lda : %d     ldc : %d     str : %d     ldi : %d"),
				itp->GetStatic(4), itp->GetStatic(5), itp->GetStatic(6), itp->GetStatic(7));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("sti : %d     not : %d     neg : %d     inc : %d"),
				itp->GetStatic(8), itp->GetStatic(9), itp->GetStatic(10), itp->GetStatic(11));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("dec : %d     dup : %d     add : %d     sub : %d"),
				itp->GetStatic(12), itp->GetStatic(13), itp->GetStatic(14), itp->GetStatic(15));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("mult : %d     div : %d     mod : %d     gt : %d"),
				itp->GetStatic(16), itp->GetStatic(17), itp->GetStatic(18), itp->GetStatic(19));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("lt : %d     ge : %d     le : %d     eq : %d"),
				itp->GetStatic(20), itp->GetStatic(21), itp->GetStatic(22), itp->GetStatic(23));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("ne : %d     and : %d     or : %d     swp : %d"),
				itp->GetStatic(24), itp->GetStatic(25), itp->GetStatic(26), itp->GetStatic(27));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("ujp : %d     tjp : %d     fjp : %d     call : %d"),
				itp->GetStatic(28), itp->GetStatic(29), itp->GetStatic(30), itp->GetStatic(31));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("ret : %d     push : %d     ldp : %d     proc : %d"),
				itp->GetStatic(32), itp->GetStatic(33), itp->GetStatic(34), itp->GetStatic(35));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("end : %d"), itp->GetStatic(36));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);

			m_str2.Format(_T("%S"), "------------Dynamic COUNT-----------");
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("nop : %d     bgn : %d     sym : %d     lod : %d"),
				itp->GetDynamic(0), itp->GetDynamic(1), itp->GetDynamic(2), itp->GetDynamic(3));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("lda : %d     ldc : %d     str : %d     ldi : %d"),
				itp->GetDynamic(4), itp->GetDynamic(5), itp->GetDynamic(6), itp->GetDynamic(7));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("sti : %d     not : %d     neg : %d     inc : %d"),
				itp->GetDynamic(8), itp->GetDynamic(9), itp->GetDynamic(10), itp->GetDynamic(11));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("dec : %d     dup : %d     add : %d     sub : %d"),
				itp->GetDynamic(12), itp->GetDynamic(13), itp->GetDynamic(14), itp->GetDynamic(15));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("mult : %d     div : %d     mod : %d     gt : %d"),
				itp->GetDynamic(16), itp->GetDynamic(17), itp->GetDynamic(18), itp->GetDynamic(19));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("lt : %d     ge : %d     le : %d     eq : %d"),
				itp->GetDynamic(20), itp->GetDynamic(21), itp->GetDynamic(22), itp->GetDynamic(23));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("ne : %d     and : %d     or : %d     swp : %d"),
				itp->GetDynamic(24), itp->GetDynamic(25), itp->GetDynamic(26), itp->GetDynamic(27));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("ujp : %d     tjp : %d     fjp : %d     call : %d"),
				itp->GetDynamic(28), itp->GetDynamic(29), itp->GetDynamic(30), itp->GetDynamic(31));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("ret : %d     push : %d     ldp : %d     proc : %d"),
				itp->GetDynamic(32), itp->GetDynamic(33), itp->GetDynamic(34), itp->GetDynamic(35));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("end : %d"), itp->GetDynamic(36));
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
			m_str2.Format(_T("%S"), "------------Dynamic Total COUNT-----------");
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2); // 결과값들 출력
			while (as < 37)
			{
				bs = bs + itp->GetDynamic(as);
				as++;
			}
			m_str2.Format(_T("%d"), bs);
			m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);

			MessageBox(L"STEP 어셈블단계를 모두 마쳤습니다");
			just++;
		}
	}
}

void CChildView::OnBnClickedRun()
{
	if (just < 1)
	{
		MessageBox(L"Start 버튼이 실행되지 않았습니다.");
	}
	else
	{
		int as = 0, bs = 0;
		int aa = 0, bb = 0;
		CString m_str2;
		itp->FileRun();
		m_pList_stack->DeleteAllItems();
		m_pList_assem->DeleteAllItems();
		m_str2.Format(_T("%S"), " ");
		int cc = 0;
		for (cc = 0; cc < count; cc++)
		{
			m_pList->SetItemText(nInsertedIndex[cc], 6, m_str2);
		}
		m_str2.Format(_T("%S"), " ");
		for (cc = 0; cc < count; cc++)
		{
			m_pList->SetItemText(nInsertedIndex[cc], 6, m_str2);
		}
		cc = 0;
		m_str2.Format(_T("%S"), "-------------RESULT-------------");
		m_pList_assem->InsertItem(nInsertedIndex[cc], m_str2);
		while (cc < itp->resultValue.size())
		{
			m_str2.Format(_T("%d"), itp->resultValue[cc++]);
			m_pList_assem->InsertItem(nInsertedIndex[cc], m_str2);
		}
		m_str2.Format(_T("%S"), "------------STATIC COUNT-----------");
		m_pList_assem->InsertItem(nInsertedIndex[cc + 1], m_str2);
		cc = cc + 2;
		m_str2.Format(_T("nop : %d     bgn : %d     sym : %d     lod : %d"),
			itp->GetStatic(0), itp->GetStatic(1), itp->GetStatic(2), itp->GetStatic(3));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("lda : %d     ldc : %d     str : %d     ldi : %d"),
			itp->GetStatic(4), itp->GetStatic(5), itp->GetStatic(6), itp->GetStatic(7));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("sti : %d     not : %d     neg : %d     inc : %d"),
			itp->GetStatic(8), itp->GetStatic(9), itp->GetStatic(10), itp->GetStatic(11));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("dec : %d     dup : %d     add : %d     sub : %d"),
			itp->GetStatic(12), itp->GetStatic(13), itp->GetStatic(14), itp->GetStatic(15));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("mult : %d     div : %d     mod : %d     gt : %d"),
			itp->GetStatic(16), itp->GetStatic(17), itp->GetStatic(18), itp->GetStatic(19));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("lt : %d     ge : %d     le : %d     eq : %d"),
			itp->GetStatic(20), itp->GetStatic(21), itp->GetStatic(22), itp->GetStatic(23));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("ne : %d     and : %d     or : %d     swp : %d"),
			itp->GetStatic(24), itp->GetStatic(25), itp->GetStatic(26), itp->GetStatic(27));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("ujp : %d     tjp : %d     fjp : %d     call : %d"),
			itp->GetStatic(28), itp->GetStatic(29), itp->GetStatic(30), itp->GetStatic(31));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("ret : %d     push : %d     ldp : %d     proc : %d"),
			itp->GetStatic(32), itp->GetStatic(33), itp->GetStatic(34), itp->GetStatic(35));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("end : %d"), itp->GetStatic(36));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);

		m_str2.Format(_T("%S"), "------------Dynamic COUNT-----------");
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("nop : %d     bgn : %d     sym : %d     lod : %d"),
			itp->GetDynamic(0), itp->GetDynamic(1), itp->GetDynamic(2), itp->GetDynamic(3));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("lda : %d     ldc : %d     str : %d     ldi : %d"),
			itp->GetDynamic(4), itp->GetDynamic(5), itp->GetDynamic(6), itp->GetDynamic(7));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("sti : %d     not : %d     neg : %d     inc : %d"),
			itp->GetDynamic(8), itp->GetDynamic(9), itp->GetDynamic(10), itp->GetDynamic(11));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("dec : %d     dup : %d     add : %d     sub : %d"),
			itp->GetDynamic(12), itp->GetDynamic(13), itp->GetDynamic(14), itp->GetDynamic(15));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("mult : %d     div : %d     mod : %d     gt : %d"),
			itp->GetDynamic(16), itp->GetDynamic(17), itp->GetDynamic(18), itp->GetDynamic(19));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("lt : %d     ge : %d     le : %d     eq : %d"),
			itp->GetDynamic(20), itp->GetDynamic(21), itp->GetDynamic(22), itp->GetDynamic(23));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("ne : %d     and : %d     or : %d     swp : %d"),
			itp->GetDynamic(24), itp->GetDynamic(25), itp->GetDynamic(26), itp->GetDynamic(27));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("ujp : %d     tjp : %d     fjp : %d     call : %d"),
			itp->GetDynamic(28), itp->GetDynamic(29), itp->GetDynamic(30), itp->GetDynamic(31));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("ret : %d     push : %d     ldp : %d     proc : %d"),
			itp->GetDynamic(32), itp->GetDynamic(33), itp->GetDynamic(34), itp->GetDynamic(35));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		m_str2.Format(_T("end : %d"), itp->GetDynamic(36));
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);

		m_str2.Format(_T("%S"), "------------Dynamic Total COUNT-----------");
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);
		while (as < 37)
		{
			bs = bs + itp->GetDynamic(as);
			as++;
		}
		m_str2.Format(_T("%d"), bs);
		m_pList_assem->InsertItem(nInsertedIndex[cc++], m_str2);

		MessageBox(L"RUN 어셈블단계를 모두 마쳤습니다");
		just++;
	}
}

void CChildView::OnBnClickedCreatelst() // 어셈 리스트 컨트롤의 결과들 lst 파일에 쓰기
{
	if (just < 2)
	{
		MessageBox(L"저장할 파일이 없습니다.");
	}
	else
	{
		CString strSaveName;
		m_pFile = new CFileDialog(false, _T("*.lst"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("lst Files(*.lst)|*.lst|"), NULL);
		if (IDOK == m_pFile->DoModal())
		{
			strSaveName = m_pFile->GetPathName();
		}
		CDialogRead r_dlg;
		ifstream fin;
		ofstream fout;
		CStringA cStrA;
		char* p_exit;

		char p_buf[5] = "%";
		p_exit = strtok(p_buf, " ");

		char buf[BUF_SIZE];

		fin.open((strPathName), ios::in);
		fout.open(strSaveName);

		fout << "------------UCODE------------" << endl;

		while (fin.getline(buf, sizeof(buf)))
		{
			strtok(buf, "%");
			fout << buf << endl;
		}
		fin.close();
		int n = 0;

		fout << "-----------INTEGER UCODE----------" << endl;
		while (n < count)
		{
			int List_seven;
			int List_eight;
			int List_nine;
			cStrA = m_pList->GetItemText(nInsertedIndex[n], 7);
			List_seven = atoi(cStrA);
			cStrA = m_pList->GetItemText(nInsertedIndex[n], 8);
			List_eight = atoi(cStrA);
			cStrA = m_pList->GetItemText(nInsertedIndex[n], 9);
			List_nine = atoi(cStrA);


			if (List_seven < 10)
			{
				fout << List_seven << "         ";
			}
			else{
				fout << List_seven << "        ";
			}

			if (0 <= List_eight < 10)
				fout << List_eight << "         ";
			else if (10 <= List_eight < 100)
				fout << List_eight << "        ";
			else
				fout << List_eight << "       ";


			if (0 <= List_nine < 10)
				fout << List_nine << endl;
			else if (10 <= List_nine < 100)
				fout << List_nine << endl;
			else if (List_nine < 0)
				fout << List_nine << endl;
			else
				fout << List_nine << endl;
			n++;
		}
		for (int n = 0; n < m_pList_assem->GetItemCount(); n++)
		{
			cStrA = m_pList_assem->GetItemText(nInsertedIndex[n], 0);
			fout << cStrA << endl;
		}
		fout.close();
	}
}

void CChildView::OnBnClickedQuit() // 종료버튼
{
	int a = MessageBox(L"정말로 종료하시겠습니까?", L"종료", MB_YESNO); // 예,아니오 옵션의 메세지박스
	if (a == IDYES) // 예버튼 눌렀을 시 종료
	{
		exit(0);
	}
}

void CChildView::OnFileOpen() // 파일 불러오기
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pFile = new CFileDialog(true, _T("*.uco"), NULL, OFN_HIDEREADONLY, _T("uco Files(*.uco)|*.uco|"), NULL);
	if (IDOK == m_pFile->DoModal())
	{
		strPathName = m_pFile->GetPathName();
		CStringA str;
		SetDlgItemText(EDITBOX1, L"       -불러온 파일-");
		SetDlgItemText(EDITBOX, strPathName);
	}
}