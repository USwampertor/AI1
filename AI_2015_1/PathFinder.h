#pragma once
#include <IDVMath.h>
#include <queue>
#include <stack>
#include "Map.h"
//BASE FOR PATHFINDING ALGORITHMS
class PathFinder
{
private:
	XVECTOR2 m_startPoint, m_endPoint;
	Map* m_map;
	TileNode* m_node;
public:
	PathFinder()
	{

	}
	~PathFinder()
	{

	}
	bool Initialize(Map* sourcemap)
	{
		if (!(m_map = sourcemap))
		{
			std::cout << "Failed to copy map..\n";
			return false;
		}
		for (int i = 0; i < m_map->GetGridSize().x; ++i)
		{
			for (int j = 0; j < m_map->GetGridSize().y; ++j)
			{
				if (m_map->m_grid[i][j].Get() != TILETYPE::OBSTACLE)
				{
					m_map->m_grid[i][j].Set(TILETYPE::NOTVISITED);
				}
			}
		}
		SetStartingPoint(sourcemap->GetBeggining());
		SetEndingPoint(sourcemap->GetEnding());
		return true;
	}
	void SetStartingPoint(XVECTOR2 start)
	{
		m_startPoint = start;
	}
	void SetEndingPoint(XVECTOR2 finish)
	{
		m_endPoint = finish;
	}
	void Render(sf::RenderWindow* window)
	{
		for (int i = 0; i < m_map->GetGridSize().x; ++i)
		{
			for (int j = 0; j < m_map->GetGridSize().y; ++j)
			{
				window->draw(m_map->m_grid[i][j].m_tile);
			}
		}
	}
	virtual void Search() = 0;
};
class BFS : public PathFinder
{
	std::queue<TileNode*> m_openList;
	BFS()
	{

	}
	~BFS()
	{

	}
	void Search()
	{

	}
};
class DFS : public PathFinder
{
	std::stack<TileNode*> m_openList;
	DFS()
	{

	}
	~DFS()
	{

	}
	void Search()
	{

	}
};
class Dijkstra : public PathFinder
{
	std::queue<TileNode*> m_openList;
	Dijkstra()
	{

	}
	~Dijkstra()
	{

	}
	void Search()
	{

	}
};
class BestSearch : public PathFinder
{
	std::priority_queue<TileNode*> m_openList;
	BestSearch()
	{

	}
	~BestSearch()
	{

	}
	void Search()
	{

	}
};
class Astar : public PathFinder
{
private:
	std::priority_queue<TileNode*> m_openList;
public:
	Astar()
	{

	}
	~Astar()
	{

	}
	void Search()
	{

	}
};