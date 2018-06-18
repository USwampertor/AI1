#include "stdafx.h"
#include "TileNode.h"

TileNode::TileNode()
{
	m_tilePosition = { 0,0 };
}
TileNode::TileNode(XVECTOR2 position, int size)
{
	m_tilePosition = position;
	m_tileSize = size;
	m_tileColor = sf::Color::White;
	m_tile.setPosition(tool.VEC2toVec2f(m_tilePosition));

}
TileNode::~TileNode()
{
}
