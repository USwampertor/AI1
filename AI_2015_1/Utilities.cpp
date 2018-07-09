#include "stdafx.h"
#include "Utilities.h"
sf::Vector2f IDVtoSFML(XVECTOR2 idvvector)
{
	return sf::Vector2f(idvvector.x, idvvector.y);
}
XVECTOR2 SFMLtoIDV(sf::Vector2f sfmlvector)
{
	return XVECTOR2(sfmlvector.x, sfmlvector.y);
}
XVECTOR2 GridtoPixel(XVECTOR2 vec)
{
	XVECTOR2 tmp = vec;
	return tmp * TILESIZE;
}
XVECTOR2 PixeltoGrid(XVECTOR2 vec)
{
	XVECTOR2 tmp;
	tmp.x = (((int)vec.x - (int)vec.x % TILESIZE)/TILESIZE);
	tmp.y = (((int)vec.y - (int)vec.y % TILESIZE)/TILESIZE);
	return tmp;
}
sf::String ReturnString(XVECTOR2 vec)
{
	sf::String tmp = (std::to_string((int)vec.x) + ", " + std::to_string((int)vec.y));
	return tmp;
}
int ManhattanDistance(XVECTOR2 start, XVECTOR2 finish)
{
	return (std::abs(finish.x - start.x) + std::abs(finish.y - start.y));
}
float EuclideanDistance(XVECTOR2 start, XVECTOR2 finish)
{
	return std::sqrt(
		((finish.x - start.x)*(finish.x - start.x) + 
		(finish.y - start.y)*(finish.y - start.y)));
}