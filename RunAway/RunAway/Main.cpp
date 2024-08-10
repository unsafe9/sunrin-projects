#include<iostream>

#include"Console.h"
#include"Input.h"

#include"Scene.h"
#include"SceneMain.h"

using namespace Core;

void initConsole(void)
{
	// ������ ũ��� Ÿ��Ʋ�� ����.
	setTitle("������� (RunAway)");
	setConSize(100, 40);

	// �����츦 ȭ�� �߽����� ����.
	HWND hWnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, 0,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (rect.right - rect.left) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - (rect.bottom - rect.top) / 2,
		0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// �ִ�ȭ��ư�� ���Ұ��� ����.
	SetWindowLongA(hWnd, GWL_STYLE, 
		GetWindowLongA(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	// ȭ�� ����� Ŀ���� ����.
	setBgColor(BLACK);
	setTextColor(WHITE);
	setCursorType(cursor_unvisible);
}

int main(void)
{
	initConsole();

	// ���� �õ� ����
	srand(static_cast<unsigned int>(GetTickCount()));
	try{
		IScene::changeScene(new SceneMain);
		// ���η���
		while (IScene::nowScene != NULL)
		{
			updateKeyState();
			IScene::nowScene->update();
		}
	}
	catch (std::exception e){
		MessageBoxA(GetConsoleWindow(), e.what(), "exception", MB_OK);
		return 0;
	}

	return 0;
}
