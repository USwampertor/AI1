#pragma once
#include "IDVMath.h"
#include <vector>
class Map
{
private:
	int* m_grid;
	
	XVECTOR2 m_beggining, m_ending;
	std::vector<XVECTOR2> m_obstacles;
public:
	Map();
	~Map();
	void Initialize(int gridwidth, int gridheight);
	void SetBeggining(XVECTOR2 position);
	void SetEnding(XVECTOR2 position);
	XVECTOR2 GetBeggining();
	XVECTOR2 GetEnding();
};

