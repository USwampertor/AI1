#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathFinder.h"
class Core
{
private:
	sf::Font m_font;
	sf::Text m_selectedPathfinder, m_startingPoint, m_endingPoint,m_heuristicText,m_pullstringText;
	sf::RectangleShape m_startRectangle, m_endingRectangle,m_heuristicRectangle,m_pullstringRectangle;
	Map m_gameMap;
	PathFinder* m_pathfinder;
	int m_pathfindertype = -1, m_searching = 0;
	bool m_close = false;
	bool m_pullstring = false;
	HEURISTIC m_heuristic=HEURISTIC::H_MANHATTAN;
public:
	Core();
	~Core();
	bool Initialize();
	void SFMLWINDOW();
	void EventHandler(sf::RenderWindow* window, sf::Event event);
	void KeyBoardEventHander(sf::Event event);
	void MouseEventHandler(sf::Event event);
	void Draw(sf::RenderWindow* window);
	bool SetPathfinder();
	bool InitPathfinder();
	void SearchnDestroy(sf::RenderWindow* window);
	//MOVED THEM TO UTILITIES
};

