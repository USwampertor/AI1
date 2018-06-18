#pragma once
#include "IDVMath.h"
enum class OBJECT_TYPE
{
	OBSTACLE,
	BOID,
	PLAYER,
	FLAG
};


class GameObject
{
public:
	XVECTOR2 m_position2d;
	std::string m_tag;
	float boundary;
	GameObject();
	~GameObject();
	virtual void Update() = 0;
	void SetPosition(float x, float y);
};
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
template <typename OBJECT>
void GetList(std::vector<OBJECT> list)
{
	//Here I would make a function that gets all the objects with tag foo
	//list = GetObjectListwithTag(foo);
};