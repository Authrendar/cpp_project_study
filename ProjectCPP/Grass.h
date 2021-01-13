#pragma once
#include "Tile.h"
class Grass :
	public Tile
{
public:
	Grass(int x, int y, int tile);

private:
	int m_x, m_y, m_tile;
};

