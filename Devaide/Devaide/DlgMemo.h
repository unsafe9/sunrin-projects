#pragma once


// CDlgMemo ��ȭ �����Դϴ�.

class CDlgMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemo)

public:
	CDlgMemo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgMemo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_MEMO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
