#pragma once
#include "DungeonRoom.h"

class DungeonGenerator
{
private:
	sf::RenderWindow* m_window;
	XVECTOR2 m_MapCenter;
public:
	void SetWindow(sf::RenderWindow* w);

	std::vector<DungeonRoom*> m_Rooms;
	std::vector<DungeonRoom*> m_SelectedRooms;
	DungeonGenerator();
	~DungeonGenerator();
	void SeparateRooms();
	void SelectRooms(
		int minHeightSelect,
		int maxHeightSelect,
		int minWidthSelect,
		int maxWidthSelect);
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

