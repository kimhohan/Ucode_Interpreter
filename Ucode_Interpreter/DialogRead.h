#pragma once
#include "afxwin.h"
#include "resource.h"

// CDialogRead ��ȭ �����Դϴ�.

class CDialogRead : public CDialog
{
	DECLARE_DYNAMIC(CDialogRead)

public:
	CDialogRead(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogRead();

	int m_read;
	char m_filename[10];

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_readEdit;
	CString m_dStr;
};