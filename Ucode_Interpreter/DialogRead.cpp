// DialogRead.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC_Ucode_2.h"
#include "DialogRead.h"
#include "afxdialogex.h"


// CDialogRead ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogRead, CDialog)

CDialogRead::CDialogRead(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRead::IDD, pParent)
{

}

CDialogRead::~CDialogRead()
{
}

void CDialogRead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_readEdit);
}


BEGIN_MESSAGE_MAP(CDialogRead, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogRead::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogRead �޽��� ó�����Դϴ�.


void CDialogRead::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CDialog::OnOK();
	m_readEdit.GetWindowTextW(m_dStr);
	m_read = _ttoi(m_dStr);
	CStringA strA;
	strA = m_dStr;
	strcpy(m_filename, strA);
}
