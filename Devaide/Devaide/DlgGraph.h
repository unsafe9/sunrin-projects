#pragma once


// CDlgGraph 대화 상자입니다.

class CDlgGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGraph)

public:
	CDlgGraph(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgGraph();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_GRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
