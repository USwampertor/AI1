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
	NOTVISITED
};
class TileNode
{
public:
	TileNode(XVECTOR2 position, int size);
	TileNode();
	~TileNode();
	TILETYPE Get();
	void Set(TILETYPE type);
	
	XVECTOR2 m_tilePosition;
	sf::RectangleShape m_tile;
	int m_tileSize;
	sf::Color m_tileColor;
	TILETYPE m_tileType;
	TileNode* m_parent;
};
class CostedTile : public TileNode
{
public:
	int cost;
	int GetCost()
	{
		return 0;
	}
};
