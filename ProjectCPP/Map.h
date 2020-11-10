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

	std::vector<int> getLevelData() { return this->mapTitle; }

private:

	TileMap map;
	std::vector<int> mapTitle;
};

