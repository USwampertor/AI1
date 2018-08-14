#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathFinder.h"
#include "Boid.h"
#include <cstdlib>
#include "DungeonGenerator.h"
class Core
{
private:
	DungeonGenerator m_dungeonGenerator;
	sf::View m_cameraView;
	sf::Font m_font;
	sf::Text m_selectedPathfinder, m_startingPoint, m_endingPoint,m_heuristicText,m_pullstringText;
	sf::RectangleShape m_startRectangle, m_endingRectangle,m_heuristicRectangle,m_pullstringRectangle;
	Map m_gameMap;
	PathFinder* m_pathfinder;
	int m_pathfindertype = -1, m_searching = 0;
	bool m_close = false;
	bool m_pullstring = false;
	HEURISTIC m_heuristic=HEURISTIC::H_MANHATTAN;
	std::vector<Boid2D> m_totalAgents;
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
	void GenerateAgents();
	void UpdateAgents();
	void MouseScrolled(sf::Event event);
	//MOVED THEM TO UTILITIES
};

