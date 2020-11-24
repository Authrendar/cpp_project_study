#include "Map.h"

Map::Map()
{
	initMap();
}

Map::~Map()
{
}

void Map::initMap()
{
	int level[] = {
	   2,2,3,3,2,2,2,2,2,2,
	   2,4,2,3,2,3,3,4,2,2,
	   4,2,2,2,3,2,2,3,2,2,
	   4,4,2,4,4,4,4,4,4,4,
	   4,4,4,3,3,2,2,2,3,4,
	   2,4,2,2,2,2,2,2,2,4,
	   2,2,2,2,2,3,2,2,2,2,
	   2,2,3,3,2,2,2,2,2,3
	};

	this->lengthOfMap = sizeof(level) / sizeof(*level);

	for (int i = 0; i < this->lengthOfMap; i++) {
		this->mapTitle.push_back(level[i]);
	}

	
	if (this->lengthOfMap == this->mapTitle.size()) {
		if (!map.load("tileset.png", sf::Vector2u(12, 12), this->mapTitle, 10, 8)) {
			std::cout << "cannot load..";
		}
	}
}

void Map::render(sf::RenderTarget* target)
{

	target->draw(this->map);
	
}

void Map::updateMapTitle(int posX, int posY, int numberOfTitle)
{


	//std::cout << posY * WIDTH+ posX << std::endl;
	this->mapTitle[posY * WIDTH + posX] = numberOfTitle;
	if (!map.load("tileset.png", sf::Vector2u(12, 12), this->mapTitle, 10, 8)) {
		std::cout << "cannot load..";
	}
	///std::cout << "Title: " << this->mapTitle.at(posY * WIDTH + posX) << std::endl;

}
