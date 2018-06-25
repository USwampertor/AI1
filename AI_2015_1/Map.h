#pragma once
#include "TileNode.h"
#include <list>
#include <vector>
class Map
{
private:
	typedef std::vector<std::vector<TileNode*>> MapGrid;
	XVECTOR2 m_gridSize;
	XVECTOR2 m_beggining, m_ending;
	std::list<XVECTOR2> m_obstacles;
public:
	MapGrid m_grid;
	Map();
	Map(const Map& copy);
	Map(int gridwidth, int gridheight);
	~Map();
	void Initialize(int gridwidth, int gridheight);
	void SetBeggining(XVECTOR2 position);
	void SetEnding(XVECTOR2 position);
	void AddObstacle(XVECTOR2 position);
	bool DeleteObstacle(XVECTOR2 position);
	bool FindObstacle(XVECTOR2 position);
	std::list<XVECTOR2> GetObstacleList();
	XVECTOR2 GetEnding();
	XVECTOR2 GetBeggining();
	XVECTOR2 GetGridSize();
	void SetTile(XVECTOR2 vec, TILETYPE type);
	bool FindTile(XVECTOR2 vec, TILETYPE type);
	void Render(sf::RenderWindow* window);
	TileNode GetTile(XVECTOR2 pos);
};

