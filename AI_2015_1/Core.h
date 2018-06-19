#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
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
	void MouseEventHandler(sf::Event event);
	void Draw(sf::RenderWindow* window);
	//MOVED THEM TO UTILITIES
};

