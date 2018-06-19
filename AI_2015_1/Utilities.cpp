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