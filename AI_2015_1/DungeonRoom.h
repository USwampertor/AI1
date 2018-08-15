#pragma once
#include "GameObject.h"
#define DEFAULTCOLOR sf::Color::Blue
class DungeonRoom : public GameObject
{
private:
	int m_ID, m_width, m_height;
public:
	int GetWidth();
	int GetHeight();
	float m_roomRadius;
	std::vector<DungeonRoom*> m_neighborRooms;
	XVECTOR2 m_lastForce = { 0,0 };
	XVECTOR2 m_roomCenter = { 0,0 };
	DungeonRoom();
	DungeonRoom(int id, XVECTOR2 position, int width, int height);
	~DungeonRoom();
	void SetRectangle();
	void Update();
	XVECTOR2 Distance();
	void SetCenter();
	void GetList(std::vector<DungeonRoom*> neighbors);
	sf::RectangleShape m_mapDisplay;
	sf::CircleShape m_centerCircle;
	bool isColliding(std::vector<DungeonRoom*> neighbors);
	void SetRoom();
};

