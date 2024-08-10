// DlgShowChildWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgShowChildWnd.h"
#include "afxdialogex.h"

static CDlgShowChildWnd *pDlg;

// CDlgShowChildWnd ��ȭ �����Դϴ�.

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

// EnumWindows �ݹ��Լ�
BOOL CALLBACK ChildEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	WCHAR String[1024] = { 0, };

	switch (pDlg->m_radioListValueName)
	{
	case 0: // �������
		GetWindowTextW(hWnd, String, sizeof(String));
		break;

	case 1: // Ŭ������
		GetClassNameW(hWnd, String, sizeof(String));
		break;
	}
	pDlg->m_listChildWnd.SetItemData(
		pDlg->m_listChildWnd.AddString(String), 
		reinterpret_cast<DWORD>(hWnd));

	return TRUE;
}
// ����Ʈ ����
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

// CDlgShowChildWnd �޽��� ó�����Դϴ�.

// �ʱ�ȭ
BOOL CDlgShowChildWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	RefreshWndList(0);

	return TRUE;
}
// ���ΰ�ħ ��ư Ŭ��
void CDlgShowChildWnd::OnBnClickedWindowChildBtnRefresh()
{
	RefreshWndList(0);
}

// �پ��α� ����
void CDlgShowChildWnd::OnClose()
{
	// ��� ���̾�α׸� �����Ѵ�.
	EndDialog(IDCANCEL);
	CDialogEx::OnClose();
}
