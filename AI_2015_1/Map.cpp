#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	
}
Map::~Map()
{
	
	delete m_grid;
}
void Map::Initialize(int gridwidth, int gridheight)
{
	m_grid = new int[gridheight*gridwidth];
	
}
void Map::SetBeggining(XVECTOR2 position)
{
	m_beggining = position;
}
XVECTOR2 Map::GetBeggining()
{
	return m_beggining;
}
void Map::SetEnding(XVECTOR2 position)
{
	m_ending = position;
}
XVECTOR2 Map::GetEnding()
{
	return m_ending;
}

