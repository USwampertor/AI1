#include "stdafx.h"
#include "GameObject.h"
GameObject::GameObject()
{
}
GameObject::~GameObject()
{
}
void GameObject::SetPosition(float x, float y)
{
	m_position2d.x = x;
	m_position2d.y = y;
}


