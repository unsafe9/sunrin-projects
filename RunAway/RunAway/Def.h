#ifndef _DEFINE_H_
#define _DEFINE_H_

#include<Windows.h>

namespace Core
{
	// ��� Ÿ��
	typedef enum RESULT
	{
		res_success		= 0x0001,
		res_null		= 0x0000,
		res_overflow	= -0x0001,
		res_underflow	= -0x0002
	}RESULT;
	inline bool failed(RESULT res)
	{ 
		return (res <= 0); 
	}
	inline bool succeeded(RESULT res)
	{ 
		return (res > 0); 
	}

	// �÷���(��Ʈ�������� �μ��� ����)
	typedef DWORD Flags;

	// �簢������
	typedef struct Rect
	{
		int bottom, left, right, top;
		Rect(void){}
		Rect(int bottom, int left, int right, int top) :
			bottom(bottom), left(left), right(right), top(top){}
		inline bool operator==(const Rect &rect) const
		{
			return rect.bottom == bottom && rect.left == left &&
				rect.right == right && rect.top == top;
		}
		inline bool operator!=(const Rect &rect) const
		{
			return rect.bottom != bottom || rect.left != left ||
				rect.right != right || rect.top != top;
		}
		Rect& set(int bottom, int left, int right, int top)
		{
			this->bottom	= bottom;
			this->left		= left;
			this->right		= right;
			this->top		= top;
			return *this;
		}
		Rect& set(const Rect &rect)
		{
			bottom	= rect.bottom;
			left	= rect.left;
			right	= rect.right;
			top		= rect.top;
			return *this;
		}
	}Rect, *PRECT;

	// ��ǥ
	typedef struct Pos
	{
		int x, y;

		Pos(void){}
		Pos(int x, int y) : x(x), y(y){}
		inline bool operator==(const Pos &pos) const
		{
			return (pos.x == x && pos.y == y);
		}
		inline bool operator!=(const Pos &pos) const
		{
			return (pos.x != x || pos.y != y);
		}
		inline Pos operator-(const Pos &pos) const
		{
			return Pos(x - pos.x, y - pos.y);
		}
		inline Pos operator+(const Pos &pos) const
		{
			return Pos(x + pos.x, y + pos.y);
		}
		inline Pos operator*(const Pos &pos) const
		{
			return Pos(x * pos.x, y * pos.y);
		}
		inline Pos& operator-=(const Pos &pos)
		{
			x -= pos.x; y -= pos.y;
			return *this;
		}
		inline Pos& operator+=(const Pos &pos)
		{
			x += pos.x; y += pos.y;
			return *this;
		}
		inline Pos& operator*=(const Pos &pos)
		{
			x *= pos.x; y += pos.y;
			return *this;
		}
	}Pos, *PPOS;

	// ����(0~7)
	typedef enum Direction
	{
		dir_stop		= 0, // ����
		//dir_lower_left  = 1, // ����
		dir_down		= 2, // ��
		//dir_lower_right	= 3, // ����
		dir_left		= 4, // ��
		dir_right		= 6, // ��
		//dir_upper_left	= 7, // �»�
		dir_up			= 8, // ��
		//dir_upper_right	= 9  // ���
	}Direction;
}

#endif