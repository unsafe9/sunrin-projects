#pragma once

#include"Resource.h"

// CDlgCalculator ��ȭ �����Դϴ�.

class CDlgCalculator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalculator)

public:
	CDlgCalculator(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgCalculator();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_CALCULATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
