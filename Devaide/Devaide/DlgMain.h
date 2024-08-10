
// DlgMain.h : ��� ����
//

#pragma once
#include "afxcmn.h"

#include "DlgCalculator.h"
#include "DlgWindow.h"
#include "DlgProgram.h"
#include "DlgGraph.h"
#include "DlgMemo.h"

// CDlgMain ��ȭ ����
class CDlgMain : public CDialogEx
{
// �����Դϴ�.
public:
	CDlgMain(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_MAIN };

// DDX/DDV �����Դϴ�.
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// �����Դϴ�.
protected:
	HICON m_hIcon;

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	afx_msg void OnMenuHelpView();
	afx_msg void OnMenuHelpAbout();
	
public:
	CTabCtrl m_mainTabCtrl;
	CDialogEx *m_pDlgShow;

	CDlgCalculator	m_dlgCalculator;
	CDlgWindow		m_dlgWindow;
	CDlgProgram		m_dlgProgram;
	CDlgGraph		m_dlgGraph;
	CDlgMemo		m_dlgMemo;

	HACCEL m_hAccel;
};
