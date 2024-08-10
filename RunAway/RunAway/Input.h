#ifndef _INPUT_H_
#define _INPUT_H_

#include"Def.h"
#include<conio.h>

#define GC_UP 72
#define GC_LEFT 75
#define GC_RIGHT 77
#define GC_DOWN 80

namespace Core
{
	// Ű ������Ʈ
	void updateKeyState(void);

	// ������ 1ȸ
	bool trigger(unsigned char key);
	// ������������ ���
	bool press(unsigned char key);
	// ������������ ������������ �ݺ�
	bool repeat(unsigned char key);
	// ������ ���� ����
	bool release(unsigned char key);
	// ���콺 ���� �Ǵ�
	bool mouseInArea(const Rect &rect);
	// 4���� �Է�
	Direction dir4(void);
	// 8���� �Է�
	//Direction dir8(void);
}

#endif
