/*///////////////////////////
|	Artificial Intelligence	|
|	UAD 6th QUAD			|
|	For educational purposes|
///////////////////////////*/
#include "stdafx.h"
#include "Core.h"
#include <iostream>

int main()
{
	std::cout << "Loading...\n";
	Core game;
	if (!game.Initialize())
	{
		std::cout << "Failed to Initialize window... \n Closing program... \n";
		return 0;
	}
	game.SFMLWINDOW();
    return 0;
}
