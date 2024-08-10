#pragma once

#include "afxwin.h"
#include "StartupManager.h"

class CStartDropListBox : public CListBox
{
public:
	CStartDropListBox();
	~CStartDropListBox();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);

public:
	virtual BOOL DestroyWindow();

public:
	bool AddDataFromRegEnum(HKEY hKey, LPCWSTR lpSubKey, REGSAM dwFlag);
	bool RefreshList();

};

