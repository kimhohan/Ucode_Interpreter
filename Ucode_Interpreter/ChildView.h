
// ChildView.h : CChildView Ŭ������ �������̽�
//
using namespace std;

#pragma once
#define START 999
#define QUIT 998
#define STEP 997
#define RUN 996
#define LST 995

#define LIST_MAIN 994
#define LIST_STACK 993
#define LIST_ASSEMBLE 992
#define LIST_MEMORY 991

#define EDITBOX 990
#define EDITBOX1 989

#define NO_OPCODE 40
#define OP_SIZE 10
#define BUF_SIZE 512

#include <iostream>
#include <string>
#include <fstream>
#include "stdafx.h"
#include <stdlib.h>
#include "Memory.h"
#include "Stack.h"
#include "Interpreter.h"
#include "Label.h"

// CChildView â

class CChildView : public CWnd
{
	// �����Դϴ�.
public:
	CChildView();

	CButton* m_pBtn_start;
	CButton* m_pBtn_quit;
	CButton* m_pBtn_step;
	CButton* m_pBtn_lst;
	CButton* m_pBtn_run;
	CListCtrl* m_pList;
	CListCtrl* m_pList_stack;
	CListCtrl* m_pList_assem;
	CListCtrl* m_pList_memory;
	CString tempstr;
	CEdit* m_pEdit;
	CEdit* m_pEdit2;

	CFileDialog* m_pFile;

	CString strPathName;

	CString str;

	CStack stack;
	CMemory* memory;

	CInterpreter* itp;

	int pc;
	int memory_size;
	int temp_line = 0;
	//int temp_line;
	int nInsertedIndex[500];
	// Ư���Դϴ�.
public:


	int count;
	int memory_count = 3;
	// �۾��Դϴ�.
public:

	// �������Դϴ�.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// �����Դϴ�.
public:
	virtual ~CChildView();

	// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedStep();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedCreatelst();
	afx_msg void OnFileOpen();
	void Assemble(int opcode_name);
};