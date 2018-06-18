#pragma once
#include "IDVMath.h"
#include <list>
#include "Utilities.h"
class Map
{
private:
	int** m_grid;
	XVECTOR2 m_gridSize;
	XVECTOR2 m_beggining, m_ending;
	std::list<XVECTOR2> m_obstacles;
public:
	Map();
	~Map();
	void Initialize(int gridwidth, int gridheight);
	void SetBeggining(XVECTOR2 position);
	void SetEnding(XVECTOR2 position);
	void AddObstacle(XVECTOR2 position);
	bool DeleteObstacle(XVECTOR2 position);
	bool FindObstacle(XVECTOR2 position);
	std::list<XVECTOR2> GetObstacleList();
	XVECTOR2 GetBeggining();
	XVECTOR2 GetEnding();
};

