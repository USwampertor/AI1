//GLOBAL SHIT ITD BE KINDA HORRIBLE TO BE DECLARING AT EACH FUCKING CLASS
#pragma once
#include <IDVMath.h>
#include <string>
#include <SFML/Graphics.hpp>
#define TILESIZE 10
sf::Vector2f IDVtoSFML(XVECTOR2 idvvector);
XVECTOR2 SFMLtoIDV(sf::Vector2f sfmlvector);
XVECTOR2 GridtoPixel(XVECTOR2 vec);
XVECTOR2 PixeltoGrid(XVECTOR2 vec);
std::string ReturnString(XVECTOR2 vec);

