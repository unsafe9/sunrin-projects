
// Devaide.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDevaide:
// �� Ŭ������ ������ ���ؼ��� Devaide.cpp�� �����Ͻʽÿ�.
//

class CDevaide : public CWinApp
{
public:
	CDevaide();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
	LPCWSTR m_lpszAppName;
	
public:
	LPCWSTR GetAppName(void) const{ return m_lpszAppName; }

};

extern CDevaide theApp;
