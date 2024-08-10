#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include<iostream>
#include<io.h>
#include<fcntl.h>
#include<Windows.h>

namespace Console
{
	void Alloc(LPWSTR title)
	{
		int hCrt;
		FILE *hf;

		AllocConsole();

		// OUTPUT
		hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "w");
		*stdout = *hf;
		setvbuf(stdout, nullptr, _IONBF, 0);

		// INPUT
		hCrt = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "r");
		*stdin = *hf;
		setvbuf(stdin, nullptr, _IONBF, 0);

		_wsetlocale(LC_ALL, L"korean");

		SetConsoleTitleW(title);
	}
	void Free(void)
	{
		_fcloseall();
	}
}


#endif // _CONSOLE_H_