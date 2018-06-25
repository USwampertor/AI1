#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	
}
Map::Map(const Map& copy)
{
	*this = copy;
}
Map::Map(int gridwidth, int gridheight)
{
	m_gridSize.x = (float)gridwidth / TILESIZE;
	m_gridSize.y = (float)gridheight / TILESIZE;
	MapGrid grid(m_gridSize.x, std::vector<TileNode*>(m_gridSize.y));
	m_grid = grid;
}
Map::~Map()
{
	//delete m_grid;
}
void Map::Initialize(int gridwidth, int gridheight)
{
	m_gridSize.x = (float)gridwidth / TILESIZE;
	m_gridSize.y = (float)gridheight / TILESIZE;
	MapGrid grid(m_gridSize.x, std::vector<TileNode*>(m_gridSize.y));
	m_grid = grid;
	for (int i = 0; i < m_gridSize.x; ++i)
	{
		//m_grid[i] = new TileNode[gridheight];
		for (int j = 0; j < m_gridSize.y; ++j)
		{
			TileNode* t = new TileNode(XVECTOR2(i*TILESIZE, j*TILESIZE), TILESIZE);
			m_grid[i][j] = t;
		}
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
void Map::SetTile(XVECTOR2 vec, TILETYPE type)
{
	vec /= TILESIZE;
	(m_grid[vec.x][vec.y])->Set(type);
}
bool Map::FindTile(XVECTOR2 vec, TILETYPE type)
{
	vec /= TILESIZE;
	return (m_grid[vec.x][vec.y])->Get() == type;
}
void Map::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < m_gridSize.x; ++i)
	{
		for (int j = 0; j < m_gridSize.y; ++j)
		{
			window->draw((m_grid[i][j])->m_tile);
		}
	}
}
XVECTOR2 Map::GetGridSize()
{
	return m_gridSize;
}
TileNode Map::GetTile(XVECTOR2 pos)
{
	return *m_grid[pos.x][pos.y];
}

