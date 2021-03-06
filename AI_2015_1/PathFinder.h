#pragma once
#include <IDVMath.h>
#include <queue>
#include <stack>
#include <list>
#include "Map.h"
#define PULLSTRING
#define MANHATTAN
#define _EUCLIDEAN
#define _SQUARESUM

//BASE FOR PATHFINDING ALGORITHMS
enum class PATHSTATE
{
	UNDEFINED = 0,
	SEARCHING,
	FINISHED,
	FAILED
};
enum class HEURISTIC
{
	H_MANHATTAN = 0,
	H_EUCLIDEAN,
	H_SQUARESUM
};
struct NodeComparator : public std::binary_function<TileNode*, TileNode*, bool>
{
	bool operator()(const TileNode* leftNode, const TileNode* rightNode) const 
	{
		return leftNode->m_fCost > rightNode->m_fCost;
	}
};

class PathFinder
{
public:
	TileNode* m_node;
	Map* m_map;
	XVECTOR2 m_startPoint, m_endPoint;
	std::vector<TileNode*> m_backtracklist;
	sf::VertexArray m_finalLines;
	HEURISTIC m_activeHeuristic = HEURISTIC::H_MANHATTAN;
	bool m_usingPullstring = false;
	
	PathFinder()
	{
		m_map = nullptr;
	}
	PathFinder(bool pullstring, HEURISTIC h)
	{
		m_usingPullstring = pullstring;
		m_activeHeuristic = h;
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
		
	}
	void RenderLines(sf::RenderWindow* window)
	{
		if (this->m_map != nullptr)
		{
				window->draw(m_finalLines);
			
		}
	}
	void PullString()
	{
		std::vector<TileNode*> temp;
		temp.push_back(m_backtracklist[0]);
		m_map->m_grid[m_backtracklist[0]->m_tilePosition.x][m_backtracklist[0]->m_tilePosition.y]->m_tile.setFillColor(sf::Color::Black);
		XVECTOR2 actualpos = m_startPoint;
		XVECTOR2 newpos;
		for (int i = 1; i < m_backtracklist.size(); ++i)
		{
			if ((i + 2) >= m_backtracklist.size()) break;
			newpos = m_backtracklist[i+2]->m_tilePosition;
			//If we cant get from a to b with a straight line, we put i in the temp
			if (!Bresenham(actualpos, newpos))
			{
				temp.push_back(m_backtracklist[i+1]);
				m_map->m_grid[m_backtracklist[i+1]->m_tilePosition.x][m_backtracklist[i+1]->m_tilePosition.y]->m_tile.setFillColor(sf::Color::Black);
				actualpos = m_backtracklist[i]->m_tilePosition;
			}
			//else we keep going as if life was good
		}
		m_map->m_grid[m_backtracklist[m_backtracklist.size() - 2]->m_tilePosition.x][m_backtracklist[m_backtracklist.size() - 2]->m_tilePosition.y]->m_tile.setFillColor(sf::Color::Black);
		temp.push_back(m_backtracklist[m_backtracklist.size()-2]);
		sf::VertexArray v(sf::LinesStrip, temp.size());
		for (int i = 0; i < temp.size(); ++i)
		{
			v[i].position = sf::Vector2f(GridtoPixel(temp[i]->m_tilePosition).x, GridtoPixel(temp[i]->m_tilePosition).y);
			v[i].color = sf::Color(100,100,100,255);
		}
		m_finalLines = v;
		//m_backtracklist.clear();
		//m_backtracklist = temp;
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
				if (m_map->FindTile((actual), TILETYPE::OBSTACLE)) return false;
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
				if (m_map->FindTile((actual), TILETYPE::OBSTACLE)) return false;
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
	BFS(bool pullstring, HEURISTIC h)
	{
		m_usingPullstring = pullstring;
		m_activeHeuristic = h;
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
		m_openList.push(&m_map->GetTile(m_startPoint));
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
				temp.x = m_node->m_tilePosition.x + 1; 
				temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x)
				{
					CheckNode(temp);
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + 1; 
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x < m_map->GetGridSize().x && 
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x; 
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - 1; 
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x >= 0 && 
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//WEST NODE
				temp.x = m_node->m_tilePosition.x - 1; 
				temp.y = m_node->m_tilePosition.y;
				if (temp.x >= 0)
				{
					CheckNode(temp);
				}
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x - 1; 
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x >= 0 && 
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x; 
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + 1; 
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x < m_map->GetGridSize().x && 
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				state = PATHSTATE::SEARCHING;
			}
			else state = PATHSTATE::FAILED;
			
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
//#ifdef PULLSTRING
			if(m_usingPullstring) PullString();
//#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_map->m_grid[pos.x][pos.y]->Set(TILETYPE::VISITED);
		m_map->m_grid[pos.x][pos.y]->m_parent = m_node;
		m_openList.push(m_map->m_grid[pos.x][pos.y]);
		//
		

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
	DFS(bool pullstring, HEURISTIC h)
	{
		m_usingPullstring = pullstring;
		m_activeHeuristic = h;
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
		m_openList.push(&m_map->GetTile(m_startPoint));
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
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x)
				{
					CheckNode(temp);
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x < m_map->GetGridSize().x &&
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x >= 0 &&
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//WEST NODE
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x >= 0)
				{
					CheckNode(temp);
				}
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x >= 0 &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x < m_map->GetGridSize().x &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				state = PATHSTATE::SEARCHING;
			}
			else state = PATHSTATE::FAILED;
			Render(window);
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
//#ifdef PULLSTRING
			if (m_usingPullstring) PullString();
//#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_map->m_grid[pos.x][pos.y]->Set(TILETYPE::VISITED);
		m_map->m_grid[pos.x][pos.y]->m_parent = m_node;
		m_openList.push(m_map->m_grid[pos.x][pos.y]);
		//
		
	}
};

//DIJKSTRA ALGORITHM
class Dijkstra : public PathFinder
{
	
private:
	std::queue<TileNode*> m_openList;
	std::vector<TileNode*> m_closedList;
public:
	Dijkstra()
	{

	}
	Dijkstra(bool pullstring, HEURISTIC h)
	{
		m_usingPullstring = pullstring;
		m_activeHeuristic = h;
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
		m_closedList.clear();
		//Starts the OpenList and inserts starting point as the first node in the list
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		PATHSTATE state = PATHSTATE::SEARCHING;
		m_openList.push(&m_map->GetTile(m_startPoint));
		//state will continue searching until it realizes its unable to get there
		//or actually got there
		while (!m_openList.empty())
		{
			m_node = m_openList.front();
			m_openList.pop();

			XVECTOR2 temp;
			//EAST NODE
			temp.x = m_node->m_tilePosition.x + 1;
			temp.y = m_node->m_tilePosition.y;
			if (temp.x < m_map->GetGridSize().x)
			{
				CheckNode(temp);
			}
			//EAST SOUTH
			temp.x = m_node->m_tilePosition.x + 1;
			temp.y = m_node->m_tilePosition.y + 1;
			if (temp.x < m_map->GetGridSize().x &&
				temp.y < m_map->GetGridSize().y)
			{
				CheckNode(temp);
			}
			//SOUTH NODE
			temp.x = m_node->m_tilePosition.x;
			temp.y = m_node->m_tilePosition.y + 1;
			if (temp.y < m_map->GetGridSize().y)
			{
				CheckNode(temp);
			}
			//SOUTH WEST
			temp.x = m_node->m_tilePosition.x - 1;
			temp.y = m_node->m_tilePosition.y + 1;
			if (temp.x >= 0 &&
				temp.y < m_map->GetGridSize().y)
			{
				CheckNode(temp);
			}
			//WEST NODE
			temp.x = m_node->m_tilePosition.x - 1;
			temp.y = m_node->m_tilePosition.y;
			if (temp.x >= 0)
			{
				CheckNode(temp);
			}
			//NORTH WEST
			temp.x = m_node->m_tilePosition.x - 1;
			temp.y = m_node->m_tilePosition.y - 1;
			if (temp.x >= 0 &&
				temp.y >= 0)
			{
				CheckNode(temp);
			}
			//NORTH NODE
			temp.x = m_node->m_tilePosition.x;
			temp.y = m_node->m_tilePosition.y - 1;
			if (temp.y >= 0)
			{
				CheckNode(temp);
			}
			//NORTH EAST
			temp.x = m_node->m_tilePosition.x + 1;
			temp.y = m_node->m_tilePosition.y - 1;
			if (temp.x < m_map->GetGridSize().x &&
				temp.y >= 0)
			{
				CheckNode(temp);
			}

			m_closedList.push_back(m_node);
			state = PATHSTATE::SEARCHING;
		}
		
		for (int i = 0; i < m_closedList.size(); ++i)
		{
			if (m_closedList[i]->m_tilePosition == m_endPoint)
			{
				state = PATHSTATE::FINISHED;
				m_node = m_closedList[i];
				break;
			}
			state = PATHSTATE::FAILED;
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
//#ifdef PULLSTRING
			if (m_usingPullstring) PullString();
//#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (
			m_map->m_grid[pos.x][pos.y]->cost >= OBSTACLECOST || ((
				m_node->m_fCost + m_map->m_grid[pos.x][pos.y]->cost >
				m_map->m_grid[pos.x][pos.y]->m_fCost) &&
				m_map->FindTile(pos, TILETYPE::VISITED)))
		{
			return;
		}
		m_map->m_grid[pos.x][pos.y]->m_fCost = 
			m_map->m_grid[pos.x][pos.y]->cost + m_node->m_fCost;
		m_map->m_grid[pos.x][pos.y]->m_parent = m_node;
		if (m_map->FindTile(pos, TILETYPE::VISITED))return;
		m_map->m_grid[pos.x][pos.y]->Set(TILETYPE::VISITED);
		m_openList.push(m_map->m_grid[pos.x][pos.y]);
		//
		
	}
};

//BESTSEARCH ALGORITHM
class BestSearch : public PathFinder
{
private:
	//std::priority_queue<CostedTile*,std::vector<CostedTile*>,LessCost> m_openList;
	std::priority_queue<TileNode*, std::vector<TileNode*>, NodeComparator> m_openList;

public:
	//We need to override the < > operators to have the comparison for this thing
	BestSearch()
	{
	}
	BestSearch(bool pullstring, HEURISTIC h)
	{
		m_usingPullstring = pullstring;
		m_activeHeuristic = h;
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
		m_openList.push(&m_map->GetTile(m_startPoint));
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
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x)
				{
					CheckNode(temp);
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x < m_map->GetGridSize().x &&
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x >= 0 &&
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//WEST NODE
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x >= 0)
				{
					CheckNode(temp);
				}
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x >= 0 &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x < m_map->GetGridSize().x &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				state = PATHSTATE::SEARCHING;
			}
			else state = PATHSTATE::FAILED;
			Render(window);
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
//#ifdef PULLSTRING
			if (m_usingPullstring) PullString();
//#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{
		if (m_map->FindTile(pos, TILETYPE::OBSTACLE) || m_map->FindTile(pos, TILETYPE::VISITED))
		{
			return;
		}
		m_map->m_grid[pos.x][pos.y]->m_fCost =
			(int)XVEC2SqrSum(pos, m_endPoint);
		m_map->m_grid[pos.x][pos.y]->Set(TILETYPE::VISITED);
		m_map->m_grid[pos.x][pos.y]->m_parent = m_node;
		m_openList.push(m_map->m_grid[pos.x][pos.y]);
		//
	}
};
//A STAR ALGORITHM
class Astar : public PathFinder
{
private:
	std::priority_queue<TileNode*,std::vector<TileNode*>, NodeComparator> m_openList;
public:
	Astar()
	{

	}
	Astar(bool pullstring, HEURISTIC h)
	{
		m_usingPullstring = pullstring;
		m_activeHeuristic = h;
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
		m_openList.push(&m_map->GetTile(m_startPoint));
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
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x < m_map->GetGridSize().x)
				{
					CheckNode(temp);
				}
				//EAST SOUTH
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x < m_map->GetGridSize().x &&
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//SOUTH WEST
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y + 1;
				if (temp.x >= 0 &&
					temp.y < m_map->GetGridSize().y)
				{
					CheckNode(temp);
				}
				//WEST NODE
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y;
				if (temp.x >= 0)
				{
					CheckNode(temp);
				}
				//NORTH WEST
				temp.x = m_node->m_tilePosition.x - 1;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x >= 0 &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH NODE
				temp.x = m_node->m_tilePosition.x;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.y >= 0)
				{
					CheckNode(temp);
				}
				//NORTH EAST
				temp.x = m_node->m_tilePosition.x + 1;
				temp.y = m_node->m_tilePosition.y - 1;
				if (temp.x < m_map->GetGridSize().x &&
					temp.y >= 0)
				{
					CheckNode(temp);
				}
				state = PATHSTATE::SEARCHING;
			}
			else state = PATHSTATE::FAILED;
			Render(window);
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
//#ifdef PULLSTRING
			if (m_usingPullstring) PullString();
//#endif
		}
	}
	void CheckNode(const XVECTOR2 pos)
	{

		if (m_map->FindTile(pos, TILETYPE::OBSTACLE))
		{
			return;
		}
		int tmpcost = 0;
//#ifdef MANHATTAN
		if (m_activeHeuristic == HEURISTIC::H_MANHATTAN)
			tmpcost = ManhattanDistance(pos, m_endPoint);
//#endif
//#ifdef EUCLIDEAN
		else if (m_activeHeuristic == HEURISTIC::H_EUCLIDEAN)
			tmpcost = EuclideanDistance(pos, m_endPoint);
//#endif
//#ifdef SQUARESUM
		else if (m_activeHeuristic == HEURISTIC::H_SQUARESUM)
			tmpcost = XVEC2SqrSum(pos, m_endPoint);
//#endif
		tmpcost +=
			(m_map->m_grid[pos.x][pos.y]->cost + m_node->m_costsofar);
		if (m_map->FindTile(pos, TILETYPE::VISITED) && 
			tmpcost >= m_map->m_grid[pos.x][pos.y]->cost) return;
		m_map->m_grid[pos.x][pos.y]->m_fCost = tmpcost;
		m_map->m_grid[pos.x][pos.y]->m_costsofar = 
			(m_map->m_grid[pos.x][pos.y]->cost + m_node->m_costsofar);
		m_map->m_grid[pos.x][pos.y]->m_parent = m_node;
		if (m_map->FindTile(pos, TILETYPE::VISITED)) return;
		m_map->m_grid[pos.x][pos.y]->Set(TILETYPE::VISITED);
		m_openList.push(m_map->m_grid[pos.x][pos.y]);
	}
};