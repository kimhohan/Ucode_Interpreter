
// MFC_Ucode_2.h : MFC_Ucode_2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFC_Ucode_2App:
// �� Ŭ������ ������ ���ؼ��� MFC_Ucode_2.cpp�� �����Ͻʽÿ�.
//

class CMFC_Ucode_2App : public CWinApp
{
public:
	CMFC_Ucode_2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_Ucode_2App theApp;
