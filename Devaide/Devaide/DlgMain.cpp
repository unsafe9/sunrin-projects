
// DlgMain.cpp : 구현 파일
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgMain.h"
#include "DlgAbout.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgMain 대화 상자
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
// CDlgMain 메시지 처리기
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

	// 이 대화 상자의 아이콘을 설정합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 탭 추가
#define InsertTab(t) m_mainTabCtrl.InsertItem(m_mainTabCtrl.GetItemCount(), _T(t))
	InsertTab("계산기");		// 0
	InsertTab("윈도우 관리");	// 1
	InsertTab("프로그램 관리");	// 2
	InsertTab("함수 그래프");	// 3
	InsertTab("메모");			// 4
#undef InsertTab
	// 탭 사이즈 설정
	CRect rect;
	GetClientRect(rect);
	ScreenToClient(rect);
	CSize size;
	size.cx = static_cast<int>(
		(static_cast<double>(rect.Width()) - 5.0) /
		static_cast<double>(m_mainTabCtrl.GetItemCount()) + 0.5);
	m_mainTabCtrl.SetItemSize(size);

	// 모델리스 생성
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
	
	// 첫번째 요소로 초기화
	m_dlgCalculator.ShowWindow(SW_SHOW);
	m_pDlgShow = &m_dlgCalculator;

	m_hAccel = LoadAcceleratorsW(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
void CDlgMain::OnSysCommand(UINT nID, LPARAM lParam)
{
	switch (nID & 0xFFF0)
	{
	case SC_CLOSE:
		// 종료버튼이 눌리면 다이얼로그를 종료한다.
		EndDialog(IDCANCEL);
		break;

	case IDM_DLG_ABOUTBOX:
	{	// 정보 박스
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
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessageW(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
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

// 엔터 + ESC로 프로그램이 종료되는 것을 막는다.
void CDlgMain::OnOK(){/*CDialogEx::OnOK();*/}
// 종료 버튼은 OnSysCommand에서 추가로 처리한다.
void CDlgMain::OnCancel(){/*CDialogEx::OnCancel();*/}

// 탭 바꾸는 처리
void CDlgMain::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_pDlgShow)
	{
		m_pDlgShow->ShowWindow(SW_HIDE);
		m_pDlgShow = NULL;
	}
	switch (m_mainTabCtrl.GetCurSel())
	{
	case 0: // 계산기
		m_dlgCalculator.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgCalculator;
		break;

	case 1: // 윈도우 관리
		m_dlgWindow.RefreshWndList(0);
		m_dlgWindow.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgWindow;
		break;

	case 2: // 프로그램 관리
		m_dlgProgram.ShowWindow(SW_SHOW);
		m_pDlgShow = &m_dlgProgram;
		break;

	case 3: // 함수 그래프
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

// 메세지를 처리하기 전에 조작
BOOL CDlgMain::PreTranslateMessage(MSG* pMsg)
{
	// 단축키처리
	if (m_hAccel && TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

// 메뉴 - 도움말 - 도움말 보기
void CDlgMain::OnMenuHelpView()
{
	ShellExecuteW(NULL, L"open", L"http://blog.naver.com/gksdntjr714/220399589159", NULL, NULL, SW_SHOWNORMAL);
}
// 메뉴 - 도움말 - 정보
void CDlgMain::OnMenuHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
