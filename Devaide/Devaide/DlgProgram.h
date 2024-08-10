#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "StartDropListBox.h"

// CDlgProgram ��ȭ �����Դϴ�.

class CDlgProgram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProgram)

public:
	CDlgProgram(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgProgram();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_PROGRAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
