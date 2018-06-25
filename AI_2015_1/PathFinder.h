#pragma once
#include <IDVMath.h>
#include <queue>
#include <stack>
#include "Map.h"
//BASE FOR PATHFINDING ALGORITHMS
enum class PATHSTATE
{
	UNDEFINED = 0,
	SEARCHING,
	FINISHED,
	FAILED
};
class PathFinder
{
public:
	TileNode* m_node;
	Map* m_map;
	XVECTOR2 m_startPoint, m_endPoint;
	PathFinder()
	{
		m_map = nullptr;
	}
	~PathFinder()
	{
		if (m_map != nullptr)
		{
			for (int i = 0; i < m_map->GetGridSize().x; ++i)
		{
			for (int j = 0; j < m_map->GetGridSize().y; ++j)
			{
				delete m_map->m_grid[i][j];
			}
		}
		}
	}
	bool Initialize(Map sourcemap)
	{
		printf("Initializing...\n");
		//m_map = new Map();
		m_map = &sourcemap;
		for (int i = 0; i < m_map->GetGridSize().x; ++i)
		{
			for (int j = 0; j < m_map->GetGridSize().y; ++j)
			{
				//TileNode* t = new TileNode(sourcemap.GetTile(XVECTOR2(i, j)));
				//if (t->Get() == TILETYPE::NONE)
				//{
				//	t->Set(TILETYPE::NOTVISITED);
				//}
				//m_map->m_grid[i][j] = t;
				if (m_map->m_grid[i][j]->Get() != TILETYPE::OBSTACLE &&
					m_map->m_grid[i][j]->Get() != TILETYPE::FINISH &&
					m_map->m_grid[i][j]->Get() != TILETYPE::START)
				{
					m_map->m_grid[i][j]->Set(TILETYPE::NOTVISITED);
				}
			}
		}
		SetStartingPoint(m_map->GetBeggining());
		SetEndingPoint(m_map->GetEnding());
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
		if (this->m_map!= nullptr)
		{
			for (int i = 0; i < m_map->GetGridSize().x; ++i)
			{
				for (int j = 0; j < m_map->GetGridSize().y; ++j)
				{
					window->draw(m_map->m_grid[i][j]->m_tile);
				}
			}

		}
	}
	virtual void Search(sf::RenderWindow* window) = 0;
	virtual void CheckNode() = 0;
};
//BFS ALGORITHM
class BFS : public PathFinder
{
private:
	std::queue<TileNode*> m_openList;
public:
	BFS()
	{

	}
	~BFS()
	{

	}
	void Search(sf::RenderWindow* window)
	{
		//Starts the OpenList
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint));
		while (state == PATHSTATE::SEARCHING)
		{
			if (m_openList.size()>0)
			{
				m_node = m_openList.front();
				m_openList.pop();
				if (m_node->m_tilePosition == m_endPoint)
				{
					state = PATHSTATE::FINISHED;
				}
				XVECTOR2 temp;
				//EAST NODE
				temp.x = m_node->m_tilePosition.x + TILESIZE; temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x)
				{
					CheckNode();
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + TILESIZE; temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.x < m_map->GetGridSize().x && temp.x < m_map->GetGridSize().x)
				{
					CheckNode();
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x; temp.y = m_node->m_tilePosition.y + TILESIZE;
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - TILESIZE; temp.y = m_node->m_tilePosition.y + TILESIZE;
				//WEST NODE
				temp.x = m_node->m_tilePosition.x + TILESIZE; temp.y = m_node->m_tilePosition.y;
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x + TILESIZE; temp.y = m_node->m_tilePosition.y;
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x + TILESIZE; temp.y = m_node->m_tilePosition.y;
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + TILESIZE; temp.y = m_node->m_tilePosition.y;
			}
			else state = PATHSTATE::FAILED;
			Render(window);
		}
	}
	void CheckNode()
	{

	}

};
//DFS ALGORITHM
class DFS : public PathFinder
{
private:
	std::stack<TileNode*> m_openList;
public:
	DFS()
	{

	}
	~DFS()
	{

	}
	void Search(sf::RenderWindow* window)
	{
		Render(window);
	}
	void CheckNode()
	{

	}
};
//DIJKSTRA ALGORITHM
class Dijkstra : public PathFinder
{
private:
	std::queue<TileNode*> m_openList;
public:
	Dijkstra()
	{

	}
	~Dijkstra()
	{

	}
	void Search(sf::RenderWindow* window)
	{
		Render(window);
	}
	void CheckNode()
	{

	}
};
//BESTSEARCH ALGORITHM
class BestSearch : public PathFinder
{
private:
	std::priority_queue<TileNode*> m_openList;
public:
	BestSearch()
	{

	}
	~BestSearch()
	{

	}
	void Search(sf::RenderWindow* window)
	{
		Render(window);
	}
	void CheckNode()
	{

	}
};
//A STAR ALGORITHM
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
	void Search(sf::RenderWindow* window)
	{
		Render(window);
	}
	void CheckNode()
	{

	}
};