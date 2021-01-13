#pragma once
#include <vector>
#include <iostream>
#include <list>
#include "Grass.h"
#include "Water.h"

class ObjectRenderMenager
{
public:
	void setLevelData(std::vector<int> levelData);
	void setObjectsOnMap();

private:
	std::vector<int> m_levelData;
	std::vector<Tile*> m_tiles;

	

	int checkTileType(int x, int y) {
		return m_levelData[y * 50 + x];
	}

	

	

	void setReservoir();
};

