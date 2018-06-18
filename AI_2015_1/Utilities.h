//GLOBAL SHIT ITD BE KINDA HORRIBLE TO BE DECLARING AT EACH FUCKING CLASS
#pragma once
#include <IDVMath.h>
#include <SFML/Graphics.hpp>
#define TILESIZE 10
class Utilities
{
public:
	Utilities()
	{

	}
	~Utilities()
	{

	}
	const sf::Vector2f VEC2toVec2f(XVECTOR2 idvvector)
	{
		return sf::Vector2f(idvvector.x, idvvector.y);
	}
	const XVECTOR2 Vec2ftoVEC2(sf::Vector2f sfmlvector)
	{
		return XVECTOR2(sfmlvector.x, sfmlvector.y);
	}
};

