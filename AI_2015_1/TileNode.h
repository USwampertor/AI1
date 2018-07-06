#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
enum TILETYPE
{
	NONE=0,
	START,
	FINISH,
	OBSTACLE,
	VISITED,
	NOTVISITED,
	FINALPATH
};
class TileNode
{
public:
	TileNode(XVECTOR2 position, int size);
	TileNode();
	~TileNode();
	TILETYPE Get();
	void Set(TILETYPE type);
	int cost = 0;
	int m_costsofar = 0;
	int m_fCost = 0;
	XVECTOR2 m_tilePosition;
	sf::RectangleShape m_tile;
	int m_tileSize;
	sf::Color m_tileColor;
	TILETYPE m_tileType;
	TileNode* m_parent;
	bool operator < (const TileNode& ct1) const;
	bool operator > (const TileNode& ct1) const;
};
class CostedTile : public TileNode
{
public:
	CostedTile();
	~CostedTile();
	void SetInfo(TileNode* t);
	int m_cost;
	int GetCost(XVECTOR2 finishingpoint)
	{
		return XVEC2Dot(m_tilePosition, finishingpoint);
	}
	
};
