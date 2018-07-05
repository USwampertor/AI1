//GLOBAL SHIT ITD BE KINDA HORRIBLE TO BE DECLARING AT EACH FUCKING CLASS
#pragma once
#include <IDVMath.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <math.h>
#define TILESIZE 10
#define OBSTACLECOST 9999999
sf::Vector2f IDVtoSFML(XVECTOR2 idvvector);
XVECTOR2 SFMLtoIDV(sf::Vector2f sfmlvector);
XVECTOR2 GridtoPixel(XVECTOR2 vec);
XVECTOR2 PixeltoGrid(XVECTOR2 vec);
sf::String ReturnString(XVECTOR2 vec);
int ManhattanDistance(XVECTOR2 start, XVECTOR2 finish);
float EuclideanDistance(XVECTOR2 start, XVECTOR2 finish);
