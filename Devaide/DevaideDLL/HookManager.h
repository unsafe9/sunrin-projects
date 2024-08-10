#ifndef _HOOKMANAGER_H_
#define _HOOKMANAGER_H_

#include "DevaideDLL.h"
#include "Hook.h"

#include <Windows.h>
#include <list>

#define HookMgr HookManager::GetInstance()

class DEVAIDE_DLLAPI HookManager
{
private:
	HookManager(void);

	std::list<Hook*> m_listHook;

public:
	static HookManager* GetInstance(void)
	{
		static HookManager instance;
		return &instance;
	}
	
	~HookManager();

public:
	BOOL SetHook(HWND hWnd, int idHook, HOOKPROC hookProc);
	BOOL UnHook(void);


};

#endif // _HOOKMANAGER_H_