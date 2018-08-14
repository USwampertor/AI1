#pragma once
#include "GameObject.h"
#define DEFAULTCOLOR sf::Color::Blue
class DungeonRoom : public GameObject
{
private:
	int m_ID, m_roomCenter, m_width, m_height;
public:
	float m_roomRadius;
	std::vector<DungeonRoom*> m_neighborRooms;
	XVECTOR2 m_lastForce = {0,0};
	DungeonRoom();
	DungeonRoom(int id, XVECTOR2 position, int width, int height);
	~DungeonRoom();
	void SetRectangle();
	void Update();
	XVECTOR2 Distance();
	void GetList(std::vector<DungeonRoom*> neighbors);
	sf::RectangleShape m_mapDisplay;
};

