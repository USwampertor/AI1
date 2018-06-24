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
	m_pathfinder = nullptr;
	return true;
}
void Core::SFMLWINDOW()
{
	sf::RenderWindow window(sf::VideoMode(1000, 400), "AI 2018 B");
	window.setTitle("Pathfinder");
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			EventHandler(&window, event);

		}
		Draw(&window);
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
	}
	if (m_close)
	{
		window->close();
	}
}
void Core::KeyBoardEventHander(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		std::cout << "Changed to Breadth FS algorithm \n";
		m_selectedPathfinder.setString("BREADTH FIRST SEARCH");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		std::cout << "Changed to Depth FS algorithm \n";
		m_selectedPathfinder.setString("DEPTH FIRST SEARCH");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		std::cout << "Changed to Dijkstra algorithm \n";
		m_selectedPathfinder.setString("DIJKSTRA");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		std::cout << "Changed to Best FS algorithm \n";
		m_selectedPathfinder.setString("BEST FIRST SEARCH");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		std::cout << "Changed to A* algorithm \n";
		m_selectedPathfinder.setString("A STAR");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		std::cout << "Closing...\n";
		m_close = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (m_pathfinder == nullptr) m_selectedPathfinder.setString("CHOOSE AN ALGORITHM");
	}

}
void Core::MouseEventHandler(sf::Event event)
{
	if (event.mouseButton.x < 800 && event.mouseButton.x > 0)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			//std::cout << "nibba right \n";
			//std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
			m_gameMap.SetTile(m_gameMap.GetEnding(), TILETYPE::NONE);
			m_gameMap.SetEnding(XVECTOR2(
				event.mouseButton.x - event.mouseButton.x % 10,
				event.mouseButton.y - event.mouseButton.y % 10));
			m_gameMap.SetTile(m_gameMap.GetEnding(), TILETYPE::FINISH);
		}
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			//std::cout << "nibba left \n";
			//std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
			m_gameMap.SetTile(m_gameMap.GetBeggining(), TILETYPE::NONE);
			m_gameMap.SetBeggining(XVECTOR2(
				event.mouseButton.x - event.mouseButton.x % 10,
				event.mouseButton.y - event.mouseButton.y % 10));
			m_gameMap.SetTile(m_gameMap.GetBeggining(), TILETYPE::START);
		}
		if (event.mouseButton.button == sf::Mouse::Middle)
		{

			//std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
			if (!m_gameMap.FindTile(XVECTOR2(
				event.mouseButton.x - event.mouseButton.x % 10,
				event.mouseButton.y - event.mouseButton.y % 10), TILETYPE::OBSTACLE))
			{
				m_gameMap.SetTile(XVECTOR2(
					event.mouseButton.x - event.mouseButton.x % 10,
					event.mouseButton.y - event.mouseButton.y % 10), TILETYPE::OBSTACLE);
			}
			else
			{
				m_gameMap.SetTile(XVECTOR2(
					event.mouseButton.x - event.mouseButton.x % 10,
					event.mouseButton.y - event.mouseButton.y % 10), TILETYPE::NONE);
			}
			

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
	m_gameMap.Render(window);
}
