#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <IDVMath.h>
#include "Map.h"
class Core
{
private:
	sf::Font m_font;
	Map m_gameMap;
public:
	Core();
	~Core();
	bool Initialize();
	void SFMLWINDOW();
	void EventHandler(sf::RenderWindow* window, sf::Event event);
	void KeyBoardEventHander(sf::Event event);
	void MouseEventHandler(sf::RenderWindow& window, sf::Event event);
	void Draw(sf::RenderWindow* window);
	sf::Vector2f VEC2toVec2f(XVECTOR2 idvvector);
	XVECTOR2 Vec2ftoVEC2(sf::Vector2f sfmlvector);
};

