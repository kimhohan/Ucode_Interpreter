#pragma once
#include "afxwin.h"
#include "resource.h"

// CDialogRead 대화 상자입니다.

class CDialogRead : public CDialog
{
	DECLARE_DYNAMIC(CDialogRead)

public:
	CDialogRead(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogRead();

	int m_read;
	char m_filename[10];

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_readEdit;
	CString m_dStr;
};