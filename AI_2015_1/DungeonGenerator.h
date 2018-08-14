#pragma once
#include "DungeonRoom.h"
class DungeonGenerator
{
private:
	std::vector<DungeonRoom> m_Rooms;
	XVECTOR2 m_MapSize;
public:
	DungeonGenerator();
	~DungeonGenerator();
	void SeparateRooms();
	void GenerateRooms(std::vector<XVECTOR2> pointLists);
	void GenerateDungeon(
		int seed,
		int minHeight,
		int minWidth,
		int maxHeight,
		int maxWidth,
		int circleRadius,
		int maxRooms,
		int minHeightselect,
		int maxHeightSelect,
		int minWidthSelect,
		int maxWidthSelect);
	void Render(sf::RenderWindow* window);
	void SetMapBoundaries(int width, int height);

};

