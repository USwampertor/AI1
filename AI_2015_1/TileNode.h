#pragma once
#include <IDVMath.h>
#include <SFML/Graphics.hpp>
#include "Utilities.h"
class TileNode
{
public:
	Utilities tool;
	XVECTOR2 m_tilePosition;
	sf::RectangleShape m_tile;
	int m_tileSize;
	sf::Color m_tileColor;
	TileNode(XVECTOR2 position, int size);
	TileNode();
	~TileNode();
};

