#include "stdafx.h"
#include "TileNode.h"

TileNode::TileNode()
{
	m_tilePosition = { 0,0 };
	m_parent = nullptr;
}
TileNode::TileNode(XVECTOR2 position, int size)
{
	m_tilePosition = position;
	m_tileSize = size;
	m_tile.setSize(sf::Vector2f(size,size));
	Set(TILETYPE::NONE);
	//XVECTOR2 pos = position * m_tileSize;
	m_tile.setPosition(IDVtoSFML(m_tilePosition));
	m_parent = nullptr;
}
TileNode::~TileNode()
{
}
void TileNode::Set(TILETYPE type)
{
	m_tileType = type;
	switch (type)
	{
	case NONE:
		m_tileColor = sf::Color::Transparent;
		cost = 1;
		break;
	case START:
		m_tileColor = sf::Color::Red;
		cost = 0;
		break;
	case FINISH:
		m_tileColor = sf::Color::Blue;
		cost = 0;
		break;
	case OBSTACLE:
		m_tileColor = sf::Color::Green;
		cost = OBSTACLECOST;
		break;
	case VISITED:
		m_tileColor = sf::Color::Yellow;
		break;
	case NOTVISITED:
		m_tileColor = sf::Color::Magenta;
		break;
	case FINALPATH:
		m_tileColor = sf::Color::Cyan;
	default:
		break;
	}
	m_tile.setFillColor(m_tileColor);
}
TILETYPE TileNode::Get()
{
	return m_tileType;
}
CostedTile::CostedTile()
{
}
CostedTile::~CostedTile()
{

}
void CostedTile::SetInfo(TileNode* t)
{
	m_tilePosition = t->m_tilePosition;
	m_tile = t->m_tile;
	m_tileSize = t->m_tileSize;
	m_tileColor = t->m_tileColor;
	m_tileType = t->m_tileType;
	m_parent = nullptr;
}
bool TileNode::operator < (const TileNode& ct1) const
{
	return m_fCost > ct1.m_fCost;
}
