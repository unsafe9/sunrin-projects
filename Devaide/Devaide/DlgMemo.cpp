// DlgMemo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgMemo.h"
#include "afxdialogex.h"


// CDlgMemo 대화 상자입니다.

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


// CDlgMemo 메시지 처리기입니다.
