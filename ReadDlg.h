#pragma once

// CReadDlg ��ȭ �����Դϴ�.

class CReadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadDlg)

public:
	CReadDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CReadDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_READ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int readValue;
};

