#include "Water.h"

Water::Water(int x, int y, int tile)
	:Tile(x,y,tile)
{
	this->m_x = x;
	this->m_y = y;
	this->m_tile = tile;
}

