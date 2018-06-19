#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
enum TILETYPE
{
	NONE=0,
	START,
	FINISH,
	OBSTACLE,
	OPEN,
	CLOSED
};
class TileNode
{
public:
	XVECTOR2 m_tilePosition;
	sf::RectangleShape m_tile;
	int m_tileSize;
	sf::Color m_tileColor;
	TILETYPE m_tileType;
	TileNode(XVECTOR2 position, int size);
	void Set(TILETYPE type);
	TILETYPE Get();
	TileNode();
	~TileNode();
};

