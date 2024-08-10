#include "stdafx.h"
#include "StartDropListBox.h"

#include <iostream>

CStartDropListBox::CStartDropListBox(){}
CStartDropListBox::~CStartDropListBox(){}

BEGIN_MESSAGE_MAP(CStartDropListBox, CListBox)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CStartDropListBox::DestroyWindow()
{
	for (int i = 0; i < GetCount(); ++i)
	{
		delete (StartupManager*)GetItemDataPtr(i);
	}

	return CListBox::DestroyWindow();
}

bool CStartDropListBox::AddDataFromRegEnum(HKEY hKey, LPCWSTR lpSubKey, REGSAM dwFlag)
{
	LPWSTR szValueName, szData;
	DWORD cbValueName, cbData;
	DWORD cbMaxValueName, cbMaxData;
	DWORD dwType;
	HKEY hkResult;

	switch (RegOpenKeyExW(hKey, lpSubKey, 0, KEY_READ | dwFlag, &hkResult))
	{
	case ERROR_SUCCESS:
		RegQueryInfoKeyW(hkResult, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &cbMaxValueName, &cbMaxData, NULL, NULL);
		szValueName = new WCHAR[cbValueName = ++cbMaxValueName];
		szData = new WCHAR[cbData = ++cbMaxData];

		for (int i = 0; RegEnumValueW(hkResult, i, szValueName, &cbValueName, NULL, &dwType, (LPBYTE)szData, &cbData) != ERROR_NO_MORE_ITEMS; ++i)
		{
			if (dwType != REG_SZ)
			{
				continue;
			}
			SetItemDataPtr(AddString(szValueName),
				StartupManager::CreateREG(hKey, szValueName, lpSubKey, dwFlag, szData));

			cbValueName = cbMaxValueName;
			cbData = cbMaxData;
		}
		RegCloseKey(hkResult);

		delete[] szValueName;
		delete[] szData;

		return true;

	case ERROR_FILE_NOT_FOUND:
		return true;

	}
	return false;
}
bool CStartDropListBox::RefreshList()
{
	for (int i = 0; i < GetCount(); ++i)
	{
		delete (StartupManager*)GetItemDataPtr(i);
	}
	ResetContent();

	/* HKEY_CURRENT_USER Run */
	AddDataFromRegEnum(HKEY_CURRENT_USER, StartupManager::REG_STARTUP_PATH_RUN, 0);
	/* HKEY_CURRENT_USER RunOnce */
	AddDataFromRegEnum(HKEY_CURRENT_USER, StartupManager::REG_STARTUP_PATH_RUNONCE, 0);
	/* HKEY_LOCAL_MACHINE 64bit Run */
	AddDataFromRegEnum(HKEY_LOCAL_MACHINE, StartupManager::REG_STARTUP_PATH_RUN, KEY_WOW64_64KEY);
	/* HKEY_LOCAL_MACHINE 64bit RunOnce */
	AddDataFromRegEnum(HKEY_LOCAL_MACHINE, StartupManager::REG_STARTUP_PATH_RUNONCE, KEY_WOW64_64KEY);
	/* HKEY_LOCAL_MACHINE 32bit Run */
	AddDataFromRegEnum(HKEY_LOCAL_MACHINE, StartupManager::REG_STARTUP_PATH_RUN, KEY_WOW64_32KEY);
	/* HKEY_LOCAL_MACHINE 32bit RunOnce */
	AddDataFromRegEnum(HKEY_LOCAL_MACHINE, StartupManager::REG_STARTUP_PATH_RUNONCE, KEY_WOW64_32KEY);

	/* STARTUP */
	// 디렉토리 경로저장
	WCHAR szPathBuf[_MAX_PATH + 1] = { 0, };
	StartupManager::DIR_STARTUP_PATH(szPathBuf);
	PathAddBackslashW(szPathBuf);
	CString szPath(szPathBuf);

	WIN32_FIND_DATAW fData;
	HANDLE hSearch = FindFirstFileW(szPath + L"*.*", &fData);
	if (hSearch == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(L"시작프로그램 폴더의 검색에 실패하였습니다.");
		return false;
	}
	do
	{
		if (!(fData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && lstrcmpW(fData.cFileName, L".") && lstrcmpW(fData.cFileName, L".."))
		{
			WCHAR szName[_MAX_FNAME] = { 0, };
			lstrcpyW(szName, fData.cFileName);
			PathRenameExtensionW(szName, L"");

			WCHAR szFilePath[_MAX_PATH];
			lstrcpyW(szFilePath, szPath);
			PathAppendW(szFilePath, fData.cFileName);

			SetItemDataPtr(AddString(fData.cFileName),
				StartupManager::CreateFILE(szName, szFilePath));
		}
	} while (FindNextFileW(hSearch, &fData));
	FindClose(hSearch);

	return true;
}
void CStartDropListBox::OnDropFiles(HDROP hDropInfo)
{
	MessageBoxW(L"drag");

	// Drag&Drop된 파일, 폴더의 갯수 저장 // -1 == 0xffffffff
	UINT uiFileNum = DragQueryFileW(hDropInfo, 0xffffffff, NULL, 0);
	for (UINT i = 0; i < uiFileNum; i++)
	{
		// Drag&Drop된 파일, 폴더의 절대경로 저장
		WCHAR szPath[_MAX_PATH];
		DragQueryFileW(hDropInfo, i, szPath, _MAX_PATH);

		// 폴더일시
		if (PathIsDirectoryW(szPath))
		{
			WCHAR szName[_MAX_FNAME] = { 0, };
			lstrcpyW(szName, PathFindFileNameW(szPath));
			PathRenameExtensionW(szName, L"");

			WCHAR szShortcutPath[_MAX_PATH] = { 0, };
			StartupManager::DIR_STARTUP_PATH(szShortcutPath);
			PathAppendW(szShortcutPath, szName);
			PathRenameExtensionW(szShortcutPath, L".lnk");

			StartupManager *pSM = StartupManager::CreateLNK(szName, szShortcutPath, szPath);
			if (pSM->Register())
			{
				SetItemDataPtr(AddString(pSM->GetName()), pSM);
			}
			else
			{
				MessageBoxW(L"등록에 실패하였습니다.");
			}
		}
		else
		{
			WCHAR szName[_MAX_PATH] = { 0, };
			lstrcpyW(szName, PathFindFileNameW(szPath));
			PathRenameExtensionW(szName, L"");

			StartupManager *pSM = StartupManager::CreateREG(HKEY_CURRENT_USER, szName, StartupManager::REG_STARTUP_PATH_RUN, NULL, szPath);
			if (pSM->Register())
			{
				SetItemDataPtr(AddString(pSM->GetName()), pSM);
			}
			else
			{
				MessageBoxW(L"등록에 실패하였습니다.");
			}
		}
	}

	DragFinish(hDropInfo);
	CListBox::OnDropFiles(hDropInfo);
}


