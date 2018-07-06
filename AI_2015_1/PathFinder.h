#pragma once
#include <IDVMath.h>
#include <queue>
#include <stack>
#include <list>
#include "Map.h"
#define _PULLSTRING
#define MANHATTAN
//#define EUCLIDEAN
//#define SQUARESUM

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
	std::vector<TileNode*> m_backtracklist;
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
	virtual bool Initialize(Map sourcemap) = 0;
	void SetStartingPoint(const XVECTOR2 start)
	{
		m_startPoint = start;
	}
	void SetEndingPoint(const XVECTOR2 finish)
	{
		m_endPoint = finish;
	}
	void RenderPath(sf::RenderWindow* window)
	{
		//This only renders the final path to go from A to B
		if (this->m_map!= nullptr)
		{
			for (int i = 0 ; i < m_backtracklist.size(); ++i)
			{
				window->draw(m_backtracklist[i]->m_tile);
			}
		}
	}
	void Render(sf::RenderWindow* window)
	{
		//DEPRECATED SHIT, DONT USE IT!
		if (this->m_map != nullptr)
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
	void PullString()
	{
		std::vector<TileNode*> temp;
		temp.push_back(m_backtracklist[0]);
		XVECTOR2 actualpos = m_startPoint;
		XVECTOR2 newpos;
		for (int i = 1; i < m_backtracklist.size(); ++i)
		{
			if ((i + 1) >= m_backtracklist.size()) break;
			newpos = m_backtracklist[i + 1]->m_tilePosition;
			//If we cant get from a to b with a straight line, we put i in the temp
			if (!Bresenham(actualpos/TILESIZE, newpos/TILESIZE))
			{
				temp.push_back(m_backtracklist[i]);
				actualpos = m_backtracklist[i]->m_tilePosition;
			}
			//else we keep going as if life was good
		}
	
		temp.push_back(m_backtracklist[m_backtracklist.size()-1]);
		m_backtracklist.clear();
		m_backtracklist = temp;
	}
	bool Bresenham(XVECTOR2 start, XVECTOR2 finish)
	{
		XVECTOR2 actual = start, last;
		float ydelta = (finish.y - start.y);
		float xdelta = (finish.x - start.x);
		float slope = ydelta / xdelta;
		if (slope < 1.0f)
		{
			last = actual;
			float pk = 2 * ydelta - xdelta;
			if (pk >= 0.0f) actual.y += 1.0f;
			actual.x += 1.0f;
			while (actual != finish)
			{
				pk = pk + 2 * ydelta - 2 * xdelta*(actual.y-last.y);
				last = actual;
				if (pk >= 0.0f) actual.y += 1.0f;
				actual.x += 1.0f;
				actual.x = (int)actual.x % (int)m_map->GetGridSize().x;
				actual.y = (int)actual.y % (int)m_map->GetGridSize().y;
				if (m_map->FindTile((actual*TILESIZE), TILETYPE::OBSTACLE)) return false;
			}
		}
		else
		{
			last = actual;
			float pk = 2 * xdelta - ydelta;
			if (pk >= 0.0f) actual.x += 1.0f;
			actual.y += 1;
			while (actual != finish)
			{
				pk = pk + 2 * xdelta - 2 * ydelta*(actual.x - last.x);
				last = actual;
				if (pk >= 0.0f) actual.x += 1.0f;
				actual.y += 1.0f;
				actual.x = (int)actual.x % (int)m_map->GetGridSize().x;
				actual.y = (int)actual.y % (int)m_map->GetGridSize().y;
				if (m_map->FindTile((actual*TILESIZE), TILETYPE::OBSTACLE)) return false;
			}
		}
		return true;
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
	bool Initialize(Map sourcemap)
	{
		printf("Initializing...\n");
		if (m_map != nullptr)
		{
			delete m_map;
			m_startPoint = { 0,0 };
			m_endPoint = { 0,0 };
		}
		m_map = new Map(sourcemap.GetGridSize().x*TILESIZE, sourcemap.GetGridSize().y*TILESIZE);
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
	void Search(sf::RenderWindow* window)
	{
		m_backtracklist.clear();
		//Starts the OpenList and inserts starting point as the first node in the list
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint/TILESIZE));
		while (PATHSTATE::SEARCHING == state)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (!m_openList.empty())
			{
				m_node = m_openList.front();
				m_openList.pop();
				
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
				m_backtracklist.push_back(m_node);
				m_node = m_node->m_parent;
			}
			printf("WE BACKTRACKED BOIS!\n");
			std::reverse(m_backtracklist.begin(), m_backtracklist.end());
#ifdef PULLSTRING
			PullString();
#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->Set(TILETYPE::VISITED);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
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
	bool Initialize(Map sourcemap)
	{
		printf("Initializing...\n");
		if (m_map != nullptr)
		{
			delete m_map;
			m_startPoint = { 0,0 };
			m_endPoint = { 0,0 };
		}
		m_map = new Map(sourcemap.GetGridSize().x*TILESIZE, sourcemap.GetGridSize().y*TILESIZE);
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
	void Search(sf::RenderWindow* window)
	{
		m_backtracklist.clear();
		//Starts the OpenList and inserts starting point as the first node in the list
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint / TILESIZE));
		while (PATHSTATE::SEARCHING == state)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (!m_openList.empty())
			{
				m_node = m_openList.top();
				m_openList.pop();

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
				m_backtracklist.push_back(m_node);
				m_node = m_node->m_parent;
			}
			printf("WE BACKTRACKED BOIS!\n");
			std::reverse(m_backtracklist.begin(), m_backtracklist.end());
#ifdef PULLSTRING
			PullString();
#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->Set(TILETYPE::VISITED);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
	}
};
//DIJKSTRA ALGORITHM
class Dijkstra : public PathFinder
{
private:
	std::priority_queue<TileNode*,std::vector<TileNode*>,std::less<TileNode*>> m_openList;
public:
	Dijkstra()
	{

	}
	~Dijkstra()
	{

	}
	bool Initialize(Map sourcemap)
	{
		printf("Initializing...\n");
		if (m_map != nullptr)
		{
			delete m_map;
			m_startPoint = { 0, 0};
			m_endPoint = { 0, 0 };
		}
		m_map = new Map(sourcemap.GetGridSize().x*TILESIZE, sourcemap.GetGridSize().y*TILESIZE);
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
	void Search(sf::RenderWindow* window)
	{
		m_backtracklist.clear();
		//Starts the OpenList and inserts starting point as the first node in the list
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint / TILESIZE));
		while (PATHSTATE::SEARCHING == state)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (!m_openList.empty())
			{
				m_node = m_openList.top();
				m_openList.pop();

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
				m_backtracklist.push_back(m_node);
				m_node = m_node->m_parent;
			}
			printf("WE BACKTRACKED BOIS!\n");
			std::reverse(m_backtracklist.begin(), m_backtracklist.end());
#ifdef PULLSTRING
			PullString();
#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_fCost >= OBSTACLECOST||
			(m_node->m_fCost + m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->cost >= 
			m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_fCost &&
				m_map->FindTile(pos, TILETYPE::VISITED)))
		{
			return;
		}
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_fCost = 
			m_node->m_fCost + m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->cost;
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
		if (m_map->FindTile(pos, TILETYPE::VISITED))return;
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->Set(TILETYPE::VISITED);
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
	}
};
//BESTSEARCH ALGORITHM
class BestSearch : public PathFinder
{
private:
	//std::priority_queue<CostedTile*,std::vector<CostedTile*>,LessCost> m_openList;
	std::priority_queue<TileNode*, std::vector<TileNode*>, std::greater<TileNode*>> m_openList;

public:
	//We need to override the < > operators to have the comparison for this thing
	BestSearch()
	{
	}
	~BestSearch()
	{

	}
	bool Initialize(Map sourcemap)
	{
		printf("Initializing...\n");
		if (m_map != nullptr)
		{
			delete m_map;
			m_startPoint = { 0, 0 };
			m_endPoint = { 0, 0 };
		}
		m_map = new Map(sourcemap.GetGridSize().x*TILESIZE, sourcemap.GetGridSize().y*TILESIZE);
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
				//CostedTile* t = new CostedTile();
				//t->SetInfo(&sourcemap.GetTile(XVECTOR2(i, j)));
				//if (t->Get() == TILETYPE::NONE)
				//{
				//	t->Set(TILETYPE::NOTVISITED);
				//}
				//m_map->m_grid[i][j] = t;
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
	void Search(sf::RenderWindow* window)
	{
		m_backtracklist.clear();
		//Starts the OpenList and inserts starting point as the first node in the list
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint / TILESIZE));
		while (PATHSTATE::SEARCHING == state)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (!m_openList.empty())
			{
				m_node = m_openList.top();
				m_openList.pop();

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
				m_backtracklist.push_back(m_node);
				m_node = m_node->m_parent;
			}
			printf("WE BACKTRACKED BOIS!\n");
			std::reverse(m_backtracklist.begin(), m_backtracklist.end());
#ifdef PULLSTRING
			PullString();
#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_fCost =
			(int)XVEC2SqrSum(pos, m_endPoint);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->Set(TILETYPE::VISITED);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
		//m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
		//m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
	}
};
//A STAR ALGORITHM
class Astar : public PathFinder
{
private:
	std::priority_queue<TileNode*,std::vector<TileNode*>,std::greater<TileNode*>> m_openList;
public:
	Astar()
	{

	}
	~Astar()
	{

	}
	bool Initialize(Map sourcemap)
	{
		printf("Initializing...\n");
		if (m_map != nullptr)
		{
			delete m_map;
			m_startPoint = { 0, 0 };
			m_endPoint = { 0, 0 };
		}
		m_map = new Map(sourcemap.GetGridSize().x*TILESIZE, sourcemap.GetGridSize().y*TILESIZE);
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
	void Search(sf::RenderWindow* window)
	{
		m_backtracklist.clear();
		//Starts the OpenList and inserts starting point as the first node in the list
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint / TILESIZE));
		while (PATHSTATE::SEARCHING == state)
		{
			//state will continue searching until it realizes its unable to get there
			//or actually got there
			if (!m_openList.empty())
			{
				m_node = m_openList.top();
				m_openList.pop();

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
				m_backtracklist.push_back(m_node);
				m_node = m_node->m_parent;
			}
			printf("WE BACKTRACKED BOIS!\n");
			std::reverse(m_backtracklist.begin(), m_backtracklist.end());
#ifdef PULLSTRING
			PullString();
#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{

		if (m_map->FindTile(pos, TILETYPE::OBSTACLE))
		{
			return;
		}
		int tmpcost = 0;
#ifdef MANHATTAN
		tmpcost = ManhattanDistance(pos, m_endPoint);
#endif
#ifdef EUCLIDEAN
		tmpcost = EuclideanDistance(pos, m_endPoint);
#endif
#ifdef SQUARESUM
		tmpcost = XVEC2SqrSum(pos, m_endPoint);
#endif
		tmpcost +=
			(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->cost + m_node->m_costsofar);
		if (m_map->FindTile(pos, TILETYPE::VISITED) && 
			tmpcost >= m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->cost) return;
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_fCost = tmpcost;
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_costsofar = 
			(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->cost + m_node->m_costsofar);
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
		if (m_map->FindTile(pos, TILETYPE::VISITED)) return;
		m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->Set(TILETYPE::VISITED);
		m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
		//m_openList.push(m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]);
		//m_map->m_grid[pos.x / TILESIZE][pos.y / TILESIZE]->m_parent = m_node;
	}
};