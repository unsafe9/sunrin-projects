#pragma once


// CDlgGraph ��ȭ �����Դϴ�.

class CDlgGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGraph)

public:
	CDlgGraph(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgGraph();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_GRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
