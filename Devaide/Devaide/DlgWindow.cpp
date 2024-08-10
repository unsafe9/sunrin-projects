// DlgWindow.cpp : ���� �����Դϴ�.
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

// CDlgWindow ��ȭ �����Դϴ�.

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


// EnumWindows�ݹ��Լ�
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	CDlgWindow &dlgWindow = dynamic_cast<CDlgMain*>(AfxGetMainWnd())->m_dlgWindow;

	if (dlgWindow.m_checkShowHiddenWnd ? 1 : IsWindowVisible(hWnd)) // ������������ ���̱� �ɼ� ����
	{
		// �̸� ����
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
		// ǥ��
		switch (dlgWindow.m_radioListValueName)
		{
		case 0: // �������
			GetWindowTextW(hWnd, szText, sizeof(szText));
			break;

		case 1: // Ŭ������
			GetClassNameW(hWnd, szText, sizeof(szText));
			break;

		case 2: // ���μ�����
			DWORD dwProcessID;
			GetWindowThreadProcessId(hWnd, &dwProcessID);
			lstrcpyW(szText, Function::GetExeName(dwProcessID));
			break;
		}
		lstrcatW(szString, szText);

		// ����
		if (dlgWindow.m_checkShowNoNameWnd ? 1 : (lstrlenW(szText) > 0))
		{
			int index = 0, count = dlgWindow.m_listWnd.GetCount();
			switch (dlgWindow.m_radioSort)
			{
			case 0: // �̸�����
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
							++index; // ������
						}
					}
				}
				break;

			case 1: // ȭ�����
				index = dlgWindow.m_checkAscendingSort ? 0 : count;
				break;
			}
			// ����
			dlgWindow.m_listWnd.InsertString(index, szString);
			dlgWindow.m_listWnd.SetItemData(index, reinterpret_cast<DWORD>(hWnd));
		}
	}
	return true;
}

// ����� ���� �ڵ�κ��� �����ϰ� CWnd Ŭ�������� �����͸� ��´�.
CWnd* CDlgWindow::GetSafeWndFromListIndex(int index) const
{
	if (index == LB_ERR)
	{
		return NULL;
	}
	HWND hWnd = GetHandleFromList(index);
	return (IsWindow(hWnd) ? FromHandle(hWnd) : NULL);
}



// CDlgWindow �޽��� ó�����Դϴ�.

// ���� ����
void CDlgWindow::OnCancel(){/*CDialogEx::OnCancel();*/ }
// ���ΰ�ħ
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

	// �ڵ鰪�� ���ΰ�ħ ���� �������� ã�´�.
	while (index <= count && GetHandleFromList(index++) != data);

	// �����ҽ� Ŀ���� �����Ѵ�.
	if (index <= count)
	{
		m_listWnd.SetCurSel(--index);
	}

	RefreshControls(index);
}
// ���ΰ�ħ ��ư Ŭ��
void CDlgWindow::OnBnClickedWindowButtonRefresh()
{
	RefreshWndList(0);
}
// ������������
void CDlgWindow::OnBnClickedWindowCheckAscending()
{
	RefreshWndList(0);
}
// �̸����� ������ ǥ��
void CDlgWindow::OnBnClickedWindowCheckNoname()
{
	RefreshWndList(0);
}
// ������ ������ ǥ��
void CDlgWindow::OnBnClickedWindowCheckHidden()
{
	RefreshWndList(0);
}
// �ڵ鰪 ǥ��
void CDlgWindow::OnBnClickedWindowCheckHandle()
{
	RefreshWndList(0);
}


// ��Ʈ�ѵ��� �����쿡 �°� �����Ѵ�.
void CDlgWindow::RefreshControls(int index)
{
	CWnd *pSelectedWnd = GetSafeWndFromListIndex(index);
	m_editText.Clear();

	// �����츦 �������� �ʾ����� �Ǵ� �������Ͻ�
	if (pSelectedWnd == NULL)
	{
		if (m_listWnd.GetCurSel() != LB_ERR)
		{
			m_staticState.SetWindowTextW(L"���� : ������");
		}
		else
		{
			m_staticState.SetWindowTextW(L"���� :");
		}
		m_buttonShowChildWnd.EnableWindow(false);

		m_buttonTopMost.EnableWindow(false);
		m_buttonTopMost.SetWindowTextW(L"�׻� �ֻ�����");

		m_buttonHide.EnableWindow(false);
		m_buttonHide.SetWindowTextW(L"�����");

		m_buttonClose.EnableWindow(false);

		m_buttonDestroy.EnableWindow(false);

		m_buttonFixSize.EnableWindow(false);
		m_buttonFixSize.SetWindowTextW(L"ũ�� ����");

		m_buttonFixPos.EnableWindow(false);
		m_buttonFixPos.SetWindowTextW(L"��ġ ����");
	}
	else // �����찡 �����Ͻ�
	{
		CString text;
		m_listWnd.GetText(index, text);
		m_editText.SetWindowTextW(text);

		m_staticState.SetWindowTextW(L"���� : ����");

		m_buttonShowChildWnd.EnableWindow(true);

		m_buttonTopMost.EnableWindow(true);
		if (GetWindowLongW(pSelectedWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_TOPMOST)
		{
			m_buttonTopMost.SetWindowTextW(L"�׻� �ֻ��� ���");
		}
		else
		{
			m_buttonTopMost.SetWindowTextW(L"�׻� �ֻ�����");
		}

		if (pSelectedWnd != m_pParentWnd)
		{
			m_buttonHide.EnableWindow(true);
			if (pSelectedWnd->IsWindowVisible())
			{
				m_buttonHide.SetWindowTextW(L"�����");
			}
			else
			{
				m_buttonHide.SetWindowTextW(L"���̱�");
			}
		}
		else
		{
			m_buttonHide.EnableWindow(false);
			m_buttonHide.SetWindowTextW(L"�����");
		}

		m_buttonClose.EnableWindow(true);

		m_buttonDestroy.EnableWindow(true);

		if (GetWindowLongW(pSelectedWnd->GetSafeHwnd(), GWL_STYLE) & WS_SIZEBOX)
		{
			m_buttonFixSize.EnableWindow(true);
			// �۾���
			m_buttonFixSize.SetWindowTextW(L"ũ�� ����");
		}
		else
		{
			m_buttonFixSize.EnableWindow(false);
			m_buttonFixSize.SetWindowTextW(L"ũ�� ����");
		}

		m_buttonFixPos.EnableWindow(true);
		// �۾���
	}
}
	
// ������ ��� ���� ����(Ŭ��)
void CDlgWindow::OnLbnSelchangeWindowListWnd()
{
	RefreshControls(m_listWnd.GetCurSel());
}
// ������ ��� ����Ŭ��
void CDlgWindow::OnLbnDblclkWindowListWnd()
{
	CWnd *pNowWnd = GetSafeWndFromListIndex(m_listWnd.GetCurSel());
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	// �ּ�ȭ�����Ͻ� ����ø���.
	if (pNowWnd->IsIconic())
	{
		pNowWnd->ShowWindow(SW_SHOWNORMAL);
	}
	m_pParentWnd->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	pNowWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_pParentWnd->SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

// �ڽ������� ���� ��ư Ŭ��
void CDlgWindow::OnBnClickedWindowButtonShowChildWnd()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	CDlgShowChildWnd dlg(pNowWnd->GetSafeHwnd());
	dlg.DoModal();
}
// �׻� �ֻ����� ��ư Ŭ��
void CDlgWindow::OnBnClickedWindowButtonTopmost()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	// �׻� �ֻ��� ���
	if (GetWindowLongW(pNowWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_TOPMOST)
	{
		// �׻� �ֻ������¸� ����Ѵ�.
		pNowWnd->SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		// �� �����츦 �� ���� �ø���.
		m_pParentWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		RefreshControls(index);
	}
	else // �׻� �ֻ�����
	{
		if (!Function::SetWindowTopMost(pNowWnd))
		{
			MessageBoxW(L"TOPMOST ��Ÿ�� ������ �����Ͽ����ϴ�.");
		}
		RefreshControls(index);
	}

}
// ����� ��ư Ŭ��
void CDlgWindow::OnBnClickedWindowButtonHide()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	if (pNowWnd->IsWindowVisible()) // �����
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
	else // ���̱�
	{
		pNowWnd->ShowWindow(SW_SHOW);
		pNowWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		m_pParentWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		RefreshControls(index);
	}
}
// ���μ��� ���� ��ư Ŭ��
void CDlgWindow::OnBnClickedWindowButtonDestroy()
{
	CWnd *pNowWnd = GetSafeWndFromListIndex(m_listWnd.GetCurSel());
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}
	if (MessageBoxW(L"������ �����Ͻðڽ��ϱ�? ������� ���� ������ �ս� �� �� �ֽ��ϴ�.", NULL, MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}

	CString szExeName = Function::GetExeName(Function::FindProcessID(pNowWnd->GetSafeHwnd()));
	HANDLE hProcess = Function::GetProcessHandle(szExeName);
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(L"�߸� �� ���μ����Դϴ�.");
	}
	else if (!Function::SafeTerminateProcess(hProcess, 1))
	{
		MessageBoxW(L"���μ��� ���ῡ �����Ͽ����ϴ�.");
	}
	RefreshWndList(0);
}
// ���� ��ư Ŭ��
void CDlgWindow::OnBnClickedWindowButtonClose()
{
	CWnd *pNowWnd = GetSafeWndFromListIndex(m_listWnd.GetCurSel());
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	if (MessageBoxW(L"������ �����Ͻðڽ��ϱ�?", NULL, MB_OKCANCEL) == IDCANCEL)
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
// ũ�� ���� // �۾���
void CDlgWindow::OnBnClickedWindowButtonFixsize()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	DWORD dwProcessID = Function::FindProcessID(pNowWnd->GetSafeHwnd());
	/*
	if (IsSizeFixed(pNowWnd->GetSafeHwnd())) // ����
	{
	ResetWndProc(pNowWnd->GetSafeHwnd());
	Function::EjectDll(dwProcessID, L"Hook.dll");
	}
	else // ����
	{
	MessageBoxW(L"�� ���α׷��� ����ġ ���ϰ� ����Ǿ��� �� ������ �Ұ��� �� �� �ֽ��ϴ�. �����Ͻñ� �ٶ��ϴ�.", L"���", MB_OK);

	Function::InjectDll(dwProcessID, L"Hook.dll");
	SetSubWndProc(pNowWnd->GetSafeHwnd(), FIXSIZE);
	}*/
	RefreshControls(index);
}
// ��ġ ���� // �۾���
void CDlgWindow::OnBnClickedWindowButtonFixpos()
{
	int index = m_listWnd.GetCurSel();
	CWnd *pNowWnd = GetSafeWndFromListIndex(index);
	if (pNowWnd == NULL) // �����찡 �������Ͻ�
	{
		MessageBoxW(L"������ �˻��� �����߽��ϴ�.");
		RefreshWndList(0);
		return;
	}

	DWORD dwProcessID = Function::FindProcessID(pNowWnd->GetSafeHwnd());

	/*if (IsSizeFixed(pNowWnd->GetSafeHwnd())) // ����
	{
	ResetWndProc(pNowWnd->GetSafeHwnd());
	Function::EjectDll(dwProcessID, L"Hook.dll");
	}
	else // ����
	{
	MessageBoxW(L"�� ���α׷��� ����ġ ���ϰ� ����Ǿ��� �� ������ �Ұ��� �� �� �ֽ��ϴ�. �����Ͻñ� �ٶ��ϴ�.", L"���", MB_OK);

	Function::InjectDll(dwProcessID, L"Hook.dll");
	SetSubWndProc(pNowWnd->GetSafeHwnd(), FIXPOS);
	}*/
	RefreshControls(index);
}
