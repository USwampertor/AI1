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
	m_tile.setSize(sf::Vector2f(size,size));
	Set(TILETYPE::NONE);
	m_tile.setPosition(IDVtoSFML(m_tilePosition));
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
		m_tileColor = sf::Color::White;
		break;
	case START:
		m_tileColor = sf::Color::Red;
		break;
	case FINISH:
		m_tileColor = sf::Color::Blue;
		break;
	case OBSTACLE:
		m_tileColor = sf::Color::Green;
		break;
	case VISITED:
		m_tileColor = sf::Color::Yellow;
		break;
	case NOTVISITED:
		m_tileColor = sf::Color::Magenta;
		break;
	default:
		break;
	}
	m_tile.setFillColor(m_tileColor);
}
TILETYPE TileNode::Get()
{
	return m_tileType;
}