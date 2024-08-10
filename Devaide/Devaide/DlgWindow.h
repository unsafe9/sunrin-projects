#pragma once
#include "afxwin.h"

#include "Resource.h"

// CDlgWindow 대화 상자입니다.

class CDlgWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWindow)

public:
	CDlgWindow(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgWindow();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_WINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnCancel();

public:
	afx_msg void OnBnClickedWindowCheckNoname();
	afx_msg void OnBnClickedWindowCheckHidden();
	afx_msg void OnBnClickedWindowCheckHandle();
	afx_msg void OnBnClickedWindowCheckAscending();

	afx_msg void OnLbnSelchangeWindowListWnd();
	afx_msg void OnLbnDblclkWindowListWnd();

	afx_msg void OnBnClickedWindowButtonRefresh();
	afx_msg void OnBnClickedWindowButtonShowChildWnd();
	afx_msg void OnBnClickedWindowButtonTopmost();
	afx_msg void OnBnClickedWindowButtonHide();
	afx_msg void OnBnClickedWindowButtonClose();
	afx_msg void OnBnClickedWindowButtonDestroy();
	afx_msg void OnBnClickedWindowButtonFixsize();
	afx_msg void OnBnClickedWindowButtonFixpos();

public:
	BOOL m_checkShowNoNameWnd;
	BOOL m_checkShowHiddenWnd;
	BOOL m_checkShowHandle;

	int m_radioListValueName;

	BOOL m_isListIncludeHandle;
	BOOL m_checkAscendingSort;
	int m_radioSort;

	CListBox m_listWnd;
	CEdit m_editText;
	CStatic m_staticState;

	CButton m_buttonShowChildWnd;
	CButton m_buttonTopMost;
	CButton m_buttonHide;
	CButton m_buttonClose;
	CButton m_buttonDestroy;
	CButton m_buttonFixSize;
	CButton m_buttonFixPos;

public:
	CWnd* GetSafeWndFromListIndex(int index) const;
	void RefreshWndList(UINT value);
	void RefreshControls(int index);

private:
	inline HWND GetHandleFromList(int index) const
	{
		return (HWND)m_listWnd.GetItemData(index);
	}

};
