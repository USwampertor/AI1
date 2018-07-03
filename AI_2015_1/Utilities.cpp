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
std::string ReturnString(XVECTOR2 vec)
{
	std::string tmp;
	tmp = vec.x; tmp += " "; tmp += vec.y;
	return tmp;
}
