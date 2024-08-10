#include "RGGameObject.h"
#include "RGScene.h"
#include "RGComponent.h"
#include "RGApplication.h"

namespace RGEngine
{
	GameObject::GameObject(void) : m_enabled(true), m_destroyed(false)
	{
		matrix.Identity();
		position = center = rotationCenter = scalingCenter = Math::Vector(0.0f, 0.0f);
		scale.SetVector(1.0f, 1.0f);
		rotate = scalingRotation = 0.0f;
	}

	GameObject::~GameObject()
	{
		for (auto &i : m_components)
		{
			(i.second)->OnDestroy();
			delete i.second;
		}
		m_components.clear();
	}

	void GameObject::SetEnabled(bool flag)
	{
		if (m_enabled != flag)
		{
			m_enabled = flag;
			m_enabled ? OnEnabled() : OnDisabled();
		}
	}

	bool GameObject::GetEnabled(void) const
	{
		return m_enabled;
	}

	void GameObject::Update(void)
	{
		for (auto &i : m_components)
		{
			if ((i.second)->GetEnabled())
			{
				(i.second)->OnUpdate();
			}
		}
	}

	void GameObject::Render(void)
	{
		D3DXMatrixTransformation2D(
			(LPD3DXMATRIX)&matrix,					// ���� ��� ���
			(LPD3DXVECTOR2)&scalingCenter,			// ������ �߽��� ����, NULL(=0, 0), 0, 0 �̹��� ���� ���
			scalingRotation,						// Ȯ�� ȸ�� ��Ҹ� ����, pScaling �� x, y�� Ȯ������� �ٸ� ��쿡  ����
			(LPD3DXVECTOR2)&scale,				// Ȯ������ ����, NULL �� ������ ���� ����
			(LPD3DXVECTOR2)&rotationCenter,			// ȸ�� �߽��� NULL(=0, 0)
			rotate,								// ȸ�� ����(Radian ����), ��ȸ�� ����
			(LPD3DXVECTOR2)&(position - center));	// �����̵� NULL(=0, 0)
		if (parent)
		{
			matrix *= parent->matrix;
		}
		RGGraphic->GetSprite()->SetTransform((LPD3DXMATRIX)&matrix);

		for (auto &i : m_components)
		{
			if ((i.second)->GetEnabled())
			{
				(i.second)->OnRender();
			}
		}
	}
	void GameObject::Destroy(void)
	{
		m_destroyed = true;
	}
}