// MyUcode.h : PROJECT_NAME ���� ���α׷��� ���� �� ���� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyUcodeApp:
// �� Ŭ������ ������ ���ؼ��� MyUcode.cpp�� �����Ͻʽÿ�.
//

class CMyUcodeApp : public CWinApp
{
public:
	CMyUcodeApp();

	// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMyUcodeApp theApp;
