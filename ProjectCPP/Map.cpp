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
	   4,2,3,3,2,2,2,2,2,2,
	   2,3,4,3,2,3,3,4,2,2,
	   4,2,2,2,3,2,2,3,2,2,
	   4,2,3,3,3,4,2,2,3,2,
	   4,2,2,3,3,2,2,2,3,4,
	   4,4,2,2,2,2,2,2,2,4,
	   4,2,2,2,2,3,2,2,2,2,
	   4,2,3,3,2,2,2,2,2,3
	};

	for (int i = 0; i < sizeof(level) / sizeof(*level); i++) {
		this->mapTitle.push_back(level[i]);
	}
	if (!map.load("tileset.png", sf::Vector2u(12, 12), level, 10, 8)) {
		std::cout << "cannot load..";
	}

}

void Map::render(sf::RenderTarget* target)
{
	target->draw(this->map);
}
