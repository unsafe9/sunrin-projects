#pragma once


// CDlgMemo 대화 상자입니다.

class CDlgMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemo)

public:
	CDlgMemo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgMemo();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_MEMO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
