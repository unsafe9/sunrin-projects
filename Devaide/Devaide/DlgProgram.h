#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "StartDropListBox.h"

// CDlgProgram 대화 상자입니다.

class CDlgProgram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProgram)

public:
	CDlgProgram(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgProgram();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_PROGRAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedProgramButtonStartAdd();
	afx_msg void OnLbnDblclkProgramListStart();
	afx_msg void OnLbnSelchangeProgramListStart();
	afx_msg void OnBnClickedProgramButtonStartDelete();

public:
	CButton m_buttonStartDelete;

	CStartDropListBox m_listStart;

};
