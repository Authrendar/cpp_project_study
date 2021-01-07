#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "TileMap.h"
#include "PerlinNoiseGenerator.h"
#include <ctime>
class Map
{
public:
	Map();
	virtual ~Map();

	void initMap();
	void render(sf::RenderTarget* target);
	void updateMapTitle(int posX, int posY, int numberOfTitle);
	std::vector<int> getLevelData() { return this->mapTitle; }

	int getCurrentTile(int posX, int posY);

private:

	TileMap map;
	std::vector<int> mapTitle;
	std::vector<std::vector<int> > tileValues;
	sf::Texture tileset;
	int lengthOfMap;
	const unsigned int m_width = 50, m_height = 50;
	const unsigned int tileSize = 12, numTiles = 5;				
	const double xMin = 1.0f, xMax = 10.f, zMin = 1.f, zMax = 5.0f;
		
	unsigned int getTile(const double& frac, const unsigned int& divisions);
	
};

