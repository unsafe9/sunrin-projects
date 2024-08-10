#pragma once

#include <Windows.h>

#include <shlwapi.h>

#include "StartupManager.h"

namespace Function
{
	HANDLE GetProcessHandle(LPCWSTR szFilename);
	bool SafeTerminateProcess(HANDLE hProcess, UINT uExitCode);

	DWORD FindProcessID(LPCWSTR szFilename);
	DWORD FindProcessID(HWND hWnd);

	bool InjectDll(DWORD dwProcessID, LPCWSTR szDllName);
	bool EjectDll(DWORD dwProcessID, LPCWSTR szDllName);
	
	HMODULE WINAPI GetRemoteModuleHandle(HANDLE hProcess, LPCWSTR lpModuleName);
	FARPROC WINAPI GetRemoteProcAddress(HANDLE hProcess, HMODULE hModule, LPCWSTR lpProcName, UINT Ordinal, BOOL UseOrdinal);

	CString GetExeName(DWORD dwProcessID);

	bool SetWindowTopMost(CWnd *pWnd);
	bool SetWindowTopMost(HWND hWnd);

	bool CreateShortcut(LPCWSTR szTargetPath, LPCWSTR szShortcutPath, LPCWSTR szDesc = NULL, LPCWSTR szArgument = NULL, LPCWSTR szIconPath = NULL, int iIconIndex = -1, WORD wHotkey = 0, int nShowCmd = SW_SHOW);
	CString GetShortcutTarget(const CString LinkFileName);

}
