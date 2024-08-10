
// DlgMain.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"

#include "DlgCalculator.h"
#include "DlgWindow.h"
#include "DlgProgram.h"
#include "DlgGraph.h"
#include "DlgMemo.h"

// CDlgMain 대화 상자
class CDlgMain : public CDialogEx
{
// 생성입니다.
public:
	CDlgMain(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_MAIN };

// DDX/DDV 지원입니다.
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// 구현입니다.
protected:
	HICON m_hIcon;

// 생성된 메시지 맵 함수
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
