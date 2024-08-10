#pragma once
#include "afxwin.h"


// DlgShowChildWnd ��ȭ �����Դϴ�.

class CDlgShowChildWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowChildWnd)

public:
	CDlgShowChildWnd(HWND datahWnd, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgShowChildWnd();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_WINDOW_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedWindowChildBtnRefresh();

public:
	CListBox m_listChildWnd;

	int m_radioListValueName;

	HWND m_datahWnd;

public:
	void RefreshWndList(UINT value);
	afx_msg void OnClose();
};
