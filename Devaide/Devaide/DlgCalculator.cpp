// DlgCalculator.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgCalculator.h"
#include "afxdialogex.h"


// CDlgCalculator ��ȭ �����Դϴ�.

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


// CDlgCalculator �޽��� ó�����Դϴ�.
