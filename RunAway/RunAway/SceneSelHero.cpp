#include"SceneSelHero.h"

#include"Console.h"
#include"Input.h"
#include"resource.h"

#include"User.h"
#include"SceneField.h"

#include<iostream>

using namespace Core;

#define drawCharacter(index)\
	draw(Pos(41, 2), 201 + (index), "��", 2)
#define drawLeft(color)\
	render<const char*>(Pos(33, 11), "��", color)
#define drawRight(color)\
	render<const char*>(Pos(65, 11), "��", color)

SceneSelHero::SceneSelHero(int stage) : m_stage(stage)
{
	m_nowIndex = 0;
	system("cls");
	render<const char*>(Pos(2, 1), "��������������������", LIGHTYELLOW);
	render<const char*>(Pos(2, 2), "��                ��", LIGHTYELLOW);
	render<const char*>(Pos(2, 3), "��������������������", LIGHTYELLOW);
	render<const char*>(Pos(7, 2), "��������", BRIGHTWHITE);
	render<int>(Pos(16, 2), stage, BRIGHTWHITE);

	drawLeft(WHITE); drawRight(WHITE);
	drawCharacter(m_nowIndex);
	render(Pos(15, 25), "�ɷ� : �̵��ӵ��� ��������.(���� 3��)");

	render<const char*>(Pos(15, 29), "���� :");
	render<const char*>(Pos(17, 30), "- ��ų�� �� ���������� �ѹ��� ��� �����մϴ�.");
	render<const char*>(Pos(17, 31), "- 60�ʵ��� ���� ���شٳ� ��Ƴ����� ���� ���������� �Ѿ�ϴ�.");
	render<const char*>(Pos(15, 33), "���� :");
	render<const char*>(Pos(17, 34), "�����̽��� - ����, �ɷ� ���");
	render<const char*>(Pos(17, 35), "����Ű     - �̵�");
}
SceneSelHero::~SceneSelHero(){}
void SceneSelHero::update(void)
{
	if (trigger(VK_LEFT))
		drawLeft(LIGHTRED);
	if (trigger(VK_RIGHT))
		drawRight(LIGHTRED);
	if (release(VK_LEFT))
		drawLeft(WHITE);
	if (release(VK_RIGHT))
		drawRight(WHITE);

	if (repeat(VK_LEFT) || repeat(VK_RIGHT))
	{
		m_nowIndex = (m_nowIndex + 1) % 3;
		drawCharacter(m_nowIndex);
		clearRect(Rect(26, 15, 100, 25));
		switch (m_nowIndex)
		{
		case 0:
			render<const char*>(Pos(15, 25), "�ɷ� : �̵��ӵ��� ��������.(���� 3��)");
			break;
		case 1:
			render<const char*>(Pos(15, 25), "�ɷ� : ���ƴٴѴ�. ���� ���������� ���� �浹�Ǹ� �״´�.");
			render<const char*>(Pos(22, 26), "�ɷ� ���ӽð��� ������ �� �� ���� ������ �״´�.(���� 3��)");
			break;
		case 2:
			render<const char*>(Pos(15, 25), "�ɷ� : �ð��� ���߰� ȥ�� �����δ�.");
			render<const char*>(Pos(22, 26), "������ �ð��ӿ����� ���� �浹�� �״´�.(���� 3��)");
			break;
		}
	}
	else if (trigger(VK_SPACE))
		changeScene(new SceneField(m_stage, m_nowIndex));
}