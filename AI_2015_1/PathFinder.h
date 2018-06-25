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
	std::stack<TileNode*> m_backtrackstack;
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
		if (m_map!=nullptr)
		{
			delete m_map;
			m_startPoint = nullptr;
			m_endPoint = nullptr;
		}
		m_map = new Map(sourcemap.GetGridSize().x*TILESIZE,sourcemap.GetGridSize().y*TILESIZE);
		//m_map = &sourcemap;
		for (int i = 0; i < m_map->GetGridSize().x; ++i)
		{
			for (int j = 0; j < m_map->GetGridSize().y; ++j)
			{
				TileNode* t = new TileNode(sourcemap.GetTile(XVECTOR2(i, j)));
				if (t->Get() == TILETYPE::NONE)
				{
					t->Set(TILETYPE::NOTVISITED);
				}
				m_map->m_grid[i][j] = t;
				//if (m_map->m_grid[i][j]->Get() != TILETYPE::OBSTACLE &&
				//	m_map->m_grid[i][j]->Get() != TILETYPE::FINISH &&
				//	m_map->m_grid[i][j]->Get() != TILETYPE::START)
				//{
				//	m_map->m_grid[i][j]->Set(TILETYPE::NOTVISITED);
				//}
			}
		}
		SetStartingPoint(sourcemap.GetBeggining());
		SetEndingPoint(sourcemap.GetEnding());
		return true;
	}
	void SetStartingPoint(const XVECTOR2 start)
	{
		m_startPoint = start;
	}
	void SetEndingPoint(const XVECTOR2 finish)
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
			//m_map->Render(window);
		}
	}
	virtual void Search(sf::RenderWindow* window) = 0;
	virtual void CheckNode(const XVECTOR2 pos) = 0;
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
		//Starts the OpenList and inserts starting point as the first node in the list
		m_openList.empty();
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint/TILESIZE));
		while (state == PATHSTATE::SEARCHING)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (m_openList.size()>0)
			{
				m_node = m_openList.front();
				m_openList.pop();
				m_node->Set(TILETYPE::VISITED);
				if (m_node->m_tilePosition == m_endPoint)
				{
					state = PATHSTATE::FINISHED;
					break;
				}
				XVECTOR2 temp;
				//EAST NODE
				temp.x = m_node->m_tilePosition.x + TILESIZE; 
				temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x*TILESIZE)
				{
					CheckNode(temp);
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + TILESIZE; 
				temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.x < m_map->GetGridSize().x*TILESIZE && 
					temp.y < m_map->GetGridSize().y*TILESIZE)
				{
					CheckNode(temp);
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x; 
				temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.y < m_map->GetGridSize().y*TILESIZE)
				{
					CheckNode(temp);
				}
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - TILESIZE; 
				temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.x >= 0 && 
					temp.y < m_map->GetGridSize().y*TILESIZE)
				{
					CheckNode(temp);
				}
				//WEST NODE
				temp.x = m_node->m_tilePosition.x - TILESIZE; 
				temp.y = m_node->m_tilePosition.y;
				if (temp.x >= 0)
				{
					CheckNode(temp);
				}
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x - TILESIZE; 
				temp.y = m_node->m_tilePosition.y - TILESIZE;
				if (temp.x >= 0 && 
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x; 
				temp.y = m_node->m_tilePosition.y - TILESIZE;
				if (temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + TILESIZE; 
				temp.y = m_node->m_tilePosition.y - TILESIZE;
				if (temp.x < m_map->GetGridSize().x *TILESIZE && 
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				state = PATHSTATE::SEARCHING;
			}
			else state = PATHSTATE::FAILED;
			//Render(window);
		}
		if (state == PATHSTATE::FAILED)
		{
			//We return an error saying that the object is unable to get to the ending
			printf("OH NO! A FUCK UP!\n");
		}
		else if (state == PATHSTATE::FINISHED)
		{
			//We make backtracking
			printf("WE FOUND IT BOIS!\n");
			while (m_node->m_parent!=nullptr)
			{
				m_backtrackstack.push(m_node);
				m_node = m_node->m_parent;
				printf("%1.0f %1.0f \n", m_node->m_tilePosition.x, m_node->m_tilePosition.y);
			}
			printf("WE BACKTRACKED BOIS!\n");
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
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
		m_openList.empty();
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint / TILESIZE));
		while (state == PATHSTATE::SEARCHING)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (m_openList.size() > 0)
			{
				m_node = m_openList.top();
				m_openList.pop();
				m_node->Set(TILETYPE::VISITED);
				if (m_node->m_tilePosition == m_endPoint)
				{
					state = PATHSTATE::FINISHED;
					break;
				}
				XVECTOR2 temp;
				//EAST NODE
				temp.x = m_node->m_tilePosition.x + TILESIZE;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x*TILESIZE)
				{
					CheckNode(temp);
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + TILESIZE;
				temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.x < m_map->GetGridSize().x*TILESIZE &&
					temp.y < m_map->GetGridSize().y*TILESIZE)
				{
					CheckNode(temp);
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.y < m_map->GetGridSize().y*TILESIZE)
				{
					CheckNode(temp);
				}
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - TILESIZE;
				temp.y = m_node->m_tilePosition.y + TILESIZE;
				if (temp.x >= 0 &&
					temp.y < m_map->GetGridSize().y*TILESIZE)
				{
					CheckNode(temp);
				}
				//WEST NODE
				temp.x = m_node->m_tilePosition.x - TILESIZE;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x >= 0)
				{
					CheckNode(temp);
				}
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x - TILESIZE;
				temp.y = m_node->m_tilePosition.y - TILESIZE;
				if (temp.x >= 0 &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y - TILESIZE;
				if (temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + TILESIZE;
				temp.y = m_node->m_tilePosition.y - TILESIZE;
				if (temp.x < m_map->GetGridSize().x *TILESIZE &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				state = PATHSTATE::SEARCHING;
			}
			else state = PATHSTATE::FAILED;
			//Render(window);
		}
		if (state == PATHSTATE::FAILED)
		{
			//We return an error saying that the object is unable to get to the ending
			printf("OH NO! A FUCK UP!\n");
		}
		else if (state == PATHSTATE::FINISHED)
		{
			//We make backtracking
			printf("WE FOUND IT BOIS!\n");
			while (m_node->m_parent != nullptr)
			{
				m_backtrackstack.push(m_node);
				m_node = m_node->m_parent;
				printf("%1.0f %1.0f \n", m_node->m_tilePosition.x, m_node->m_tilePosition.y);
			}
			printf("WE BACKTRACKED BOIS!\n");
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
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
	void CheckNode(const XVECTOR2 pos)
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
	void CheckNode(const XVECTOR2 pos)
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
	void CheckNode(const XVECTOR2 pos)
	{

	}
};