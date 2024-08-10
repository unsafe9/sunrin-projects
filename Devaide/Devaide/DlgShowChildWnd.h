#pragma once
#include "afxwin.h"


// DlgShowChildWnd 대화 상자입니다.

class CDlgShowChildWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowChildWnd)

public:
	CDlgShowChildWnd(HWND datahWnd, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgShowChildWnd();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_WINDOW_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
