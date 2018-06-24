#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathFinder.h"
class Core
{
private:
	sf::Font m_font;
	sf::Text m_selectedPathfinder;
	Map m_gameMap;
	PathFinder* m_pathfinder;
	bool m_close = false;
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

