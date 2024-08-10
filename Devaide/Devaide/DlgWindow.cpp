// DlgWindow.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

#include "Devaide.h"

#include "DlgWindow.h"
#include "DlgMain.h"
#include "DlgShowChildWnd.h"

#include <TCHAR.h>
#include <psapi.h>

#include "Function.h"

// CDlgWindow 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgWindow, CDialogEx)

CDlgWindow::CDlgWindow(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgWindow::IDD, pParent)
, m_checkShowNoNameWnd(FALSE)
, m_checkShowHiddenWnd(FALSE)
, m_checkShowHandle(FALSE)
, m_radioListValueName(0)
, m_radioSort(0)
, m_checkAscendingSort(FALSE)
, m_isListIncludeHandle(FALSE){}

CDlgWindow::~CDlgWindow(){}

void CDlgWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_WINDOW_CHECK_NONAME, m_checkShowNoNameWnd);
	DDX_Check(pDX, IDC_WINDOW_CHECK_HIDDEN, m_checkShowHiddenWnd);
	DDX_Check(pDX, IDC_WINDOW_CHECK_HANDLE, m_checkShowHandle);
	DDX_Radio(pDX, IDC_WINDOW_RADIO_WNDNAME, m_radioListValueName);
	DDV_MinMaxInt(pDX, m_radioListValueName, 0, 2);
	DDX_Radio(pDX, IDC_WINDOW_RADIO_SORTNAME, m_radioSort);
	DDV_MinMaxInt(pDX, m_radioSort, 0, 1);
	DDX_Check(pDX, IDC_WINDOW_CHECK_ASCENDING, m_checkAscendingSort);
	DDX_Control(pDX, IDC_WINDOW_LIST_WND, m_listWnd);
	DDX_Control(pDX, IDC_WINDOW_STATIC_STATE, m_staticState);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_SHOWCHILDWND, m_buttonShowChildWnd);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_TOPMOST, m_buttonTopMost);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_HIDE, m_buttonHide);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_DESTROY, m_buttonDestroy);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_CLOSE, m_buttonClose);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_FIXSIZE, m_buttonFixSize);
	DDX_Control(pDX, IDC_WINDOW_BUTTON_FIXPOS, m_buttonFixPos);
	DDX_Control(pDX, IDC_WINDOW_EDIT_TEXT, m_editText);
}


BEGIN_MESSAGE_MAP(CDlgWindow, CDialogEx)
	ON_BN_CLICKED(IDC_WINDOW_CHECK_NONAME, &CDlgWindow::OnBnClickedWindowCheckNoname)
	ON_BN_CLICKED(IDC_WINDOW_CHECK_HIDDEN, &CDlgWindow::OnBnClickedWindowCheckHidden)
	ON_BN_CLICKED(IDC_WINDOW_CHECK_HANDLE, &CDlgWindow::OnBnClickedWindowCheckHandle)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_WINDOW_RADIO_WNDNAME, IDC_WINDOW_RADIO_PROCESSNAME, &CDlgWindow::RefreshWndList)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_WINDOW_RADIO_SORTNAME, IDC_WINDOW_RADIO_SORTZ, &CDlgWindow::RefreshWndList)
	ON_BN_CLICKED(IDC_WINDOW_CHECK_ASCENDING, &CDlgWindow::OnBnClickedWindowCheckAscending)
	ON_LBN_SELCHANGE(IDC_WINDOW_LIST_WND, &CDlgWindow::OnLbnSelchangeWindowListWnd)
	ON_LBN_DBLCLK(IDC_WINDOW_LIST_WND, &CDlgWindow::OnLbnDblclkWindowListWnd)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_SHOWCHILDWND, &CDlgWindow::OnBnClickedWindowButtonShowChildWnd)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_TOPMOST, &CDlgWindow::OnBnClickedWindowButtonTopmost)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_HIDE, &CDlgWindow::OnBnClickedWindowButtonHide)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_REFRESH, &CDlgWindow::OnBnClickedWindowButtonRefresh)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_DESTROY, &CDlgWindow::OnBnClickedWindowButtonDestroy)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_CLOSE, &CDlgWindow::OnBnClickedWindowButtonClose)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_FIXSIZE, &CDlgWindow::OnBnClickedWindowButtonFixsize)
	ON_BN_CLICKED(IDC_WINDOW_BUTTON_FIXPOS, &CDlgWindow::OnBnClickedWindowButtonFixpos)
END_MESSAGE_MAP()


// EnumWindows콜백함수
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	CDlgWindow &dlgWindow = dynamic_cast<CDlgMain*>(AfxGetMainWnd())->m_dlgWindow;

	if (dlgWindow.m_checkShowHiddenWnd ? 1 : IsWindowVisible(hWnd)) // 숨겨진윈도우 보이기 옵션 구분
	{
		// 이름 얻음
		WCHAR szString[512] = { 0, }, szText[512] = { 0, };
		if (dlgWindow.m_checkShowHandle)
		{
			wsprintfW(szString, L"%08X - ", hWnd);
			dlgWindow.m_isListIncludeHandle = TRUE;
		}
		else
		{
			dlgWindow.m_isListIncludeHandle = FALSE;
		}
		// 표시
		switch (dlgWindow.m_radioListValueName)
		{
		case 0: // 윈도우명
			GetWindowTextW(hWnd, szText, sizeof(szText));
			break;

		case 1: // 클래스명
			GetClassNameW(hWnd, szText, sizeof(szText));
			break;

		case 2: // 프로세스명
			DWORD dwProcessID;
			GetWindowThreadProcessId(hWnd, &dwProcessID);
			lstrcpyW(szText, Function::GetExeName(dwProcessID));
			break;
		}
		lstrcatW(szString, szText);

		// 정렬
		if (dlgWindow.m_checkShowNoNameWnd ? 1 : (lstrlenW(szText) > 0))
		{
			int index = 0, count = dlgWindow.m_listWnd.GetCount();
			switch (dlgWindow.m_radioSort)
			{
			case 0: // 이름순서
				if (count > 0)
				{
					for (int i = 0; i < count; ++i)
					{
						CString buf;
						dlgWindow.m_listWnd.GetText(i, buf);
						int cmp = lstrcmpW(szText,
							dlgWindow.m_isListIncludeHandle ?
							static_cast<LPCWSTR>(buf)+11 : buf);
						if (dlgWindow.m_checkAscendingSort ? cmp > 0 : cmp < 0)
						{
							++index; // 내려감
						}
					}
				}
				break;

			case 1: // 화면순서
				index = dlgWindow.m_checkAscendingSort ? 0 : count;
				break;
			}
			// 삽입
			dlgWindow.m_listWnd.InsertString(index, szString);
			dlgWindow.m_listWnd.SetItemData(index, reinterpret_cast<DWORD>(hWnd));
		}
	}
	return true;
}

// 목록의 값인 핸들로부터 안전하게 CWnd 클래스로의 포인터를 얻는다.
CWnd* CDlgWindow::GetSafeWndFromListIndex(int index) const
{
	if (index == LB_ERR)
	{
		return NULL;
	}
	HWND hWnd = GetHandleFromList(index);
	return (IsWindow(hWnd) ? FromHandle(hWnd) : NULL);
}



// CDlgWindow 메시지 처리기입니다.

// 종료 막음
void CDlgWindow::OnCancel(){/*CDialogEx::OnCancel();*/ }
// 새로고침
void CDlgWindow::RefreshWndList(UINT value)
{
	if (value >= IDC_WINDOW_RADIO_WNDNAME &&
		value <= IDC_WINDOW_RADIO_PROCESSNAME)
	{
		UINT temp = m_radioListValueName;
		UpdateData(TRUE);
		if (temp == m_radioListValueName)
		{
			return;
		}
	}
	else if (value >= IDC_WINDOW_RADIO_SORTNAME &&
		value <= IDC_WINDOW_RADIO_SORTZ)
	{
		UINT temp = m_radioSort;
		UpdateData(TRUE);
		if (temp == m_radioSort)
		{
			return;
		}
	}
	else
	{
		UpdateData(TRUE);
	}

	HWND data = GetHandleFromList(m_listWnd.GetCurSel());
	int count, index = 0;

	m_listWnd.ResetContent();
	EnumWindows(EnumWindowsProc, 0L);
	count = m_listWnd.GetCount();

	// 핸들값이 새로고침 전과 같은것을 찾는다.
	while (index <= count && GetHandleFromList(index++) != data);

	// 존재할시 커서를 설정한다.
	if (index <= count)
	{
		m_listWnd.SetCurSel(--index);
	}

	RefreshControls(index);
}
// 새로고침 버튼 클릭
void CDlgWindow::OnBnClickedWindowButtonRefresh()
{
	RefreshWndList(0);
}
// 오름차순정렬
void CDlgWindow::OnBnClickedWindowCheckAscending()
{
	RefreshWndList(0);
}
// 이름없는 윈도우 표시
void CDlgWindow::OnBnClickedWindowCheckNoname()
{
	RefreshWndList(0);
}
// 숨겨진 윈도우 표시
void CDlgWindow::OnBnClickedWindowCheckHidden()
{
	RefreshWndList(0);
}
// 핸들값 표시
void CDlgWindow::OnBnClickedWindowCheckHandle()
{
	RefreshWndList(0);
}


// 컨트롤들을 윈도우에 맞게 설정한다.
void CDlgWindow::RefreshControls(int index)
{
	CWnd *pSelectedWnd = GetSafeWndFromListIndex(index);
	m_editText.Clear();

	// 윈도우를 선택하지 않았을시 또는 비정상일시
	if (pSelectedWnd == NULL)
	{
		if (m_listWnd.GetCurSel() != LB_ERR)
		{
			m_staticState.SetWindowTextW(L"상태 : 비정상");
		}
		else
		{
			m_staticState.SetWindowTextW(L"상태 :");
		}
		m_buttonShowChildWnd.EnableWindow(false);

		m_buttonTopMost.EnableWindow(false);
		m_buttonTopMost.SetWindowTextW(L"항상 최상위로");

		m_buttonHide.EnableWindow(false);
		m_buttonHide.SetWindowTextW(L"숨기기");

		m_buttonClose.EnableWindow(false);

		m_buttonDestroy.EnableWindow(false);

		m_buttonFixSize.EnableWindow(false);
		m_buttonFixSize.SetWindowTextW(L"크기 고정");

		m_buttonFixPos.EnableWindow(false);
		m_buttonFixPos.SetWindowTextW(L"위치 고정");
	}
	else // 윈도우가 정상일시
	{
		CString text;
		m_listWnd.GetText(index, text);
		m_editText.SetWindowTextW(text);

		m_staticState.SetWindowTextW(L"상태 : 정상");

		m_buttonShowChildWnd.EnableWindow(true);

		m_buttonTopMost.EnableWindow(true);
		if (GetWindowLongW(pSelectedWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_TOPMOST)
		{
			m_buttonTopMost.SetWindowTextW(L"항상 최상위 취소");
		}
		else
		{
			m_buttonTopMost.SetWindowTextW(L"항상 최상위로");
		}

		if (pSelectedWnd != m_pParentWnd)
		{
			m_buttonHide.EnableWindow(true);
			if (pSelectedWnd->IsWindowVisible())
			{
				m_buttonHide.SetWindowTextW(L"숨기기");
			}
			else
			{
				m_buttonHide.SetWindowTextW(L"보이기");
			}
		}
		else
		{
			m_buttonHide.EnableWindow(false);
			m_buttonHide.SetWindowTextW(L"숨기기");
		}

		m_buttonClose.EnableWindow(true);

		m_buttonDestroy.EnableWindow(true);

		if (GetWindowLongW(pSelectedWnd->GetSafeHwnd(), GWL_STYLE) & WS_SIZEBOX)
		{
			m_buttonFixSize.EnableWindow(true);
			// 작업중
			m_buttonFixSize.SetWindowTextW(L"크기 고정");
		}
		else
		{
			m_buttonFixSize.EnableWindow(false);
			m_buttonFixSize.SetWindowTextW(L"크기 고정");
		}

		m_buttonFixPos.EnableWindow(true);
		// 작업중
	}
}
	
// 윈도우 목록 선택 변경(클릭)
void CDlgWindow::OnLbnSelchangeWindowListWnd()
{
	RefreshControls(m_listWnd.GetCurSel());
}
// 윈도우 목록 더블클릭
void CDlgWindow::OnLbnDblclkWindowListWnd()
{
	CWnd *pNowWnd = GetSafeWndFromListIndex(m_listWnd.GetCurSel());
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	// 최소화상태일시 끌어올린다.
	if (pNowWnd->IsIconic())
	{
		pNowWnd->ShowWindow(SW_SHOWNORMAL);
	}
	m_pParentWnd->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	pNowWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_pParentWnd->SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

// 자식윈도우 보기 버튼 클릭
void CDlgWindow::OnBnClickedWindowButtonShowChildWnd()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	CDlgShowChildWnd dlg(pNowWnd->GetSafeHwnd());
	dlg.DoModal();
}
// 항상 최상위로 버튼 클릭
void CDlgWindow::OnBnClickedWindowButtonTopmost()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	// 항상 최상위 취소
	if (GetWindowLongW(pNowWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_TOPMOST)
	{
		// 항상 최상위상태를 취소한다.
		pNowWnd->SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		// 이 윈도우를 맨 위로 올린다.
		m_pParentWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		RefreshControls(index);
	}
	else // 항상 최상위로
	{
		if (!Function::SetWindowTopMost(pNowWnd))
		{
			MessageBoxW(L"TOPMOST 스타일 설정에 실패하였습니다.");
		}
		RefreshControls(index);
	}

}
// 숨기기 버튼 클릭
void CDlgWindow::OnBnClickedWindowButtonHide()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	if (pNowWnd->IsWindowVisible()) // 숨기기
	{
		pNowWnd->ShowWindow(SW_HIDE);
		if (m_checkShowHiddenWnd == false)
		{
			RefreshWndList(0);
		}
		else
		{
			RefreshControls(index);
		}
	}
	else // 보이기
	{
		pNowWnd->ShowWindow(SW_SHOW);
		pNowWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		m_pParentWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		RefreshControls(index);
	}
}
// 프로세스 종료 버튼 클릭
void CDlgWindow::OnBnClickedWindowButtonDestroy()
{
	CWnd *pNowWnd = GetSafeWndFromListIndex(m_listWnd.GetCurSel());
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}
	if (MessageBoxW(L"정말로 종료하시겠습니까? 저장되지 않은 정보가 손실 될 수 있습니다.", NULL, MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}

	CString szExeName = Function::GetExeName(Function::FindProcessID(pNowWnd->GetSafeHwnd()));
	HANDLE hProcess = Function::GetProcessHandle(szExeName);
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(L"잘못 된 프로세스입니다.");
	}
	else if (!Function::SafeTerminateProcess(hProcess, 1))
	{
		MessageBoxW(L"프로세스 종료에 실패하였습니다.");
	}
	RefreshWndList(0);
}
// 종료 버튼 클릭
void CDlgWindow::OnBnClickedWindowButtonClose()
{
	CWnd *pNowWnd = GetSafeWndFromListIndex(m_listWnd.GetCurSel());
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	if (MessageBoxW(L"정말로 종료하시겠습니까?", NULL, MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	pNowWnd->SendMessageW(WM_SYSCOMMAND, SC_CLOSE);
	if (IsWindow(pNowWnd->GetSafeHwnd()))
	{
		pNowWnd->SendMessageW(WM_CLOSE);
	}

	RefreshWndList(0);

}
// 크기 고정 // 작업중
void CDlgWindow::OnBnClickedWindowButtonFixsize()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	DWORD dwProcessID = Function::FindProcessID(pNowWnd->GetSafeHwnd());
	/*
	if (IsSizeFixed(pNowWnd->GetSafeHwnd())) // 해제
	{
	ResetWndProc(pNowWnd->GetSafeHwnd());
	Function::EjectDll(dwProcessID, L"Hook.dll");
	}
	else // 설정
	{
	MessageBoxW(L"이 프로그램이 예상치 못하게 종료되었을 시 해제가 불가능 할 수 있습니다. 유의하시기 바랍니다.", L"경고", MB_OK);

	Function::InjectDll(dwProcessID, L"Hook.dll");
	SetSubWndProc(pNowWnd->GetSafeHwnd(), FIXSIZE);
	}*/
	RefreshControls(index);
}
// 위치 고정 // 작업중
void CDlgWindow::OnBnClickedWindowButtonFixpos()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // 윈도우가 비정상일시
	{
		MessageBoxW(L"윈도우 검색에 실패했습니다.");
		RefreshWndList(0);
		return;
	}

	DWORD dwProcessID = Function::FindProcessID(pNowWnd->GetSafeHwnd());

	/*if (IsSizeFixed(pNowWnd->GetSafeHwnd())) // 해제
	{
	ResetWndProc(pNowWnd->GetSafeHwnd());
	Function::EjectDll(dwProcessID, L"Hook.dll");
	}
	else // 설정
	{
	MessageBoxW(L"이 프로그램이 예상치 못하게 종료되었을 시 해제가 불가능 할 수 있습니다. 유의하시기 바랍니다.", L"경고", MB_OK);

	Function::InjectDll(dwProcessID, L"Hook.dll");
	SetSubWndProc(pNowWnd->GetSafeHwnd(), FIXPOS);
	}*/
	RefreshControls(index);
}
