// DlgMemo.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgMemo.h"
#include "afxdialogex.h"


// CDlgMemo ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgMemo, CDialogEx)

CDlgMemo::CDlgMemo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMemo::IDD, pParent)
{

}

CDlgMemo::~CDlgMemo()
{
}

void CDlgMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMemo, CDialogEx)
END_MESSAGE_MAP()


// CDlgMemo �޽��� ó�����Դϴ�.
