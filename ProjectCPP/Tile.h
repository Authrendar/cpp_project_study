#pragma once
class Tile {
public:
	Tile(int x, int y, int tile);
	int getPosX();
	int getPosY();

	int getTileType();
private:
	int m_x, m_y, m_tile;
};

