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
	m_gameMap.Initialize(600, 400);
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
		MouseEventHandler(*window, event);
		break;
	}
}
void Core::KeyBoardEventHander(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		std::cout << "Changed to Breadth FS algorithm \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		std::cout << "Changed to Depth FS algorithm \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		std::cout << "Changed to Dijkstra algorithm \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		std::cout << "Changed to Best FS algorithm \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		std::cout << "Changed to A* algorithm \n";
	}
}
void Core::MouseEventHandler(sf::RenderWindow& window, sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		//std::cout << "nibba right \n";
		std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
		m_gameMap.SetEnding(XVECTOR2(
			event.mouseButton.x - event.mouseButton.x % 10,
			event.mouseButton.y - event.mouseButton.y % 10));
	}
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		//std::cout << "nibba left \n";
		std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
		m_gameMap.SetBeggining(XVECTOR2(
			event.mouseButton.x - event.mouseButton.x%10,
			event.mouseButton.y- event.mouseButton.y%10));
	}
	if (event.mouseButton.button == sf::Mouse::XButton2)
	{
		std::cout << event.mouseButton.x << " " << event.mouseButton.y << "\n";
		if (!m_gameMap.FindObstacle(XVECTOR2(
			event.mouseButton.x - event.mouseButton.x % 10,
			event.mouseButton.y - event.mouseButton.y % 10)))
		{
			m_gameMap.AddObstacle(XVECTOR2(
				event.mouseButton.x - event.mouseButton.x % 10,
				event.mouseButton.y - event.mouseButton.y % 10));
		}
		else
		{
			m_gameMap.DeleteObstacle(XVECTOR2(
				event.mouseButton.x - event.mouseButton.x % 10,
				event.mouseButton.y - event.mouseButton.y % 10));
		}
	}
}
void Core::Draw(sf::RenderWindow* window)
{
	sf::RectangleShape uirectangle(sf::Vector2f(200, 400));
	uirectangle.setFillColor(sf::Color::White);
	uirectangle.setPosition(sf::Vector2f(800, 0));
	window->draw(uirectangle);

	sf::RectangleShape beggining(sf::Vector2f(10, 10));
	beggining.setPosition(m_tool.VEC2toVec2f(m_gameMap.GetBeggining()));
	beggining.setFillColor(sf::Color::Blue);
	window->draw(beggining);

	sf::RectangleShape ending(sf::Vector2f(10, 10));
	ending.setPosition(m_tool.VEC2toVec2f(m_gameMap.GetEnding()));
	ending.setFillColor(sf::Color::Red);
	window->draw(ending);

	std::list<XVECTOR2> obstacles = m_gameMap.GetObstacleList();
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		sf::RectangleShape obstacle(sf::Vector2f(10, 10));
		obstacle.setPosition(VEC2toVec2f(*it));
		obstacle.setFillColor(sf::Color::White);
		window->draw(obstacle);
	}
}

