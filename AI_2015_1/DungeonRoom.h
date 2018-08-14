#pragma once
#include "GameObject.h"
#define DEFAULTCOLOR sf::Color::Blue
class DungeonRoom : public GameObject
{
private:
	int m_ID, m_roomCenter, m_width, m_height;
public:
	DungeonRoom();
	DungeonRoom(int id, XVECTOR2 position, int width, int height);
	~DungeonRoom();
	void SetRectangle();
	
	
	sf::RectangleShape m_mapDisplay;
};

