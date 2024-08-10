#ifndef _HOOK_H_
#define _HOOK_H_

#include <Windows.h>

class Hook
{
public:
	Hook();
	~Hook();

private:
	HHOOK hHook;	// Hook Handle
	HWND  hServer;	// Hook Server Window Handle

};

#endif // _HOOK_H_