#include "Tile.h"

Tile::Tile(int x, int y, int tile)
{
	this->m_x = x;
	this->m_y = y;
	this->m_tile = tile;
}

int Tile::getPosX()
{
	return this->m_x;
}

int Tile::getPosY()
{
	return this->m_y;
}

int Tile::getTileType()
{
	return this->m_tile;
}
