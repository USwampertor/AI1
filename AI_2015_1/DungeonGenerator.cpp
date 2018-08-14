#include "stdafx.h"
#include "DungeonGenerator.h"


DungeonGenerator::DungeonGenerator()
{
}


DungeonGenerator::~DungeonGenerator()
{
}
void DungeonGenerator::SetWindow(sf::RenderWindow* w)
{
	m_window = w;
}
void DungeonGenerator::SeparateRooms()
{
	/*What we gonna do boys, no no, here me out. We gonna make this little bastards to 
	stand the fuck aside until the vectors they return are less that a given value. But,
	wait wait, come back, bare me for a moment. We gonna be in this function checking the
	total sum of the vectors until they give us a good and nice 0~. That means that all 
	rooms are scattered without problems*/
	for (int i = 0; i < m_Rooms.size(); ++i)
	{
		m_Rooms[i]->m_neighborRooms = m_Rooms;
	}

	//XVECTOR2 totalSum = { 0,0 };
	float tLength = 1.5f, separationforce = 0.0f;
	int roomsSeparating = 0;
	do
	{
		//system("cls");
		//totalSum = { 0,0 };
		roomsSeparating = 0;
		for (int i = 0; i < m_Rooms.size(); ++i)
		{
			m_Rooms[i]->Update();
			//totalSum += m_Rooms[i]->m_lastForce;
			separationforce = m_Rooms[i]->m_lastForce.Length();
			std::cout << separationforce << std::endl;
			if (separationforce > tLength)
				++roomsSeparating;
			//m_window->draw(m_Rooms[i]->m_mapDisplay);
		}
		//tLength = totalSum.Length();
	} while (roomsSeparating>100);

	
}
void DungeonGenerator::SetMapBoundaries(int width, int height)
{
	m_MapCenter = XVECTOR2(width/2.0f, height/2.0f);
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
	m_Rooms.clear();
	std::vector<XVECTOR2> randomPoints = GenerateRandomPoints(circleRadius, seed, maxRooms);
	srand(seed);
	for (int i = 0; i< randomPoints.size(); ++i)
	{
		randomPoints[i].x += m_MapCenter.x;
		randomPoints[i].y += m_MapCenter.y;
		DungeonRoom* room = new DungeonRoom(
			rand(),
			randomPoints[i],
			(minWidth + (rand() % (int)(maxWidth - minWidth + 1)))*TILESIZE,
			(minHeight + (rand() % (int)(maxHeight - minHeight + 1)))*TILESIZE);
		//std::cout << room->m_position2d.x << " " << room->m_position2d.y << std::endl;
		m_Rooms.push_back(room);
	}
	SeparateRooms();
}
void DungeonGenerator::GenerateRooms(std::vector<XVECTOR2> pointLists)
{

}
void DungeonGenerator::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < m_Rooms.size(); ++i)
	{
		window->draw((m_Rooms[i])->m_mapDisplay);
		window->draw((m_Rooms[i])->m_centerCircle);
	}
}
