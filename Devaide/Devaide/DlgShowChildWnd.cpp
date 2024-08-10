// DlgShowChildWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgShowChildWnd.h"
#include "afxdialogex.h"

static CDlgShowChildWnd *pDlg;

// CDlgShowChildWnd 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgShowChildWnd, CDialogEx)

CDlgShowChildWnd::CDlgShowChildWnd(HWND datahWnd, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowChildWnd::IDD, pParent)
	, m_radioListValueName(0)
	, m_datahWnd(datahWnd)
{
	pDlg = this;
}

CDlgShowChildWnd::~CDlgShowChildWnd()
{
	pDlg = NULL;
}

void CDlgShowChildWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WINDOW_CHILD_LIST_WND, m_listChildWnd);
	DDX_Radio(pDX, IDC_WINDOW_CHILD_RADIO_WNDNAME, m_radioListValueName);
	DDV_MinMaxInt(pDX, m_radioListValueName, 0, 1);
}


BEGIN_MESSAGE_MAP(CDlgShowChildWnd, CDialogEx)
	ON_BN_CLICKED(ID_WINDOW_CHILD_BUTTON_REFRESH, &CDlgShowChildWnd::OnBnClickedWindowChildBtnRefresh)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_WINDOW_CHILD_RADIO_WNDNAME, IDC_WINDOW_CHILD_RADIO_CLSNAME, &CDlgShowChildWnd::RefreshWndList)
	ON_WM_CLOSE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// EnumWindows 콜백함수
BOOL CALLBACK ChildEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	WCHAR String[1024] = { 0, };

	switch (pDlg->m_radioListValueName)
	{
	case 0: // 윈도우명
		GetWindowTextW(hWnd, String, sizeof(String));
		break;

	case 1: // 클래스명
		GetClassNameW(hWnd, String, sizeof(String));
		break;
	}
	pDlg->m_listChildWnd.SetItemData(
		pDlg->m_listChildWnd.AddString(String), 
		reinterpret_cast<DWORD>(hWnd));

	return TRUE;
}
// 리스트 갱신
void CDlgShowChildWnd::RefreshWndList(UINT value)
{
	HWND data = reinterpret_cast<HWND>(
		m_listChildWnd.GetItemData(m_listChildWnd.GetCurSel()));
	int index = 0;

	m_listChildWnd.ResetContent();
	UpdateData(true);
	EnumChildWindows(m_datahWnd, ChildEnumWindowsProc, 0L);

	int count = m_listChildWnd.GetCount();
	while (index <= count && 
		reinterpret_cast<HWND>(
		m_listChildWnd.GetItemData(index++)) != data){}
	if (index <= count)
		m_listChildWnd.SetCurSel(--index);
}

// CDlgShowChildWnd 메시지 처리기입니다.

// 초기화
BOOL CDlgShowChildWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	RefreshWndList(0);

	return TRUE;
}
// 새로고침 버튼 클릭
void CDlgShowChildWnd::OnBnClickedWindowChildBtnRefresh()
{
	RefreshWndList(0);
}

// 다어얼로그 종료
void CDlgShowChildWnd::OnClose()
{
	// 모달 다이얼로그를 종료한다.
	EndDialog(IDCANCEL);
	CDialogEx::OnClose();
}
