// DlgProgram.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgProgram.h"
#include "afxdialogex.h"
#include "Function.h"


// CDlgProgram ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgProgram, CDialogEx)

CDlgProgram::CDlgProgram(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProgram::IDD, pParent){}

CDlgProgram::~CDlgProgram(){}

void CDlgProgram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRAM_BUTTON_START_DELETE, m_buttonStartDelete);
	DDX_Control(pDX, IDC_PROGRAM_LIST_START, m_listStart);
}


BEGIN_MESSAGE_MAP(CDlgProgram, CDialogEx)
	ON_BN_CLICKED(IDC_PROGRAM_BUTTON_START_ADD, &CDlgProgram::OnBnClickedProgramButtonStartAdd)
	ON_LBN_DBLCLK(IDC_PROGRAM_LIST_START, &CDlgProgram::OnLbnDblclkProgramListStart)
	ON_LBN_SELCHANGE(IDC_PROGRAM_LIST_START, &CDlgProgram::OnLbnSelchangeProgramListStart)
	ON_BN_CLICKED(IDC_PROGRAM_BUTTON_START_DELETE, &CDlgProgram::OnBnClickedProgramButtonStartDelete)
END_MESSAGE_MAP()


// CDlgProgram �޽��� ó�����Դϴ�.

void CDlgProgram::OnCancel(){/*CDialogEx::OnCancel();*/}

// ���̾�α� �ʱ�ȭ
BOOL CDlgProgram::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listStart.RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// �������α׷���� Ŭ��
void CDlgProgram::OnLbnSelchangeProgramListStart()
{
	if (m_listStart.GetCurSel() == LB_ERR)
	{
		m_buttonStartDelete.EnableWindow(false);
	}
	else
	{
		m_buttonStartDelete.EnableWindow(true);
	}
}
// �������α׷���� ����Ŭ��
void CDlgProgram::OnLbnDblclkProgramListStart()
{
	int index = m_listStart.GetCurSel();
	if (index != LB_ERR)
	{
		CString szItem;
		m_listStart.GetText(index, szItem);

		StartupManager *pSM = (StartupManager*)m_listStart.GetItemDataPtr(index);

		if (!pSM->IsRegistered())
		{
			MessageBoxW(L"��ϵǾ����� ���� �׸��Դϴ�.");
			m_listStart.RefreshList();
		}
		else
		{
			MessageBoxW(pSM->GetData(), szItem);
		}
	}
}
// �������α׷�������ư Ŭ��
void CDlgProgram::OnBnClickedProgramButtonStartDelete()
{
	int nCount = m_listStart.GetSelCount();
	if (nCount == LB_ERR)
	{
		return;
	}

	CArray<int, int> arySels;
	arySels.SetSize(nCount);
	m_listStart.GetSelItems(nCount, arySels.GetData());

	CString strBuf;
	strBuf.Empty();
	for (int i = 0; i < nCount; ++i)
	{
		CString strValueName;
		m_listStart.GetText(arySels[i], strValueName);
		strBuf += L"- " + strValueName + L"\n";
	}
	strBuf += L"\n������ �����Ͻðڽ��ϱ�?";
	if (MessageBoxW(strBuf, NULL, MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}

	for (int i = 0; i < nCount; ++i)
	{
		m_listStart.GetSelItems(m_listStart.GetSelCount(), arySels.GetData());

		CString strValueName;
		m_listStart.GetText(arySels[0], strValueName);
		
		StartupManager *pSM = (StartupManager*)m_listStart.GetItemDataPtr(arySels[0]);
		if (pSM->Unregister())
		{
			m_listStart.DeleteString(arySels[0]);
			delete pSM;
		}
		else
		{
			MessageBoxW(L"������ �����Ͽ����ϴ�.");
		}
	}
}
// �������α׷��߰���ư Ŭ��
void CDlgProgram::OnBnClickedProgramButtonStartAdd()
{

}

