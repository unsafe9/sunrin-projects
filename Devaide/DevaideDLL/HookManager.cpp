#include"HookManager.h"

HookManager::HookManager(void) : hHook(NULL), hServer(NULL){}
HookManager::~HookManager(){}

BOOL HookManager::SetHook(HWND hWnd, int idHook, HOOKPROC hookProc)
{
	// Set Hook Server
	hHook = SetWindowsHookExW(idHook, hookProc,
		(HINSTANCE)GetModuleHandleW(NULL), 0);
	if (hHook == NULL)
	{
		return FALSE;
	}
	hServer = hWnd;
	return TRUE;
}
BOOL HookManager::UnHook(void)
{
	BOOL res = UnhookWindowsHookEx(hHook);
	hHook = NULL;
	hServer = NULL;
	return res;
}