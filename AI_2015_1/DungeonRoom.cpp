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
void DungeonRoom::Update()
{
	m_position2d += Distance();
	m_mapDisplay.setPosition(IDVtoSFML(m_position2d));
}
void DungeonRoom::SetRectangle()
{
	m_mapDisplay.setSize(IDVtoSFML(XVECTOR2(m_width,m_height)));
	m_mapDisplay.setFillColor(DEFAULTCOLOR);
	m_mapDisplay.setOutlineThickness(1.0f);
	m_mapDisplay.setOutlineColor(sf::Color::White);
	m_mapDisplay.setPosition(IDVtoSFML(m_position2d));
	m_roomRadius = Maximum(m_width, m_height);
}
void DungeonRoom::GetList(std::vector<DungeonRoom*> neighbors)
{
	m_neighborRooms = neighbors;
}
XVECTOR2 DungeonRoom::Distance()
{
	int iNeighBorRooms = 0;
	XVECTOR2 vGeneralAvoidance = { 0,0 };
	for each(DungeonRoom* room in m_neighborRooms)
	{
		float roomdistance = (room->m_position2d - m_position2d).Length();

		if ((room->m_position2d - m_position2d).Length() != 0 &&
			(room->m_position2d - m_position2d).Length() < m_roomRadius)
		{
			vGeneralAvoidance += (room->m_position2d - m_position2d);
			++iNeighBorRooms;
		}
	}
	if (iNeighBorRooms != 0)
	{
		vGeneralAvoidance /= iNeighBorRooms;
		vGeneralAvoidance *= -1;
		vGeneralAvoidance.Normalize();
		vGeneralAvoidance *= 2.0f;
	}
	m_lastForce = vGeneralAvoidance;
	return vGeneralAvoidance;
}