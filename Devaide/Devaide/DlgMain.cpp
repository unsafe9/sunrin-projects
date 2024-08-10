
// DlgMain.cpp : ���� ����
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgMain.h"
#include "DlgAbout.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgMain ��ȭ ����
CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent),
	m_pDlgShow(NULL),
	m_dlgCalculator(this),
	m_dlgWindow(this),
	m_dlgProgram(this),
	m_dlgGraph(this),
	m_dlgMemo(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
}
void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_mainTabCtrl);
}
// CDlgMain �޽��� ó����
BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CDlgMain::OnTcnSelchangeTabMain)
	ON_COMMAND(ID_MENU_HELP_VIEW, &CDlgMain::OnMenuHelpView)
	ON_COMMAND(ID_ACT_MENU_HELP_VIEW, &CDlgMain::OnMenuHelpView)
	ON_COMMAND(ID_MENU_HELP_ABOUT, &CDlgMain::OnMenuHelpAbout)
END_MESSAGE_MAP()


BOOL CDlgMain::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = L"Devaide";

	return CDialogEx::PreCreateWindow(cs);
}
BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// �� �߰�
#define InsertTab(t) m_mainTabCtrl.InsertItem(m_mainTabCtrl.GetItemCount(), _T(t))
	InsertTab("����");		// 0
	InsertTab("������ ����");	// 1
	InsertTab("���α׷� ����");	// 2
	InsertTab("�Լ� �׷���");	// 3
	InsertTab("�޸�");			// 4
#undef InsertTab
	// �� ������ ����
	CRect rect;
	GetClientRect(rect);
	ScreenToClient(rect);
	CSize size;
	size.cx = static_cast<int>(
		(static_cast<double>(rect.Width()) - 5.0) /
		static_cast<double>(m_mainTabCtrl.GetItemCount()) + 0.5);
	m_mainTabCtrl.SetItemSize(size);

	// �𵨸��� ����
	m_dlgCalculator.Create(IDD_DLG_CALCULATOR, &m_mainTabCtrl);
	m_dlgCalculator.SetWindowPos(NULL, 5, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	m_dlgWindow.Create(IDD_DLG_WINDOW, &m_mainTabCtrl);
	m_dlgWindow.SetWindowPos(NULL, 5, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	m_dlgProgram.Create(IDD_DLG_PROGRAM, &m_mainTabCtrl);
	m_dlgProgram.SetWindowPos(NULL, 5, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	m_dlgGraph.Create(IDD_DLG_GRAPH, &m_mainTabCtrl);
	m_dlgGraph.SetWindowPos(NULL, 5, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	m_dlgMemo.Create(IDD_DLG_MEMO, &m_mainTabCtrl);
	m_dlgMemo.SetWindowPos(NULL, 5, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	// ù��° ��ҷ� �ʱ�ȭ
	m_dlgCalculator.ShowWindow(SW_SHOW);
	m_pDlgShow = &m_dlgCalculator;

	m_hAccel = LoadAcceleratorsW(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}
void CDlgMain::OnSysCommand(UINT nID, LPARAM lParam)
{
	switch (nID & 0xFFF0)
	{
	case SC_CLOSE:
		// �����ư�� ������ ���̾�α׸� �����Ѵ�.
		EndDialog(IDCANCEL);
		break;

	case IDM_DLG_ABOUTBOX:
	{	// ���� �ڽ�
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}	break;

	default:
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
void CDlgMain::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessageW(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
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
HCURSOR CDlgMain::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���� + ESC�� ���α׷��� ����Ǵ� ���� ���´�.
void CDlgMain::OnOK(){/*CDialogEx::OnOK();*/}
// ���� ��ư�� OnSysCommand���� �߰��� ó���Ѵ�.
void CDlgMain::OnCancel(){/*CDialogEx::OnCancel();*/}

// �� �ٲٴ� ó��
void CDlgMain::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_pDlgShow)
	{
		m_pDlgShow->ShowWindow(SW_HIDE);
		m_pDlgShow = NULL;
	}
	switch (m_mainTabCtrl.GetCurSel())
	{
	case 0: // ����
		m_dlgCalculator.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgCalculator;
		break;

	case 1: // ������ ����
		m_dlgWindow.RefreshWndList(0);
		m_dlgWindow.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgWindow;
		break;

	case 2: // ���α׷� ����
		m_dlgProgram.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgProgram;
		break;

	case 3: // �Լ� �׷���
		m_dlgGraph.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgGraph;
		break;

	case 4: // Memo
		m_dlgMemo.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgMemo;
		break;
	}
	*pResult = 0;
}

// �޼����� ó���ϱ� ���� ����
BOOL CDlgMain::PreTranslateMessage(MSG* pMsg)
{
	// ����Űó��
	if (m_hAccel && TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

// �޴� - ���� - ���� ����
void CDlgMain::OnMenuHelpView()
{
	ShellExecuteW(NULL, L"open", L"http://blog.naver.com/gksdntjr714/220399589159", NULL, NULL, SW_SHOWNORMAL);
}
// �޴� - ���� - ����
void CDlgMain::OnMenuHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
