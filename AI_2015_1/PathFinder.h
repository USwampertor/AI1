#pragma once
#include <IDVMath.h>
#include <queue>
#include "Map.h"
//BASE FOR PATHFINDING ALGORITHMS
class PathFinder
{
private:
	XVECTOR2 m_startPoint, m_endPoint;
	Map* m_map;
public:
	PathFinder()
	{

	}
	~PathFinder()
	{

	}
	void GetStartingPoint(XVECTOR2 start)
	{
		m_startPoint = start;
	}
	void GetEndingPoint(XVECTOR2 finish)
	{
		m_endPoint = finish;
	}
	virtual void Search() = 0;
};
class BFS : public PathFinder
{
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
	std::priority_queue<TileNode> m_openList;
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