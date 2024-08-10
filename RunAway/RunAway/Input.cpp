#include<Windows.h>
#include<conio.h>

#include"Input.h"

#pragma warning(disable:4996)

using namespace Core;

static bool lkey[256], rkey[256], repeats[256];
static DWORD repeat_counter[256];

// Core.cpp���� ����
void Core::updateKeyState(void)
{
	for (int i = 0; i < 256; i++)
	{
		lkey[i] = rkey[i];
		rkey[i] = GetKeyState(i) & 0x8000 ? true : false;

		if (trigger(i))
		{
			repeats[i] = true;
			repeat_counter[i] = 1500;
		}
		else if (press(i))
		{
			if (repeat_counter[i] > 0)
			{
				repeats[i] = false;
				repeat_counter[i]--;
			}
			else
			{
				repeats[i] = true;
				repeat_counter[i] = 300;
			}
		}
		else
		{
			repeats[i] = false;
			repeat_counter[i] = 0;
		}
	}
}
bool Core::trigger(unsigned char key)
{
	return lkey[key] == false && rkey[key] == true;
}
// ������������ ���
bool Core::press(unsigned char key)
{
	return lkey[key] == true && rkey[key] == true;
}
// ������������ ������������ �ݺ�
bool Core::repeat(unsigned char key)
{
	return repeats[key] == true;
}
// ������ ���� ����
bool Core::release(unsigned char key)
{
	return lkey[key] == true && rkey[key] == false;
}
bool Core::mouseInArea(const Rect &rect)
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(GetConsoleWindow(), &point);
	return 
		point.x >= rect.left && point.y >= rect.top && 
		point.x <= rect.right && point.y <= rect.bottom;
}
// 4���� �Է�
Direction Core::dir4(void)
{
	if (press(VK_UP))		return dir_up;		// ��
	if (press(VK_DOWN))		return dir_down;	// ��
	if (press(VK_LEFT))		return dir_left;	// ��
	if (press(VK_RIGHT))	return dir_right;	// ��
	return dir_stop;
}
/*
// 8���� �Է�
Direction Core::dir8(void)
{
	Direction res = dir_stop;
	if (press(VK_DOWN))
	{
		if (press(VK_LEFT))
			return dir_lower_left; // ����
		if (press(VK_RIGHT))
			return dir_lower_right; // ����
		return dir_down; // ��
	}
	else
	{
		if (press(VK_LEFT))
			res = dir_left; // ��
		if (press(VK_RIGHT))
			res = dir_right; // ��
	}
	if (press(VK_UP))
	{
		if (press(VK_LEFT))
			return dir_upper_left; // �»�
		if (press(VK_RIGHT))
			return dir_upper_right; // ���
		return dir_up; // ��
	}
	else
	{
		if (press(VK_LEFT))
			res = dir_left; // ��
		if (press(VK_RIGHT))
			res = dir_right; // ��
	}
	return res;
}
*/