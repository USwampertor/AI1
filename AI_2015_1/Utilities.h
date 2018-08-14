//GLOBAL SHIT ITD BE KINDA HORRIBLE TO BE DECLARING AT EACH FUCKING CLASS
#pragma once
#include <IDVMath.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <queue>
#include <time.h>

#define DEBUGAGENTS 10
#define AGENTICIRCLE 7.0f
#define AGENTOCIRCLE 9.0f
#define AGENTSIZE 5.0f


#define TILESIZE 5
#define OBSTACLECOST 9999999
#define PI 3.14159
#define MAXPOINTS 50
#define RANDOMSEED 30091997
struct VectorComparator : public std::binary_function<XVECTOR2, XVECTOR2, bool>
{
	bool operator()(const XVECTOR2 left, const XVECTOR2 right) const
	{
		if (left.x > right.x)
			return left.x > right.x;
		else return left.y > right.y;
	}
};

sf::Vector2f IDVtoSFML(XVECTOR2 idvvector);
XVECTOR2 SFMLtoIDV(sf::Vector2f sfmlvector);
XVECTOR2 GridtoPixel(XVECTOR2 vec);
XVECTOR2 PixeltoGrid(XVECTOR2 vec);
int GtoP(int tile);
int PtoG(int pixel);
sf::String ReturnString(XVECTOR2 vec);
int ManhattanDistance(XVECTOR2 start, XVECTOR2 finish);
float EuclideanDistance(XVECTOR2 start, XVECTOR2 finish);
void DelaunayTriangulation(std::vector<XVECTOR2> sortedPoints);
void SortPoints(std::vector<XVECTOR2> unsortedPoints);
std::vector<XVECTOR2> GenerateRandomPoints(int radius, int seed, int maxPoints);