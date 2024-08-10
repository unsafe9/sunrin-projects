// DlgGraph.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Devaide.h"
#include "DlgGraph.h"
#include "afxdialogex.h"


// CDlgGraph 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgGraph, CDialogEx)

CDlgGraph::CDlgGraph(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgGraph::IDD, pParent)
{

}

CDlgGraph::~CDlgGraph()
{
}

void CDlgGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgGraph, CDialogEx)
END_MESSAGE_MAP()


// CDlgGraph 메시지 처리기입니다.
