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
XVECTOR2 GridtoPixel(XVECTOR2 vec)
{
	XVECTOR2 tmp = vec;
	return tmp * TILESIZE;
}
XVECTOR2 PixeltoGrid(XVECTOR2 vec)
{
	XVECTOR2 tmp;
	tmp.x = (((int)vec.x - (int)vec.x % TILESIZE)/TILESIZE);
	tmp.y = (((int)vec.y - (int)vec.y % TILESIZE)/TILESIZE);
	return tmp;
}
int GtoP(int tile)
{
	return tile * TILESIZE;
}
int PtoG(int pixel)
{
	return (((int)pixel - (int)pixel % TILESIZE) / TILESIZE);
}
sf::String ReturnString(XVECTOR2 vec)
{
	sf::String tmp = (std::to_string((int)vec.x) + ", " + std::to_string((int)vec.y));
	return tmp;
}
int ManhattanDistance(XVECTOR2 start, XVECTOR2 finish)
{
	return (std::abs(finish.x - start.x) + std::abs(finish.y - start.y));
}
float EuclideanDistance(XVECTOR2 start, XVECTOR2 finish)
{
	return std::sqrt(
		((finish.x - start.x)*(finish.x - start.x) + 
		(finish.y - start.y)*(finish.y - start.y)));
}
void DelaunayTriangulation(std::vector<XVECTOR2> sortedPoints)
{

}
void SortPoints(std::vector<XVECTOR2> unsortedPoints)
{
	std::priority_queue<XVECTOR2, std::vector<XVECTOR2>, VectorComparator> sortedqueue;
	for (int i = 0; i < unsortedPoints.size(); ++i)
	{
		sortedqueue.push(unsortedPoints[i]);
	}
	unsortedPoints.clear();
	for (int i = 0; !sortedqueue.empty(); ++i)
	{
		unsortedPoints[i] = sortedqueue.top();
		sortedqueue.pop();
	}

}
std::vector<XVECTOR2> GenerateRandomPoints(int radius, int seed, int maxPoints)
{
	
	std::vector<XVECTOR2> randompoints;
	srand(seed);
	float angle, randomRadius, x, y;
	int totalpoints = rand() % maxPoints;
	totalpoints = maxPoints;
	for (int i = 0; i < totalpoints; ++i)
	{
		//float randominterval = (float)rand() / (float)maxPoints;
		//angle = randominterval * 2.0f * PI;
		//randomRadius = radius * sqrt(randominterval);
		randomRadius = (rand() % radius);
		angle = (((float)rand()) / (float)RAND_MAX);
		angle *= (2.0f*PI);
		std::cout << angle << std::endl;
		x = randomRadius * cos(angle);
		y = randomRadius * sin(angle);
		randompoints.push_back(XVECTOR2(x, y));
		std::cout << x << " " << y << std::endl;
	}
	return randompoints;
}