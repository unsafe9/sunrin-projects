// DlgCalculator.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgCalculator.h"
#include "afxdialogex.h"


// CDlgCalculator 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgCalculator, CDialogEx)

CDlgCalculator::CDlgCalculator(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalculator::IDD, pParent)
{

}

CDlgCalculator::~CDlgCalculator(){}

void CDlgCalculator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCalculator, CDialogEx)
END_MESSAGE_MAP()


// CDlgCalculator 메시지 처리기입니다.
