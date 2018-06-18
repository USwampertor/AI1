#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	
}
Map::~Map()
{
	delete m_grid;
}
void Map::Initialize(int gridwidth, int gridheight)
{
	m_gridSize.x = (float)gridwidth/TILESIZE;
	m_gridSize.y = (float)gridheight/TILESIZE;
	m_grid = new int*[gridwidth];
	for (int i = 0; i < gridwidth; i+=TILESIZE)
	{
		m_grid[i] = new int[gridheight];
	}
}
void Map::SetBeggining(XVECTOR2 position)
{
	m_beggining = position;
}
XVECTOR2 Map::GetBeggining()
{
	return m_beggining;
}
void Map::SetEnding(XVECTOR2 position)
{
	m_ending = position;
}
XVECTOR2 Map::GetEnding()
{
	return m_ending;
}
void Map::AddObstacle(XVECTOR2 position)
{
	m_obstacles.push_back(position);
}
bool Map::DeleteObstacle(XVECTOR2 position)
{
	for ( auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		if (*it==position)
		{
			m_obstacles.erase(it);
			return true;
		}
	}
	return false;
}
bool Map::FindObstacle(XVECTOR2 position)
{
	for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		if (*it == position)
		{
			return true;
		}
	}
	return false;
}
std::list<XVECTOR2> Map::GetObstacleList()
{
	return m_obstacles;
}

