#include "Grass.h"

Grass::Grass(int x, int y, int tile)
	:Tile(x, y, tile)
{
	this->m_y = y;
	this->m_tile = tile;
	this->m_x = x;
}

