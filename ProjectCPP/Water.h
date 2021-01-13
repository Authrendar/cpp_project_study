#pragma once
#include "Tile.h"
class Water :
	public Tile
{
public:
	Water(int x, int y, int tile);

private:
	int m_x, m_y, m_tile;
};

