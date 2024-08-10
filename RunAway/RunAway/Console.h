#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include"Def.h"
#include<iostream>

namespace Core
{
	// Ŀ�� ��ġ ����(gotoxy)
	void setCursorPos(const Pos &pos);
	inline void gotoxy(const Pos &pos)
	{
		setCursorPos(pos);
	}
	Pos getCursorPos(void);

	// Ŀ�� Ÿ��
	typedef enum CursorType
	{
		cursor_unvisible,
		cursor_input,
		cursor_normal
	}CursorType;
	void setCursorType(CursorType type);
	CursorType getCursorType(void);

	// ��
	typedef enum Color
	{
		BLACK			= 0x0,	// ������
		BLUE			= 0x1,	// �Ķ���
		GREEN			= 0x2,	// �ʷϻ�
		SKYBLUE			= 0x3,	// ����
		RED				= 0x4,	// ������
		PURPLE			= 0x5,	// ���ֻ�
		YELLOW			= 0x6,	// �����
		WHITE			= 0x7,	// ���
		GRAY			= 0x8,	// ȸ��
		LIGHTBLUE		= 0x9,	// ���� �Ķ���
		LIGHTGREEN		= 0xA,	// ���� �ʷϻ�
		LIGHTSKYBLUE	= 0xB,	// ���� ����
		LIGHTRED		= 0xC,	// ���� ������
		LIGHTPURPLE		= 0xD,	// ���� ���ֻ�
		LIGHTYELLOW		= 0xE,	// ���� �����
		BRIGHTWHITE		= 0xF,	// ���� ���
		NOW_COLOR		= -1,	// ���� �÷�
		NONE			= -2	// �������� ����
	}Color;
	void setTextColor(Color color);
	Color getTextColor(void);
	void setBgColor(Color color);
	Color getBgColor(void);

	// �ܼ� ũ�� ����
	void setConSize(int cols, int lines);

	// �����
	void clearRect(const Rect &rect);

	// ����Ѵ�
	template<typename T>
	void render(const Pos &pos, T source, Color color = getTextColor())
	{
		Color oriColor = getTextColor();

		gotoxy(pos);
		if (color != NOW_COLOR && color != NONE)
			setTextColor(color);
		std::cout << source;
		if (color != NOW_COLOR && color != NONE)
			setTextColor(oriColor);
	}
	// �׸��� printf�� �׸���
	void draw(const Pos &pos, int resource, const char *pszCh, int space = 1, Color color = NONE);

	// Ÿ��Ʋ
	inline void setTitle(const char *pszText)
	{
		SetConsoleTitleA(pszText);
	}
	inline void getTitle(char *pBuf, int nSize)
	{
		GetConsoleTitleA(pBuf, nSize);
	}
}

#endif