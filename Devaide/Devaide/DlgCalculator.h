#pragma once

#include"Resource.h"

// CDlgCalculator 대화 상자입니다.

class CDlgCalculator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalculator)

public:
	CDlgCalculator(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgCalculator();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_CALCULATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
