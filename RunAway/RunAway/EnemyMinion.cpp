#include"EnemyMinion.h"

using namespace Core;

EnemyMinion::EnemyMinion(const Pos &pos, Color color)
: IEnemy(pos, 230, "��", 2, color){}
EnemyMinion::~EnemyMinion(){}
void EnemyMinion::update(void)
{
	IEnemy::update();
	if (m_prevDir != m_dir)
	{
		switch (m_prevDir = m_dir)
		{
		case dir_up:	m_myChar = "��"; break;
		case dir_down:	m_myChar = "��"; break;
		case dir_left:	m_myChar = "��"; break;
		case dir_right:	m_myChar = "��"; break;
		}
	}
}