#include "stdafx.h"
#include "Core.h"

Core::Core()
{
	
}


Core::~Core()
{
}

bool Core::Initialize()
{
	//Initialize window and resources we gonna need for the program
	m_gameMap.Initialize(800, 400);
	if (!m_font.loadFromFile("PGB.ttf"))
	{
		return false;
	}
	m_selectedPathfinder.setFont(m_font);
	m_selectedPathfinder.setCharacterSize(8);
	m_selectedPathfinder.setFillColor(sf::Color::Black);
	m_selectedPathfinder.setPosition(sf::Vector2f(820, 20));
	m_selectedPathfinder.setString("Not using any \n algorithm");
	m_startingPoint.setFont(m_font);
	m_startingPoint.setCharacterSize(8);
	m_startingPoint.setFillColor(sf::Color::Black);
	m_startingPoint.setPosition(sf::Vector2f(850, 40));
	m_startingPoint.setString("START"); 
	m_endingPoint.setFont(m_font);
	m_endingPoint.setCharacterSize(8);
	m_endingPoint.setFillColor(sf::Color::Black);
	m_endingPoint.setPosition(sf::Vector2f(850, 60));
	m_endingPoint.setString("FINISH");
	m_heuristicText.setFont(m_font);
	m_heuristicText.setCharacterSize(8);
	m_heuristicText.setFillColor(sf::Color::Black);
	m_heuristicText.setPosition(sf::Vector2f(850, 80));
	m_heuristicText.setString("MANHATTAN");
	m_pullstringText.setFont(m_font);
	m_pullstringText.setCharacterSize(8);
	m_pullstringText.setFillColor(sf::Color::Black);
	m_pullstringText.setPosition(sf::Vector2f(850, 100));
	m_pullstringText.setString("PULLSTRING");
	m_startRectangle.setSize(sf::Vector2f(TILESIZE, TILESIZE));
	m_startRectangle.setFillColor(sf::Color::Red);
	m_startRectangle.setPosition(sf::Vector2f(820, 40));
	m_endingRectangle.setSize(sf::Vector2f(TILESIZE, TILESIZE));
	m_endingRectangle.setFillColor(sf::Color::Blue);
	m_endingRectangle.setPosition(sf::Vector2f(820, 60));
	m_heuristicRectangle.setSize(sf::Vector2f(TILESIZE, TILESIZE));
	m_heuristicRectangle.setFillColor(sf::Color::Cyan);
	m_heuristicRectangle.setPosition(sf::Vector2f(820, 80));
	m_pullstringRectangle.setSize(sf::Vector2f(TILESIZE, TILESIZE));
	m_pullstringRectangle.setFillColor(sf::Color::Black);
	m_pullstringRectangle.setPosition(sf::Vector2f(820, 100));
	
	
	m_pathfinder = nullptr;
	
	//GenerateAgents();
	m_dungeonGenerator.SetMapBoundaries(800, 400);
	return true;
}
void Core::SFMLWINDOW()
{
	sf::RenderWindow window(sf::VideoMode(1000.0f, 400.0f), "AI 2018 B");
	m_cameraView = { sf::Vector2f(400.0f,200.0f) ,sf::Vector2f(1000.0f,400.0f) };
	window.setTitle("Pathfinder");
	m_dungeonGenerator.SetWindow(&window);
	bool generated = false;
	while (window.isOpen())
	{
		if (!generated)
		{
			m_dungeonGenerator.GenerateDungeon(RANDOMSEED, 1, 2, 10, 8, 100, 150, 4, 5, 6, 6);
			generated = true;
		}
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			EventHandler(&window, event);
		}
		if(m_searching==1)SearchnDestroy(&window);
		//UpdateAgents();
		window.setView(m_cameraView);
		Draw(&window);
		//m_cameraView.rotate(5);
		window.display();
	}
}
void Core::EventHandler(sf::RenderWindow* window, sf::Event event)
{
	
	switch (event.type)
	{
	case sf::Event::Closed:
			window->close();
			break;
	case sf::Event::KeyPressed:
		KeyBoardEventHander(event);
		break;
	case sf::Event::Resized:
		window->setSize(sf::Vector2u(1000, 400));
		break;
	case sf::Event::MouseButtonPressed:
		MouseEventHandler(event);
		break;
	case sf::Event::MouseWheelScrolled:
		MouseScrolled(event);
		break;
	}
	if (m_close)
	{
		window->close();
	}
}
void Core::MouseScrolled(sf::Event event)
{
	if (event.mouseWheelScroll.delta < 0.0f)
	{
		m_cameraView.zoom(0.9f);
	}
	if (event.mouseWheelScroll.delta > 0.0f)
	{
		m_cameraView.zoom(1.1f);
	}
}
void Core::KeyBoardEventHander(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//m_cameraView.setCenter(m_cameraView.getCenter());
		m_cameraView.move(0.0f, 10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_cameraView.move(-10.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_cameraView.move(0.0f, -10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_cameraView.move(10.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		std::cout << "Changed to Breadth FS algorithm \n";
		m_selectedPathfinder.setString("BREADTH FIRST SEARCH");
		m_pathfindertype = 1;
		if (!SetPathfinder()) m_selectedPathfinder.setString("FAILED TO SET PATHFINDER!!!");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		std::cout << "Changed to Depth FS algorithm \n";
		m_selectedPathfinder.setString("DEPTH FIRST SEARCH");
		m_pathfindertype = 2;
		if (!SetPathfinder()) m_selectedPathfinder.setString("FAILED TO SET PATHFINDER!!!");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		std::cout << "Changed to Dijkstra algorithm \n";
		m_selectedPathfinder.setString("DIJKSTRA");
		m_pathfindertype = 3;
		if (!SetPathfinder()) m_selectedPathfinder.setString("FAILED TO SET PATHFINDER!!!");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		std::cout << "Changed to Best FS algorithm \n";
		m_selectedPathfinder.setString("BEST FIRST SEARCH");
		m_pathfindertype = 4;
		if (!SetPathfinder()) m_selectedPathfinder.setString("FAILED TO SET PATHFINDER!!!");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		std::cout << "Changed to A* algorithm \n";
		m_selectedPathfinder.setString("A STAR");
		m_pathfindertype = 5;
		if(!SetPathfinder()) m_selectedPathfinder.setString("FAILED TO SET PATHFINDER!!!");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		std::cout << "Closing...\n";
		m_close = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (m_pathfinder == nullptr) m_selectedPathfinder.setString("CHOOSE AN ALGORITHM");
		else
		{
			m_selectedPathfinder.setString("Starting...");
			/*if (InitPathfinder());*/ m_searching = 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		m_heuristic = HEURISTIC::H_EUCLIDEAN;
		if (m_pathfinder != nullptr) m_pathfinder->m_activeHeuristic = m_heuristic;
		m_heuristicText.setString("EUCLIDEAN");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		m_heuristic = HEURISTIC::H_MANHATTAN;
		if (m_pathfinder != nullptr) m_pathfinder->m_activeHeuristic = m_heuristic;
		m_heuristicText.setString("MANHATTAN");

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		m_heuristic = HEURISTIC::H_SQUARESUM;
		if (m_pathfinder != nullptr) m_pathfinder->m_activeHeuristic = m_heuristic;
		m_heuristicText.setString("SQUARE SUM");

	}
}
void Core::MouseEventHandler(sf::Event event)
{
	if (event.mouseButton.x < 800 && event.mouseButton.x > 0)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			//std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
			m_gameMap.SetTile(m_gameMap.GetEnding(), TILETYPE::NONE);
			m_gameMap.SetEnding(
				PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y)));
			m_gameMap.SetTile(m_gameMap.GetEnding(), TILETYPE::FINISH);
			m_endingPoint.setString(
				ReturnString(PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y))));
		}
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			//std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
			m_gameMap.SetTile(m_gameMap.GetBeggining(), TILETYPE::NONE);
			m_gameMap.SetBeggining(
				PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y)));
			m_gameMap.SetTile(m_gameMap.GetBeggining(), TILETYPE::START);
			m_startingPoint.setString(
				ReturnString(PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y))));
		}
		if (event.mouseButton.button == sf::Mouse::Middle)
		{

			//std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
			if (!m_gameMap.FindTile(
				PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y)), 
				TILETYPE::OBSTACLE))
			{
				m_gameMap.SetTile(
					PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y)), 
					TILETYPE::OBSTACLE);
			}
			else
			{
				m_gameMap.SetTile(
					PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y)),
					TILETYPE::NONE);
			}
			

		}
	}
	else if (PixeltoGrid(XVECTOR2(event.mouseButton.x, event.mouseButton.y))*TILESIZE==XVECTOR2(820,100))
	{
		if (!m_pullstring)
		{
			m_pullstringRectangle.setFillColor(sf::Color::Green);
			m_pullstring = true;
			if (m_pathfinder != nullptr) m_pathfinder->m_usingPullstring = true;
		}
		else
		{
			m_pullstringRectangle.setFillColor(sf::Color::Black);
			m_pullstring = false;
			if (m_pathfinder != nullptr) m_pathfinder->m_usingPullstring = false;
		}
	}
}
void Core::Draw(sf::RenderWindow* window)
{
	sf::RectangleShape uirectangle(sf::Vector2f(200, 400));
	uirectangle.setFillColor(sf::Color(150,150,150));
	uirectangle.setPosition(sf::Vector2f(800, 0));
	window->draw(uirectangle);
	window->draw(m_selectedPathfinder);
	window->draw(m_startingPoint);
	window->draw(m_endingPoint);
	window->draw(m_heuristicText);
	window->draw(m_pullstringText);
	window->draw(m_startRectangle);
	window->draw(m_endingRectangle);
	window->draw(m_heuristicRectangle);
	window->draw(m_pullstringRectangle);
	
	//sf::RectangleShape beggining(sf::Vector2f(10, 10));
	//beggining.setPosition(IDVtoSFML(m_gameMap.GetBeggining()));
	//beggining.setFillColor(sf::Color::Blue);
	//window->draw(beggining);
	//
	//sf::RectangleShape ending(sf::Vector2f(10, 10));
	//ending.setPosition(IDVtoSFML(m_gameMap.GetEnding()));
	//ending.setFillColor(sf::Color::Red);
	//window->draw(ending);
	//
	//std::list<XVECTOR2> obstacles = m_gameMap.GetObstacleList();
	//for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	//{
	//	sf::RectangleShape obstacle(sf::Vector2f(10, 10));
	//	obstacle.setPosition(IDVtoSFML(*it));
	//	obstacle.setFillColor(sf::Color::White);
	//	window->draw(obstacle);
	//}

	//m_gameMap.Render(window);
	if (m_searching == 2) 
	{ m_pathfinder->RenderPath(window); m_pathfinder->RenderLines(window); 
	};
	for (int i = 0; i < m_totalAgents.size(); ++i)
	{
		window->draw(m_totalAgents[i].m_body);
	}
	m_dungeonGenerator.Render(window);
}
bool Core::SetPathfinder()
{
	if (m_pathfindertype != -1)
	{
		delete m_pathfinder;
		switch (m_pathfindertype)
		{
		case 1:
			m_pathfinder = new BFS(m_pullstring, m_heuristic);
			break;
		case 2:
			m_pathfinder = new DFS(m_pullstring, m_heuristic);
			break;
		case 3:
			m_pathfinder = new Dijkstra(m_pullstring, m_heuristic);
			break;
		case 4:
			m_pathfinder = new BestSearch(m_pullstring, m_heuristic);
			break;
		case 5:
			m_pathfinder = new Astar(m_pullstring, m_heuristic);
			break;
		default:
			m_selectedPathfinder.setString("Don't really know \n how you got here");
			return false;
			break;
		}
		if (m_pathfinder == nullptr) return false;
	}
	return true;
		
}
bool Core::InitPathfinder()
{
	if (!(m_pathfinder->Initialize(m_gameMap)))
	{
		m_selectedPathfinder.setString("FAILED TO INITIALIZE PATHFINDER");
		return false;
	}
	else
		m_selectedPathfinder.setString("--SEARCHING--");
	return true;
}
void Core::SearchnDestroy(sf::RenderWindow* window)
{
	if (!InitPathfinder())
	{
		return;
	}
	m_pathfinder->Search(window);
	m_selectedPathfinder.setString("--FINAL--");
	m_searching = 2;
}
void Core::GenerateAgents()
{
	Boid2D objective = { "objective",400,200,AGENTICIRCLE,AGENTOCIRCLE,0.0f };
	for (int i = 0; i < DEBUGAGENTS; ++i)
	{
		char a[4] ; _itoa_s(i,a,10 );
		Boid2D agent = { a ,20.0f * i,10.0f,AGENTICIRCLE,AGENTOCIRCLE,1.0f };
		agent.m_EnemyPosition = objective.m_position2d;
		m_totalAgents.push_back(agent);
	}
}
void Core::UpdateAgents()
{
	for (int i = 0; i < m_totalAgents.size(); ++i)
	{
		m_totalAgents[i].Update();
		//std::cout 
		//	<< "Agent " << i << " " << 
		//	m_totalAgents[i].m_position2d.x << " " << 
		//	m_totalAgents[i].m_position2d.y << std::endl;
	}
}
