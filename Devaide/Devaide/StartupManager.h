#pragma once

#include <Windows.h>

class StartupManager
{
public:
	enum Type
	{
		SMT_REG,
		SMT_FILE,
		SMT_LNK,
	};

private:
	HKEY m_hKey; // 레지스트리 키 핸들
	CString m_szName; // 저장되는 이름(확장자X)
	CString m_szValuePath; // 파일 절대경로
	CString m_szData; // 실행되는(타겟)파일 절대경로
	REGSAM m_dwFlag; // 32, 64비트
	
	StartupManager::Type m_type;

public:
	static LPCWSTR REG_STARTUP_PATH_RUN;
	static LPCWSTR REG_STARTUP_PATH_RUNONCE;
	static bool DIR_STARTUP_PATH(LPWSTR lpszBuf)
	{
		return SHGetSpecialFolderPathW(NULL, lpszBuf, CSIDL_STARTUP, 0) ? true : false;
	}

private:
	StartupManager(void);

public:
	static StartupManager* CreateFILE(LPCWSTR lpszName, LPCWSTR lpszPath);
	static StartupManager* CreateLNK(LPCWSTR lpszName, LPCWSTR lpszShortcutPath, LPCWSTR lpszTargetPath);
	static StartupManager* CreateREG(HKEY hKey, LPCWSTR lpszName, LPCWSTR lpszRegPath, REGSAM dwFlag, LPCWSTR lpszData);
	
	~StartupManager();

public:
	bool Register(void);
	bool Unregister(void);

	bool IsRegistered(void);

private:
	bool SHRegWriteString(HKEY hKey, LPCWSTR lpszKey, LPCWSTR lpszValue, LPCWSTR lpszData);
	bool SHRegDelValue(HKEY hKey, LPCWSTR lpszKey, LPCWSTR lpszValue);
	bool SHRegReadString(HKEY hKey, LPCWSTR lpszKey, LPCWSTR lpszValue, LPCWSTR lpszDefault, LPWSTR lpszRet, DWORD nSize);

public:
	HKEY GetHKEY(void) const
	{
		return m_hKey;
	}

	LPCWSTR GetName(void) const
	{
		return m_szName;
	}

	LPCWSTR GetShortcutPath(void) const
	{
		return m_szValuePath;
	}
	LPCWSTR GetRegPath(void) const
	{
		return m_szValuePath;
	}
	LPCWSTR GetPath(void) const
	{
		return m_szValuePath;
	}

	LPCWSTR GetData(void) const
	{
		return m_szData;
	}
	LPCWSTR GetTargetPath(void) const
	{
		return m_szData;
	}

	REGSAM GetFlag(void) const
	{
		return m_dwFlag;
	}

	StartupManager::Type GetType(void) const
	{
		return m_type;
	}
	
};
