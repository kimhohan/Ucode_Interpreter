// DialogRead.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_Ucode_2.h"
#include "DialogRead.h"
#include "afxdialogex.h"


// CDialogRead 대화 상자입니다.

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


// CDialogRead 메시지 처리기입니다.


void CDialogRead::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CDialog::OnOK();
	m_readEdit.GetWindowTextW(m_dStr);
	m_read = _ttoi(m_dStr);
	CStringA strA;
	strA = m_dStr;
	strcpy(m_filename, strA);
}
