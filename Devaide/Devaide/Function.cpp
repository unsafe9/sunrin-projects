#include "stdafx.h"
#include "Function.h"

#include <Tlhelp32.h>
#include <Psapi.h>

#include <io.h>

#pragma comment(lib, "shlwapi")

#include <intshcut.h>

using namespace Function;

HANDLE Function::GetProcessHandle(LPCWSTR szFilename)
{
	HANDLE hProcessSnapshot;
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe32;

	hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
	{
		return INVALID_HANDLE_VALUE;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	Process32First(hProcessSnapshot, &pe32);

	do{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (hProcess != NULL)
		{
			if (lstrcmpW(pe32.szExeFile, szFilename) == 0)
			{
				CloseHandle(hProcessSnapshot);
				return hProcess;
			}
		}
	} while (Process32Next(hProcessSnapshot, &pe32));

	CloseHandle(hProcessSnapshot);

	return INVALID_HANDLE_VALUE;
}
bool Function::SafeTerminateProcess(HANDLE hProcess, UINT uExitCode)
{
	DWORD dwTID, dwCode, dwErr = 0;
	HANDLE hProcessDup = INVALID_HANDLE_VALUE;
	HANDLE hRT = NULL;
	HINSTANCE hKernel = GetModuleHandleW(L"Kernel32");

	bool bSuccess = false;
	BOOL bDup = DuplicateHandle(GetCurrentProcess(),
		hProcess,
		GetCurrentProcess(),
		&hProcessDup,
		PROCESS_ALL_ACCESS,
		FALSE, 0);
	if (GetExitCodeProcess((bDup) ? hProcessDup : hProcess, &dwCode)
		&& (dwCode == STILL_ACTIVE))
	{
		FARPROC pfnExitProc;
		pfnExitProc = GetProcAddress(hKernel, "ExitProcess");
		hRT = CreateRemoteThread(
			bDup ? hProcessDup : hProcess,
			NULL, 0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(pfnExitProc),
			reinterpret_cast<PVOID>(uExitCode), 0, &dwTID);
		if (hRT == NULL)
		{
			dwErr = GetLastError();
		}
	}
	else
	{
		dwErr = ERROR_PROCESS_ABORTED;
	}
	if (hRT)
	{
		WaitForSingleObject((bDup) ? hProcessDup : hProcess, INFINITE);
		CloseHandle(hRT);
		bSuccess = true;
	}
	if (bDup)
	{
		CloseHandle(hProcessDup);
	}
	if (!bSuccess)
	{
		SetLastError(dwErr);
	}

	return bSuccess;
}

DWORD Function::FindProcessID(LPCWSTR szFilename)
{
	HANDLE hProcessSnapshot = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe;

	pe.dwSize = sizeof(PROCESSENTRY32);
	hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

	Process32First(hProcessSnapshot, &pe);
	do{
		if (lstrcmpW(szFilename, pe.szExeFile) == 0)
		{
			CloseHandle(hProcessSnapshot);
			return pe.th32ProcessID;
		}
	} while (Process32Next(hProcessSnapshot, &pe));

	CloseHandle(hProcessSnapshot);
	
	return 0xffffffff;
}
DWORD Function::FindProcessID(HWND hWnd)
{
	DWORD dwProcessID;
	GetWindowThreadProcessId(hWnd, &dwProcessID);
	return dwProcessID;
}

bool Function::InjectDll(DWORD dwProcessID, LPCWSTR szDllName)
{
	// 대상 프로세스의 핸들 구함
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
	if (!hProcess)
	{
		return false;
	}

	// 대상 프로세스 메모리에 szDllName크기만큼 메모리 할당
	// 리턴값은 내 프로세스가 아닌 대상 프로세스의 메모리 주소이다.
	DWORD dwBufSize = lstrlenW(szDllName) + 1;
	LPVOID pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);
	// 할당 받은 메모리에 dll경로 씀
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllName, dwBufSize, NULL);
	
	// LoadLibraryW API 주소구함
	HMODULE hModule = GetModuleHandleW(L"kernel32.dll");
	LPTHREAD_START_ROUTINE pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryW");
	
	// 프로세스에 스레드 실행
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return true;
}
bool Function::EjectDll(DWORD dwProcessID, LPCWSTR szDllName)
{
	// 대상 프로세스의 핸들 구함
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
	if (!hProcess)
	{
		return false;
	}

	/*// 대상 프로세스에서 szDllName 모듈정보 로드
	bool found = false;
	MODULEENTRY32 me;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, NULL);
	Module32First(hSnapshot, &me);
	do
	{
		if (lstrcmpW(szDllName, me.szModule) == 0)
		{
			found = true;
			break;
		}
	} while (Module32Next(hSnapshot, &me));
	CloseHandle(hSnapshot);
	if (!found)
		return FALSE;*/
	
	// FreeLibrary API 주소구함
	HMODULE hModule = GetModuleHandleW(L"kernel32.dll");;
	LPTHREAD_START_ROUTINE pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "FreeLibrary");

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, GetRemoteModuleHandle(hProcess, szDllName), 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return true;
}

HMODULE WINAPI Function::GetRemoteModuleHandle(HANDLE hProcess, LPCWSTR lpModuleName)
{
	HMODULE* ModuleArray = NULL;
	DWORD ModuleArraySize = 100;
	DWORD NumModules = 0;
	WCHAR lpModuleNameCopy[MAX_PATH] = { 0 };
	WCHAR ModuleNameBuffer[MAX_PATH] = { 0 };

	/* Make sure we didn't get a NULL pointer for the module name */
	if (lpModuleName == NULL)
	{
		goto GRMH_FAIL_JMP;
	}

	/* Convert lpModuleName to all lowercase so the comparison isn't case sensitive */
	for (size_t i = 0; lpModuleName[i] != '\0'; ++i)
	{
		if (lpModuleName[i] >= 'A' && lpModuleName[i] <= 'Z')
		{
			// 0x20 is the difference between uppercase and lowercase
			lpModuleNameCopy[i] = lpModuleName[i] + 0x20; 
		}
		else
		{
			lpModuleNameCopy[i] = lpModuleName[i];
		}
		lpModuleNameCopy[i + 1] = '\0';
	}

	/* Allocate memory to hold the module handles */
	ModuleArray = new HMODULE[ModuleArraySize];

	/* Check if the allocation failed */
	if (ModuleArray == NULL)
	{
		goto GRMH_FAIL_JMP;
	}

	/* Get handles to all the modules in the target process */
	if (!::EnumProcessModulesEx(hProcess, ModuleArray,
		ModuleArraySize * sizeof(HMODULE), &NumModules, LIST_MODULES_ALL))
	{
		goto GRMH_FAIL_JMP;
	}

	/* We want the number of modules not the number of bytes */
	NumModules /= sizeof(HMODULE);

	/* Did we allocate enough memory for all the module handles? */
	if (NumModules > ModuleArraySize)
	{
		delete[] ModuleArray; // Deallocate so we can try again
		ModuleArray = NULL; // Set it to NULL se we can be sure if the next try fails
		ModuleArray = new HMODULE[NumModules]; // Allocate the right amount of memory

		/* Check if the allocation failed */
		if (ModuleArray == NULL)
		{
			goto GRMH_FAIL_JMP;
		}

		ModuleArraySize = NumModules; // Update the size of the array

		/* Get handles to all the modules in the target process */
		if (!::EnumProcessModulesEx(hProcess, ModuleArray,
			ModuleArraySize * sizeof(HMODULE), &NumModules, LIST_MODULES_ALL))
		{
			goto GRMH_FAIL_JMP;
		}
		/* We want the number of modules not the number of bytes */
		NumModules /= sizeof(HMODULE);
	}
	
	/* Iterate through all the modules and see if the names match the one we are looking for */
	for (DWORD i = 0; i <= NumModules; ++i)
	{
		/* Get the module's name */
		::GetModuleBaseNameW(hProcess, ModuleArray[i],
			ModuleNameBuffer, sizeof(ModuleNameBuffer));

		/* Convert ModuleNameBuffer to all lowercase so the comparison isn't case sensitive */
		for (size_t j = 0; ModuleNameBuffer[j] != '\0'; ++i)
		{
			if (ModuleNameBuffer[j] >= 'A' && ModuleNameBuffer[j] <= 'Z')
			{
				// 0x20 is the difference between uppercase and lowercase
				ModuleNameBuffer[j] += 0x20; 
			}
		}

		/* Does the name match? */
		if (wcsstr(ModuleNameBuffer, lpModuleNameCopy) != NULL)
		{
			/* Make a temporary variable to hold return value*/
			HMODULE TempReturn = ModuleArray[i];

			/* Give back that memory */
			delete[] ModuleArray;

			/* Success */
			return TempReturn;
		}

		/* Wrong module let's try the next... */
	}

	/* Uh Oh... */
GRMH_FAIL_JMP:

	/* If we got to the point where we allocated memory we need to give it back */
	if (ModuleArray != NULL)
	{
		delete[] ModuleArray;
	}

	/* Failure... */
	return NULL;
}
FARPROC WINAPI Function::GetRemoteProcAddress(HANDLE hProcess, HMODULE hModule, LPCWSTR lpProcName, UINT Ordinal, BOOL UseOrdinal)
{
	BOOL Is64Bit = FALSE;
	MODULEINFO RemoteModuleInfo = { 0 };
	UINT_PTR RemoteModuleBaseVA = 0;
	IMAGE_DOS_HEADER DosHeader = { 0 };
	DWORD Signature = 0;
	IMAGE_FILE_HEADER FileHeader = { 0 };
	IMAGE_OPTIONAL_HEADER64 OptHeader64 = { 0 };
	IMAGE_OPTIONAL_HEADER32 OptHeader32 = { 0 };
	IMAGE_DATA_DIRECTORY ExportDirectory = { 0 };
	IMAGE_EXPORT_DIRECTORY ExportTable = { 0 };
	UINT_PTR ExportFunctionTableVA = 0;
	UINT_PTR ExportNameTableVA = 0;
	UINT_PTR ExportOrdinalTableVA = 0;
	DWORD* ExportFunctionTable = NULL;
	DWORD* ExportNameTable = NULL;
	WORD* ExportOrdinalTable = NULL;

	/* Temporary variables not used until much later but easier
	/* to define here than in all the the places they are used */
	CHAR TempChar;
	BOOL Done = FALSE;

	/* Check to make sure we didn't get a NULL pointer for the name unless we are searching by ordinal */
	if (lpProcName == NULL && !UseOrdinal)
	{
		goto GRPA_FAIL_JMP;
	}

	/* Get the base address of the remote module along with some other info we don't need */
	if (!::GetModuleInformation(hProcess, hModule, &RemoteModuleInfo, sizeof(RemoteModuleInfo)))
	{
		goto GRPA_FAIL_JMP;
	}
	RemoteModuleBaseVA = (UINT_PTR)RemoteModuleInfo.lpBaseOfDll;

	/* Read the DOS header and check it's magic number */
	if (!::ReadProcessMemory(hProcess, (LPCVOID)RemoteModuleBaseVA, &DosHeader,
		sizeof(DosHeader), NULL) || DosHeader.e_magic != IMAGE_DOS_SIGNATURE)
	{
		goto GRPA_FAIL_JMP;
	}

	/* Read and check the NT signature */
	if (!::ReadProcessMemory(hProcess, (LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew),
		&Signature, sizeof(Signature), NULL) || Signature != IMAGE_NT_SIGNATURE)
	{
		goto GRPA_FAIL_JMP;
	}

	/* Read the main header */
	if (!::ReadProcessMemory(hProcess,
		(LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof(Signature)),
		&FileHeader, sizeof(FileHeader), NULL))
	{
		goto GRPA_FAIL_JMP;
	}

	/* Which type of optional header is the right size? */
	if (FileHeader.SizeOfOptionalHeader == sizeof(OptHeader64))
	{
		Is64Bit = TRUE;
	}
	else if (FileHeader.SizeOfOptionalHeader == sizeof(OptHeader32))
	{
		Is64Bit = FALSE;
	}
	else
	{
		goto GRPA_FAIL_JMP;
	}

	if (Is64Bit)
	{
		/* Read the optional header and check it's magic number */
		if (!::ReadProcessMemory(hProcess,
			(LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof(Signature)+sizeof(FileHeader)),
			&OptHeader64, FileHeader.SizeOfOptionalHeader, NULL)
			|| OptHeader64.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
		{
			goto GRPA_FAIL_JMP;
		}
	}
	else
	{
		/* Read the optional header and check it's magic number */
		if (!::ReadProcessMemory(hProcess,
			(LPCVOID)(RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof(Signature)+sizeof(FileHeader)),
			&OptHeader32, FileHeader.SizeOfOptionalHeader, NULL)
			|| OptHeader32.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
		{
			goto GRPA_FAIL_JMP;
		}
	}

	/* Make sure the remote module has an export directory and if it does save it's relative address and size */
	if (Is64Bit && OptHeader64.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1)
	{
		ExportDirectory.VirtualAddress = (OptHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).VirtualAddress;
		ExportDirectory.Size = (OptHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).Size;
	}
	else if (OptHeader32.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1)
	{
		ExportDirectory.VirtualAddress = (OptHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).VirtualAddress;
		ExportDirectory.Size = (OptHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]).Size;
	}
	else
	{
		goto GRPA_FAIL_JMP;
	}

	/* Read the main export table */
	if (!::ReadProcessMemory(hProcess, (LPCVOID)(RemoteModuleBaseVA + ExportDirectory.VirtualAddress),
		&ExportTable, sizeof(ExportTable), NULL))
	{
		goto GRPA_FAIL_JMP;
	}

	/* Save the absolute address of the tables so we don't need to keep adding the base address */
	ExportFunctionTableVA = RemoteModuleBaseVA + ExportTable.AddressOfFunctions;
	ExportNameTableVA = RemoteModuleBaseVA + ExportTable.AddressOfNames;
	ExportOrdinalTableVA = RemoteModuleBaseVA + ExportTable.AddressOfNameOrdinals;

	/* Allocate memory for our copy of the tables */
	ExportFunctionTable = new DWORD[ExportTable.NumberOfFunctions];
	ExportNameTable = new DWORD[ExportTable.NumberOfNames];
	ExportOrdinalTable = new WORD[ExportTable.NumberOfNames];

	/* Check if the allocation failed */
	if (ExportFunctionTable == NULL || ExportNameTable == NULL || ExportOrdinalTable == NULL)
	{
		goto GRPA_FAIL_JMP;
	}

	/* Get a copy of the function table */
	if (!::ReadProcessMemory(hProcess, (LPCVOID)ExportFunctionTableVA,
		ExportFunctionTable, ExportTable.NumberOfFunctions * sizeof(DWORD), NULL))
	{
		goto GRPA_FAIL_JMP;
	}

	/* Get a copy of the name table */
	if (!::ReadProcessMemory(hProcess, (LPCVOID)ExportNameTableVA,
		ExportNameTable, ExportTable.NumberOfNames * sizeof(DWORD), NULL))
	{
		goto GRPA_FAIL_JMP;
	}

	/* Get a copy of the ordinal table */
	if (!::ReadProcessMemory(hProcess, (LPCVOID)ExportOrdinalTableVA,
		ExportOrdinalTable, ExportTable.NumberOfNames * sizeof(WORD), NULL))
	{
		goto GRPA_FAIL_JMP;
	}

	/* If we are searching for an ordinal we do that now */
	if (UseOrdinal)
	{
		/* NOTE:
		/* Microsoft's PE/COFF specification does NOT say we need to subtract the ordinal base
		/* from our ordinal but it seems to always give the wrong function if we don't */

		/* Make sure the ordinal is valid */
		if (Ordinal < ExportTable.Base || (Ordinal - ExportTable.Base) >= ExportTable.NumberOfFunctions)
		{
			goto GRPA_FAIL_JMP;
		}

		UINT FunctionTableIndex = Ordinal - ExportTable.Base;

		/* Check if the function is forwarded and if so get the real address*/
		if (ExportFunctionTable[FunctionTableIndex] >= ExportDirectory.VirtualAddress &&
			ExportFunctionTable[FunctionTableIndex] <= ExportDirectory.VirtualAddress + ExportDirectory.Size)
		{
			Done = FALSE;
			CString TempForwardString;

			/* Get the forwarder string one character at a time because we don't know how long it is */
			for (UINT_PTR i = 0; !Done; ++i)
			{
				/* Get next character */
				if (!::ReadProcessMemory(hProcess,
					(LPCVOID)(RemoteModuleBaseVA + ExportFunctionTable[FunctionTableIndex] + i),
					&TempChar, sizeof(TempChar), NULL))
				{
					goto GRPA_FAIL_JMP;
				}

				TempForwardString += TempChar; // Add it to the string

				/* If it's NUL we are done */
				if (TempChar == (CHAR)'\0')
				{
					Done = TRUE;
				}
			}

			/* Find the dot that seperates the module name and the function name/ordinal */
			size_t Dot = TempForwardString.Find('.');
			if (Dot == -1)
			{
				goto GRPA_FAIL_JMP;
			}

			/* Temporary variables that hold parts of the forwarder string */
			CString RealModuleName, RealFunctionId;
			RealModuleName = TempForwardString.Left(Dot - 1);
			RealFunctionId = TempForwardString.Right(Dot + 1);
			HMODULE RealModule = GetRemoteModuleHandle(hProcess, (LPCWSTR)RealModuleName);
			FARPROC TempReturn;// Make a temporary variable to hold return value 


			/* Figure out if the function was exported by name or by ordinal */
			if (RealFunctionId[0] == '#') // Exported by ordinal
			{
				UINT RealOrdinal = 0U;
				RealFunctionId.Delete(0, 1); // Remove '#' from string

				/* My version of atoi() because I was too lazy to use the real one... */
				for (int i = 0; i < RealFunctionId.GetLength(); ++i)
				{
					if (RealFunctionId[i] >= '0' && RealFunctionId[i] <= '9')
					{
						RealOrdinal *= 10U;
						RealOrdinal += RealFunctionId[i] - '0';
					}
					else
					{
						break;
					}
				}

				/* Recursively call this function to get return value */
				TempReturn = GetRemoteProcAddress(hProcess, RealModule, NULL, RealOrdinal, TRUE);
			}
			else // Exported by name
			{
				/* Recursively call this function to get return value */
				TempReturn = GetRemoteProcAddress(hProcess, RealModule, (LPCWSTR)RealFunctionId, 0, FALSE);
			}

			/* Give back that memory */
			delete[] ExportFunctionTable;
			delete[] ExportNameTable;
			delete[] ExportOrdinalTable;

			/* Success!!! */
			return TempReturn;
		}
		else // Not Forwarded
		{

			/* Make a temporary variable to hold return value*/
			FARPROC TempReturn = (FARPROC)(RemoteModuleBaseVA + ExportFunctionTable[FunctionTableIndex]);

			/* Give back that memory */
			delete[] ExportFunctionTable;
			delete[] ExportNameTable;
			delete[] ExportOrdinalTable;

			/* Success!!! */
			return TempReturn;
		}
	}


	/* Iterate through all the names and see if they match the one we are looking for */
	for (DWORD i = 0; i < ExportTable.NumberOfNames; ++i)	
	{
		CString TempFunctionName;

		Done = FALSE;// Reset for next name

		/* Get the function name one character at a time because we don't know how long it is */
		for (UINT_PTR j = 0; !Done; ++j)
		{
			/* Get next character */
			if (!::ReadProcessMemory(hProcess, (LPCVOID)(RemoteModuleBaseVA + ExportNameTable[i] + j),
				&TempChar, sizeof(TempChar), NULL))
			{
				goto GRPA_FAIL_JMP;
			}

			TempFunctionName += TempChar; // Add it to the string

			/* If it's NUL we are done */
			if (TempChar == (CHAR)'\0')
			{
				Done = TRUE;
			}
		}

		/* Does the name match? */
		if (TempFunctionName.Find(lpProcName) != -1)
		{
			/* NOTE:
			/* Microsoft's PE/COFF specification says we need to subtract the ordinal base
			/*from the value in the ordinal table but that seems to always give the wrong function */

			/* Check if the function is forwarded and if so get the real address*/
			if (ExportFunctionTable[ExportOrdinalTable[i]] >= ExportDirectory.VirtualAddress &&
				ExportFunctionTable[ExportOrdinalTable[i]] <= ExportDirectory.VirtualAddress + ExportDirectory.Size)
			{
				Done = FALSE;
				CString TempForwardString;

				/* Get the forwarder string one character at a time because we don't know how long it is */
				for (UINT_PTR j = 0; !Done; ++j)
				{
					/* Get next character */
					if (!::ReadProcessMemory(hProcess,
						(LPCVOID)(RemoteModuleBaseVA + ExportFunctionTable[i] + j),
						&TempChar, sizeof(TempChar), NULL))
					{
						goto GRPA_FAIL_JMP;
					}

					TempForwardString += TempChar; // Add it to the string

					/* If it's NUL we are done */
					if (TempChar == (CHAR)'\0')
					{
						Done = TRUE;
					}
				}

				/* Find the dot that seperates the module name and the function name/ordinal */
				size_t Dot = TempForwardString.Find('.');
				if (Dot == -1)
				{
					goto GRPA_FAIL_JMP;
				}

				/* Temporary variables that hold parts of the forwarder string */
				CString RealModuleName, RealFunctionId;
				RealModuleName = TempForwardString.Left(Dot);
				RealFunctionId = TempForwardString.Right(Dot + 1);

				HMODULE RealModule = GetRemoteModuleHandle(hProcess, (LPCWSTR)RealModuleName);
				FARPROC TempReturn;// Make a temporary variable to hold return value 


				/* Figure out if the function was exported by name or by ordinal */
				if (RealFunctionId[0] == '#') // Exported by ordinal
				{
					UINT RealOrdinal = 0U;
					RealFunctionId.Delete(0, 1); // Remove '#' from string

					/* My version of atoi() because I was to lazy to use the real one... */
					for (int i = 0; i < RealFunctionId.GetLength(); ++i)
					{
						if (RealFunctionId[i] >= '0' && RealFunctionId[i] <= '9')
						{
							RealOrdinal *= 10U;
							RealOrdinal += RealFunctionId[i] - '0';
						}
						else
						{
							break;
						}
					}

					/* Recursively call this function to get return value */
					TempReturn = GetRemoteProcAddress(hProcess, RealModule, NULL, RealOrdinal, TRUE);
				}
				else // Exported by name
				{
					/* Recursively call this function to get return value */
					TempReturn = GetRemoteProcAddress(hProcess, RealModule, (LPCWSTR)RealFunctionId, 0, FALSE);
				}

				/* Give back that memory */
				delete[] ExportFunctionTable;
				delete[] ExportNameTable;
				delete[] ExportOrdinalTable;

				/* Success!!! */
				return TempReturn;
			}
			else // Not Forwarded
			{

				/* Make a temporary variable to hold return value*/
				FARPROC TempReturn;

				/* NOTE:
				/* Microsoft's PE/COFF specification says we need to subtract the ordinal base
				/*from the value in the ordinal table but that seems to always give the wrong function */
				//TempReturn = (FARPROC)(RemoteModuleBaseVA + ExportFunctionTable[ExportOrdinalTable[i] - ExportTable.Base]);

				/* So we do it this way instead */
				TempReturn = (FARPROC)(RemoteModuleBaseVA + ExportFunctionTable[ExportOrdinalTable[i]]);

				/* Give back that memory */
				delete[] ExportFunctionTable;
				delete[] ExportNameTable;
				delete[] ExportOrdinalTable;

				/* Success!!! */
				return TempReturn;
			}
		}

		/* Wrong function let's try the next... */
	}

	/* Uh Oh... */
GRPA_FAIL_JMP:

	/* If we got to the point where we allocated memory we need to give it back */
	if (ExportFunctionTable != NULL)
	{
		delete[] ExportFunctionTable;
	}
	if (ExportNameTable != NULL)
	{
		delete[] ExportNameTable;
	}
	if (ExportOrdinalTable != NULL)
	{
		delete[] ExportOrdinalTable;
	}

	/* Falure... */
	return NULL;
}

CString Function::GetExeName(DWORD dwProcessID)
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	//Enumerate all processes
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return NULL;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	WCHAR szEXEName[MAX_PATH];
	//Loop through all process to find the one that matches
	//the one we are looking for
	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] == dwProcessID)
		{
			// Get a handle to the process
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
				PROCESS_VM_READ, FALSE, dwProcessID);

			// Get the process name
			if (NULL != hProcess)
			{
				HMODULE hMod;
				DWORD cbNeeded;

				if (EnumProcessModules(hProcess, &hMod,
					sizeof(hMod), &cbNeeded))
				{
					//Get the name of the exe file
					GetModuleBaseNameW(hProcess, hMod, szEXEName,
						sizeof(szEXEName) / sizeof(WCHAR));

					return CString(szEXEName);
				}
			}
		}
	}
	return NULL;
}

bool Function::SetWindowTopMost(CWnd *pWnd)
{
	// 최소화상태일시 끌어올린다.
	if (pWnd->IsIconic())
	{
		pWnd->ShowWindow(SW_SHOWNORMAL);
	}
	// 항상 최상위로 설정한다.
	time_t timer = time(NULL);
	do{
		if (!IsWindow(pWnd->GetSafeHwnd()) && time(NULL) > timer + 2)
		{
			return false;
		}
		pWnd->SetForegroundWindow();
		pWnd->SetActiveWindow();
		::SetWindowPos(pWnd->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
	} while (!(GetWindowLongW(pWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_TOPMOST));
	return true;
}
bool Function::SetWindowTopMost(HWND hWnd)
{
	// 최소화상태일시 끌어올린다.
	if (IsIconic(hWnd))
	{
		ShowWindow(hWnd, SW_SHOWNORMAL);
	}
	// 항상 최상위로 설정한다.
	time_t timer = time(NULL);
	do{
		if (!IsWindow(hWnd) && time(NULL) > timer + 2)
		{
			return false;
		}
		::SetForegroundWindow(hWnd);
		::SetActiveWindow(hWnd);
		::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
	} while (!(GetWindowLongW(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST));
	return true;
}

/*
szTargetPath
바로가기의 대상. 파일일 경우 대상 파일의 경로를, 웹페이지 일 경우에 웹페이지 주소를 입력

szShortcutPath
저장하려는 바로가기 파일의 경로. 바로가기의 확장자는 반드시 .lnk 이어야 하며 인터넷 바로가기의 확장자는 .url 이어야함

szDesc
바로가기에 대한 설명

szArgument
바로가기 실행 시 사용할 파라미터. 인터넷 바로가기의 경우는 NULL 전달

szIconPath
바로가기 아이콘의 경로. NULL로 설정할 경우 바로가기 대상의 아이콘을 그대로 사용

iIconIndex
szIconPath에서 설정한 아이콘 파일에서 실제 사용할 아이콘 인덱스

wHotkey
바로가기 키. 하위 바이트에는 Virtual keycode를, 상위바이트에는 modifier flag를 넣어주는 기본적인 핫키 형식

nShowCmd
실행 창의 형태를 지정. 기본은 SW_SHOW이며 SW_MAXIMIZE(최대화), SW_MINIMIZE(최소화) 등 사용 가능
*/
bool Function::CreateShortcut(LPCWSTR szTargetPath, LPCWSTR szShortcutPath, LPCWSTR szDesc, LPCWSTR szArgument, LPCWSTR szIconPath, int iIconIndex, WORD wHotkey, int nShowCmd)
{
	// Validate parameters
	ASSERT(szTargetPath);
	ASSERT(szShortcutPath);

	HRESULT hRes;
	IUniformResourceLocatorW* purl = NULL;
	IShellLinkW* psl = NULL;
	IPersistFile* ppf = NULL;
	bool bRet = false;

	::CoInitialize(NULL);

	WCHAR szDrive[_MAX_DRIVE], szDir[_MAX_PATH], szName[_MAX_FNAME], szExt[_MAX_EXT];
	_wsplitpath_s(szShortcutPath, szDrive, szDir, szName, szExt);

	CString sExt(szExt);

	// Shortcut
	if (0 == sExt.CollateNoCase(L".lnk"))
	{
		hRes = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
			IID_IShellLinkW, (LPVOID*)&psl);
		hRes = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
	}

	// URL Shortcut
	else if (0 == sExt.CollateNoCase(L".url"))
	{
		hRes = ::CoCreateInstance(CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER,
			IID_IUniformResourceLocatorW, (LPVOID*)&purl);
		if (SUCCEEDED(hRes))
		{
			hRes = purl->QueryInterface(IID_IShellLinkW, (LPVOID*)&psl);
			if (SUCCEEDED(hRes))
				hRes = purl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		}
	}
	else
	{
		// Shortcut file extention must be .lnk or .url
		::CoUninitialize();
		return false;
	}

	if (SUCCEEDED(hRes))
	{
		hRes = psl->SetPath(szTargetPath);
		if (szDesc)
			psl->SetDescription(szDesc);

		if (szArgument)
			psl->SetArguments(szArgument);

		if (szIconPath && iIconIndex >= 0)
			psl->SetIconLocation(szIconPath, iIconIndex);

		if (wHotkey)
			psl->SetHotkey(wHotkey);

		CString sDir;
		sDir.Format(L"%s%s", szDrive, szDir);
		psl->SetWorkingDirectory(sDir);
		psl->SetShowCmd(nShowCmd);

		USES_CONVERSION;
		hRes = ppf->Save(T2COLE(szShortcutPath), TRUE);
		if (hRes != S_OK)
			TRACE(L"IPersistFile::Save Error\n");
		else
			bRet = true;

		ppf->Release();
		psl->Release();
		if (purl)
			purl->Release();
	}
	::CoUninitialize();
	return bRet;
}
CString Function::GetShortcutTarget(const CString LinkFileName)
{
	HRESULT hres;

	CString Link, Temp(LinkFileName);
	Temp.MakeLower();
	if (Temp.Find(L".lnk") == -1)           //Check if the name ends with .lnk
		Link = LinkFileName + L".lnk";   //if not, append it
	else
		Link = LinkFileName;
	CString Info;
	Info.Empty();

	IShellLinkW* psl;
	//Create the ShellLink object
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLinkW, (LPVOID*)&psl);

	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;
		//Bind the ShellLink object to the Persistent File
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf);
		if (SUCCEEDED(hres))
		{
			//Read the link into the persistent file
			hres = ppf->Load(Link, 0);
			
			if (SUCCEEDED(hres))
			{
				//Read the target information from the link object
				//UNC paths are supported (SLGP_UNCPRIORITY)
				psl->GetPath(Temp.GetBuffer(1024), 1024, NULL, SLGP_UNCPRIORITY);
				Temp.ReleaseBuffer();
				Info = Temp;
				//Read the arguments from the link object
				psl->GetArguments(Temp.GetBuffer(1024), 1024);
				Temp.ReleaseBuffer();
				Info += L" " + Temp;
			}
		}
	}
	psl->Release();
	//Return the Target and the Argument as a CString
	return Info;
}
