#include<new>
#include<iostream>

#include"Scene.h"

// ���� �� �����������
IScene* IScene::nowScene = NULL;

// ������
IScene::IScene(void){}
// �Ҹ���
IScene::~IScene()
{
	if (m_tileMap != NULL)
		delete m_tileMap;
}
PTILEMAP IScene::getTileMap(void) const
{
	return m_tileMap;
}
// ������ ��������Լ�
void IScene::changeScene(IScene *scene, bool deleteScene)
{
	if (nowScene != NULL && deleteScene)
		delete nowScene;
	nowScene = scene;
}