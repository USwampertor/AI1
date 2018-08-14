#include "stdafx.h"
#include "DungeonRoom.h"


DungeonRoom::DungeonRoom()
{
}


DungeonRoom::~DungeonRoom()
{
}

DungeonRoom::DungeonRoom(int id, XVECTOR2 position, int width, int height)
{
	m_ID = id;
	m_position2d = position;
	m_width = width;
	m_height = height;
	SetRectangle();
}
void DungeonRoom::SetRectangle()
{
	m_mapDisplay.setSize(IDVtoSFML(XVECTOR2(m_width,m_height)));
	m_mapDisplay.setFillColor(DEFAULTCOLOR);
	m_mapDisplay.setOutlineColor(sf::Color::White);
	m_mapDisplay.setPosition(IDVtoSFML(m_position2d));
}
