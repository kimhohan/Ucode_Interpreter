// MyUcodeDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyUcode.h"
#include "MyUcodeDlg.h"
#include "afxdialogex.h"
#include "ReadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ �����Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyUcodeDlg ��ȭ ����



CMyUcodeDlg::CMyUcodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyUcodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyUcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ucoBox);
	DDX_Control(pDX, IDC_LIST3, label);
	DDX_Control(pDX, IDC_LIST4, source);
	DDX_Control(pDX, IDC_LIST2, stack);
}

BEGIN_MESSAGE_MAP(CMyUcodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &CMyUcodeDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyUcodeDlg::OnBnClickedStep)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyUcodeDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyUcodeDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CMyUcodeDlg �޽��� ó����

BOOL CMyUcodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ���� ������ �־��� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ���쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	ucoBox.AddString(_T("test1.uco"));
	ucoBox.AddString(_T("factorial.uco"));
	ucoBox.AddString(_T("pal.uco"));
	ucoBox.AddString(_T("bubble.uco"));
	ucoBox.AddString(_T("maxmin.uco"));
	ucoBox.AddString(_T("swp.uco"));
	ucoBox.AddString(_T("abs.uco"));
	ucoBox.SetCurSel(0);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMyUcodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ���� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ������ �����ϴ� MFC ���� ���α׷��� ���쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyUcodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� �����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� �����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// �����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMyUcodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyUcodeDlg::OnBnClickedStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	//���õ� �Ҵ� ������ �ε����� ������
	int choose = ucoBox.GetCurSel();
	CString lable, str;
	switch (choose)
	{
	case 0: text = "test1"; break;
	case 1: text = "factorial"; break;
	case 2: text = "pal"; break;
	case 3: text = "bubble"; break;
	case 4: text = "maxmin"; break;
	case 5: text = "swp"; break;
	case 6: text = "abs"; break;
	}

	itp = new Interp(text);

	for (int i = 0; i < itp->lable.getLableCount(); i++){
		lable = itp->lable.getLableInfo(i);
		label.AddString(lable);
	}

	char buf[512];
	ifstream fin;
	fin.open((text + ".uco").c_str(), ios::in);

	while (fin.getline(buf, sizeof(buf))){
		str.Format(_T("%S"), buf);
		source.AddString(str);
	}
	source.SetCurSel(0);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	fin.close();
	UpdateData(FALSE);
}


void CMyUcodeDlg::OnBnClickedStep()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;

	source.SetCurSel(itp->getPc());
	itp->FileStepPass();
	stack.ResetContent();
	for (int i = 0; i <= itp->stack.getTop(); i++){
		str.Format(_T("%d"), itp->stack.getValue(i));
		stack.AddString(str);
	}
	if (itp->getPc() == -1)
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	UpdateData(FALSE);
}


void CMyUcodeDlg::OnBnClickedRun()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	itp->FileAllpass();
	stack.ResetContent();
	for (int i = 0; i <= itp->stack.getTop(); i++){
		str.Format(_T("%d"), itp->stack.getValue(i));
		stack.AddString(str);
	}
	source.SetCurSel(-1);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	UpdateData(FALSE);
}


void CMyUcodeDlg::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	itp->fileWrite();
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);

	int choose = ucoBox.GetCurSel();
	CString lable, str;
	switch (choose)
	{
	case 0: ShellExecute(NULL, _T("open"), _T("notepad"), _T("test1.list"), NULL, SW_SHOW); break;
	case 1: ShellExecute(NULL, _T("open"), _T("notepad"), _T("factorial.list"), NULL, SW_SHOW); break;
	case 2: ShellExecute(NULL, _T("open"), _T("notepad"), _T("pal.list"), NULL, SW_SHOW); break;
	case 3: ShellExecute(NULL, _T("open"), _T("notepad"), _T("bubble.list"), NULL, SW_SHOW); break;
	case 4: ShellExecute(NULL, _T("open"), _T("notepad"), _T("maxmin.list"), NULL, SW_SHOW); break;
	case 5: ShellExecute(NULL, _T("open"), _T("notepad"), _T("swp.list"), NULL, SW_SHOW); break;
	case 6: ShellExecute(NULL, _T("open"), _T("notepad"), _T("abs.list"), NULL, SW_SHOW); break;
	}
}

