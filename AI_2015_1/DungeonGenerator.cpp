#include "stdafx.h"
#include "DungeonGenerator.h"


DungeonGenerator::DungeonGenerator()
{
}


DungeonGenerator::~DungeonGenerator()
{
}
void DungeonGenerator::SeparateRooms()
{

}
void DungeonGenerator::SetMapBoundaries(int width, int height)
{
	m_MapSize = XVECTOR2(width, height);
}
void DungeonGenerator::GenerateDungeon(
	int seed,
	int minHeight,
	int minWidth,
	int maxHeight,
	int maxWidth,
	int circleRadius,
	int maxRooms,
	int minHeightselect,
	int maxHeightSelect,
	int minWidthSelect,
	int maxWidthSelect)
{
	std::vector<XVECTOR2> randomPoints = GenerateRandomPoints(circleRadius, seed, maxRooms);
	srand(seed);
	for (int i = 0; i< randomPoints.size(); ++i)
	{
		DungeonRoom room = {
			rand(),
			XVECTOR2(
				(randomPoints[i].x + (m_MapSize.x / 2)),
				(randomPoints[i].y + (m_MapSize.y / 2))),
			(minWidth + (rand() % (int)(maxWidth - minWidth + 1)))*TILESIZE,
			(minWidth + (rand() % (int)(maxWidth - minWidth + 1)))*TILESIZE };
		std::cout << room.m_position2d.x << " " << room.m_position2d.y << std::endl;

		m_Rooms.push_back(room);

	}

}
void DungeonGenerator::GenerateRooms(std::vector<XVECTOR2> pointLists)
{

}
void DungeonGenerator::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < m_Rooms.size(); ++i)
	{
		window->draw((m_Rooms[i]).m_mapDisplay);
	}
}
