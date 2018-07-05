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
	tmp.x += 1.0f; tmp.y += 1.0f;
	return tmp * TILESIZE;
}
XVECTOR2 PixeltoGrid(XVECTOR2 vec)
{
	XVECTOR2 tmp = vec;
	tmp.x = tmp.x - (int)tmp.x % TILESIZE;
	tmp.y = tmp.y - (int)tmp.y % TILESIZE;
	return tmp;
}
sf::String ReturnString(XVECTOR2 vec)
{
	//sf::String x = std::to_string((int)vec.x);	
	//sf::String y = std::to_string((int)vec.y);
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