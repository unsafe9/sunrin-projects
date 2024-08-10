#include "stdafx.h"
#include "StartupManager.h"
#include "Function.h"

LPCWSTR StartupManager::REG_STARTUP_PATH_RUN = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
LPCWSTR StartupManager::REG_STARTUP_PATH_RUNONCE = L"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";

StartupManager::StartupManager() : 
m_hKey(NULL), m_dwFlag(NULL),
m_szData(L""), m_szName(L""), m_szValuePath(L""){}
StartupManager::~StartupManager(){}

StartupManager* StartupManager::CreateFILE(LPCWSTR lpszName, LPCWSTR lpszPath)
{
	StartupManager *pSM = new StartupManager();

	pSM->m_szName.Format(L"%ws", lpszName ? lpszName : L"");
	pSM->m_szValuePath.Format(L"%ws", lpszPath ? lpszPath : L"");
	
	pSM->m_type = SMT_FILE;

	return pSM;
}
StartupManager* StartupManager::CreateLNK(LPCWSTR lpszName, LPCWSTR lpszShortcutPath, LPCWSTR lpszTargetPath)
{
	StartupManager *pSM = new StartupManager();

	pSM->m_szName.Format(L"%ws", lpszName ? lpszName : L"");
	pSM->m_szValuePath.Format(L"%ws", lpszShortcutPath ? lpszShortcutPath : L"");
	pSM->m_szData.Format(L"%ws", lpszTargetPath ? lpszTargetPath : L"");

	pSM->m_type = SMT_LNK;

	return pSM;
}
StartupManager* StartupManager::CreateREG(HKEY hKey, LPCWSTR lpszName, LPCWSTR lpszRegPath, REGSAM dwFlag, LPCWSTR lpszData)
{
	StartupManager *pSM = new StartupManager();

	pSM->m_hKey = hKey;
	pSM->m_szName.Format(L"%ws", lpszName ? lpszName : L"");
	pSM->m_szValuePath.Format(L"%ws", lpszRegPath ? lpszRegPath : L"");
	pSM->m_dwFlag = dwFlag;
	pSM->m_szData.Format(L"%ws", lpszData ? lpszData : L"");

	pSM->m_type = SMT_REG;

	return pSM;
}

bool StartupManager::Register(void)
{
	if (IsRegistered())
	{
		return false;
	}
	switch (m_type)
	{
	case SMT_REG:
		return SHRegWriteString(m_hKey, m_szValuePath, m_szName, m_szData);

	case SMT_LNK:
		return Function::CreateShortcut(m_szData, m_szValuePath);

	}
	return false;
}
bool StartupManager::Unregister(void)
{
	if (!IsRegistered())
	{
		return false;
	}
	switch (m_type)
	{
	case SMT_REG:
		return SHRegDelValue(m_hKey, m_szValuePath, m_szName);

	case SMT_LNK:
	case SMT_FILE:
		return DeleteFileW(m_szValuePath) ? true : false;

	}
	return false;
}
bool StartupManager::IsRegistered(void)
{
	WCHAR szBuf[_MAX_PATH] = { 0, };
	
	switch (m_type)
	{
	case SMT_REG:
		return SHRegReadString(m_hKey, m_szValuePath, m_szName, L"", szBuf, MAX_PATH) && lstrcmpW(szBuf, L"") != 0;

	case SMT_LNK:
	case SMT_FILE:
		return _waccess(m_szValuePath, 0) == 0;

	}
	return false;
}

bool StartupManager::SHRegWriteString(HKEY hKey, LPCWSTR lpKey, LPCWSTR lpValue, LPCWSTR lpData)
{
	HKEY hkResult;
	if (RegCreateKeyExW(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | m_dwFlag, NULL, &hkResult, NULL) != ERROR_SUCCESS)
	{
		return false;
	}
	if (RegSetValueExW(hkResult, lpValue, 0, REG_SZ, (LPBYTE)lpData, (lstrlenW(lpData) + 1) * sizeof(WCHAR)) != ERROR_SUCCESS)
	{
		RegCloseKey(hkResult);
		return false;
	}

	RegCloseKey(hkResult);
	return true;
}
bool StartupManager::SHRegDelValue(HKEY hKey, LPCWSTR lpKey, LPCWSTR lpValue)
{
	HKEY hkResult;
	if (RegOpenKeyExW(hKey, lpKey, 0, KEY_SET_VALUE | m_dwFlag, &hkResult) != ERROR_SUCCESS)
	{
		return false;
	}
	if (RegDeleteValueW(hkResult, lpValue) != ERROR_SUCCESS)
	{
		RegCloseKey(hkResult);
		return false;
	}

	RegCloseKey(hkResult);
	return true;
}
bool StartupManager::SHRegReadString(HKEY hKey, LPCWSTR lpKey, LPCWSTR lpszValue, LPCWSTR lpszDefault, LPWSTR lpszRet, DWORD nSize)
{
	HKEY hkResult;
	DWORD dwDisp;
	if (RegCreateKeyExW(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | m_dwFlag, NULL, &hkResult, &dwDisp) != ERROR_SUCCESS)
	{
		lstrcpyW(lpszRet, lpszDefault);
		return false;
	}

	DWORD cbSize = nSize * sizeof(WCHAR);
	if (RegQueryValueExW(hkResult, lpszValue, 0, NULL, (LPBYTE)lpszRet, &cbSize) != ERROR_SUCCESS)
	{
		lstrcpyW(lpszRet, lpszDefault);
		RegCloseKey(hkResult);
		return false;
	}

	RegCloseKey(hkResult);
	return true;
}
