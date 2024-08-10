// DlgProgram.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgProgram.h"
#include "afxdialogex.h"
#include "Function.h"


// CDlgProgram 대화 상자입니다.

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


// CDlgProgram 메시지 처리기입니다.

void CDlgProgram::OnCancel(){/*CDialogEx::OnCancel();*/}

// 다이얼로그 초기화
BOOL CDlgProgram::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listStart.RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// 시작프로그램목록 클릭
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
// 시작프로그램목록 더블클릭
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
			MessageBoxW(L"등록되어있지 않은 항목입니다.");
			m_listStart.RefreshList();
		}
		else
		{
			MessageBoxW(pSM->GetData(), szItem);
		}
	}
}
// 시작프로그램삭제버튼 클릭
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
	strBuf += L"\n정말로 삭제하시겠습니까?";
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
			MessageBoxW(L"삭제에 실패하였습니다.");
		}
	}
}
// 시작프로그램추가버튼 클릭
void CDlgProgram::OnBnClickedProgramButtonStartAdd()
{

}

