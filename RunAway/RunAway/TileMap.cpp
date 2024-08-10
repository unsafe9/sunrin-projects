#include<new>
#include<iostream>

#include"TileMap.h"
#include"Console.h"

using namespace Core;

// ������
TileMap::TileMap(int Xsize, int Ysize) :
m_Xsize(Xsize), m_Ysize(Ysize){}
// �Ҹ���
TileMap::~TileMap()
{
	KeyList *iter;
	while (m_keyList != NULL)
	{
		iter = m_keyList->next;
		delete m_keyList;
		m_keyList = iter;
	}
	if (m_intMap != NULL)
	{
		for (int i = 0; i < m_Ysize; i++)
		{
			if (m_intMap[i] != NULL)
				delete[] m_intMap[i];
		}
		delete[] m_intMap;
	}
}
// Ű�� ��´�
int TileMap::getKey(const Core::Pos &pos) const
{
	return m_intMap[pos.y][pos.x];
}
// �� ũ�� ��ȯ
inline int TileMap::getXsize(void) const
{
	return m_Xsize;
}
inline int TileMap::getYsize(void) const
{
	return m_Ysize;
}
// Ű�� ���� ����Ʈ Ž��(Ž�� ���н� NULL ��ȯ)
TileMap::KeyList* TileMap::searchListFromKey(int key) const
{
	KeyList *i = m_keyList;
	while (i != NULL && i->key != key)
		i = i->next;
	return i;
}
void TileMap::setKey(int key, bool bMovable, char *pszCh)
{
	if (KeyList *search = searchListFromKey(key))
	{
		search->bMovable = bMovable;
		search->pszCh = pszCh;
	}
	else
	{
		m_keyListTail = (m_keyList == NULL ? m_keyList : m_keyListTail->next) = new KeyList;
		m_keyListTail->key = key;
		m_keyListTail->bMovable = bMovable;
		m_keyListTail->pszCh = pszCh;
	}
}
// ���� �̵����ɻ��¸� ����
RESULT TileMap::setKeyMovable(int key, bool bMovable)
{
	if (KeyList *search = searchListFromKey(key))
		search->bMovable = bMovable;
	else
		return res_null;
	return res_success;
}
// Ű�� ���� �׷����� ����
RESULT TileMap::setKeyChar(int key, char *pszCh)
{
	if (KeyList *search = searchListFromKey(key))
		search->pszCh = pszCh;
	else
		return res_null;
	return res_success;
}
// Ÿ�� �ʱ�ȭ
void TileMap::setTiles(int **intMap)
{
	m_intMap = intMap;
}
// ��ǥ�� ���ο� Ÿ���� �����
RESULT TileMap::setTile(const Pos &pos, int key)
{
	if (m_intMap == NULL)
		return res_null;
	else if (pos.x >= m_Xsize || pos.y >= m_Ysize)
		return res_overflow;
	else if (pos.x < 0 || pos.y < 0)
		return res_underflow;

	m_intMap[pos.y][pos.x] = key;
	return res_success;
}
// ��ǥ���� �̵��� �����Ѱ�
bool TileMap::movable(const Pos& pos) const
{
	if (pos.x >= m_Xsize || pos.y >= m_Ysize || pos.x < 0 || pos.y < 0)
		return false;
	return searchListFromKey(m_intMap[pos.y][pos.x])->bMovable;
}

// ȭ�鿡 ����Ѵ�.
void TileMap::render(bool bClearScreen) const
{
	if (bClearScreen)
		system("cls");
	for (int i = 0; i < m_Ysize; i++)
	{
		Core::gotoxy(Pos(0, i));
		for (int j = 0; j < m_Xsize; j++)
		{
			if (KeyList *search = searchListFromKey(m_intMap[i][j]))
				printf("%s", search->pszCh);
		}
	}
}
void TileMap::render(const Pos &pos) const
{
	if (KeyList *search = searchListFromKey(m_intMap[pos.y][pos.x]))
		Core::render(Pos(pos.x * 2, pos.y), search->pszCh);
}
void TileMap::render(const Core::Rect &rect) const
{
	for (int i = rect.top; i < rect.bottom; i++)
	{
		Core::gotoxy(Pos(rect.left, i));
		for (int j = rect.left; j < rect.right; j++)
		{
			if (KeyList *search = searchListFromKey(m_intMap[i][j]))
				printf("%s", search->pszCh);
		}
	}
}
/*
RESULT TileMap::save(const char *pFileName)
{

}
RESULT TileMap::load(const char *pFileName)
{

}
*/