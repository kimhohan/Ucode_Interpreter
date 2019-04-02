// MyUcodeDlg.h : ���� ����
//

#pragma once

#include "interp.h"
#include "afxwin.h"
//#include "Shellapi.h"
// CMyUcodeDlg ��ȭ ����
class CMyUcodeDlg : public CDialogEx
{
public:
	Interp *itp;
	string text;
	// �����Դϴ�.
	public:
	CMyUcodeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MYUCODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


	// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox ucoBox;
	afx_msg void OnBnClickedStart();
	CListBox label;
	CListBox source;
	afx_msg void OnBnClickedStep();
	CListBox stack;
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedSave();
};

