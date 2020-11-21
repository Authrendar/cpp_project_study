#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "TileMap.h"
class Map
{
public:
	Map();
	virtual ~Map();

	void initMap();
	void render(sf::RenderTarget* target);
	void updateMapTitle(int posX, int posY, int numberOfTitle);
	std::vector<int> getLevelData() { return this->mapTitle; }

private:

	TileMap map;
	std::vector<int> mapTitle;
	int lengthOfMap;
	int WIDTH=10, HEIGHT=8;
};

