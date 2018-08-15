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
	m_position2d.x = (int)position.x - (int)position.x % TILESIZE;
	m_position2d.y = (int)position.y - (int)position.y % TILESIZE;
	m_width = width;
	m_height = height;
	SetRectangle();
	m_centerCircle.setRadius(2.5f);
	m_centerCircle.setFillColor(sf::Color::Yellow);
	m_centerCircle.setPosition(IDVtoSFML(m_roomCenter - XVECTOR2(2.5f, 2.5f)));
}
void DungeonRoom::Update()
{
	
	//m_position2d.x = (int)m_position2d.x - (int)m_position2d.x % TILESIZE;
	//m_position2d.y = (int)m_position2d.y - (int)m_position2d.y % TILESIZE;
	

}
void DungeonRoom::SetRoom()
{
	m_mapDisplay.setPosition(IDVtoSFML(m_position2d));
	SetCenter();
	m_centerCircle.setPosition(IDVtoSFML(m_roomCenter - XVECTOR2(2.5f, 2.5f)));
}
bool DungeonRoom::isColliding(std::vector<DungeonRoom*> neighbors)
{
	for (int i = 0; i < neighbors.size(); ++i)
	{
		if (neighbors[i]->m_ID != m_ID)
		{
			if (
				((neighbors[i]->m_position2d.x > m_position2d.x && neighbors[i]->m_position2d.x < m_position2d.x + m_width) ||
				(neighbors[i]->m_position2d.x + neighbors[i]->m_width > m_position2d.x && neighbors[i]->m_position2d.x < m_position2d.x)) &&
				((neighbors[i]->m_position2d.y > m_position2d.y && neighbors[i]->m_position2d.y < m_position2d.y + m_height) ||
				(neighbors[i]->m_position2d.y + neighbors[i]->m_height > m_position2d.y && neighbors[i]->m_position2d.y < m_position2d.y)))
			{
				return true;
			}
		}
	}
	return false;
}
void DungeonRoom::SetRectangle()
{
	m_mapDisplay.setSize(IDVtoSFML(XVECTOR2(m_width,m_height)));
	m_mapDisplay.setFillColor(DEFAULTCOLOR);
	m_mapDisplay.setOutlineThickness(1.0f);
	m_mapDisplay.setOutlineColor(sf::Color::White);
	m_mapDisplay.setPosition(IDVtoSFML(m_position2d));
	m_roomRadius = Maximum(m_width, m_height);
	SetCenter();
}
void DungeonRoom::SetCenter()
{
	m_roomCenter.x = m_position2d.x + m_width / 2;
	m_roomCenter.y = m_position2d.y + m_height / 2;
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
		float roomdistance = (room->m_roomCenter - m_roomCenter).Length();

		//if ((int)(room->m_roomCenter - m_roomCenter).Length() != 0 &&
		//	(room->m_roomCenter - m_roomCenter).Length() < m_roomRadius)
		if (
		((room->m_position2d.x > m_position2d.x && room->m_position2d.x < m_position2d.x + m_width)  || (room->m_position2d.x + room->m_width > m_position2d.x  && room->m_position2d.x < m_position2d.x)) &&
		((room->m_position2d.y > m_position2d.y && room->m_position2d.y < m_position2d.y + m_height) || (room->m_position2d.y + room->m_height > m_position2d.y && room->m_position2d.y < m_position2d.y)))
		{
			vGeneralAvoidance += (room->m_roomCenter - m_roomCenter);
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
int DungeonRoom::GetWidth()
{
	return m_width;
}
int DungeonRoom::GetHeight()
{
	return m_height;
}