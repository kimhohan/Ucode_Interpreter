// ReadDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyUcode.h"
#include "ReadDlg.h"
#include "afxdialogex.h"

// CReadDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CReadDlg, CDialogEx)

CReadDlg::CReadDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CReadDlg::IDD, pParent)
, readValue(0)
{

}

CReadDlg::~CReadDlg()
{
}

void CReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, readValue);
}


BEGIN_MESSAGE_MAP(CReadDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadDlg �޽��� ó�����Դϴ�.

