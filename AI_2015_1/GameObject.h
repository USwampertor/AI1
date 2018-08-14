#pragma once
#include "Utilities.h"
enum class OBJECT_TYPE
{
	OBSTACLE = 0,
	BOID,
	PLAYER,
	FLAG,
	DUNGEON,
	ITEM,

};


class GameObject
{
public:
	XVECTOR2 m_position2d;
	std::string m_tag;
	float boundary;
	GameObject();
	~GameObject();
	
	void SetPosition(float x, float y);
	

};
