#include "Map.h"

Map::Map()
{
	
}

Map::~Map()
{
	this->mapTitle.clear();
}

void Map::initMap()
{
	

	srand(time(0));
	PerlinNoiseGenerator generator;
	utils::NoiseMap noiseMap = generator.setBounds(xMin, xMax, zMin, zMax).buildMap(this->m_width, this->m_height, rand());
	
	
	std::cout.precision(1);
	for (int x = 0; x < m_width; ++x)
	{
		tileValues.push_back(std::vector<int>());
		for (int y = 0; y < m_height; ++y)
		{
			double noiseValue = noiseMap.GetValue(x, y);

			int tile = getTile(noiseValue, numTiles);
			tileValues[x].push_back(tile);

			//levelData.push_back(tile);
			//std::cout << tile << ", ";
			mapTitle.push_back(tile);
			
		}
		
	}
	if (!tileset.loadFromFile("tileset.png"))
		std::cout << "cannot load" << std::endl;
	
	map.setTileSet(tileset);
	map.initBoard(m_width, m_height, tileSize, tileValues);
	std::cout << mapTitle.size() << std::endl;

	
}

void Map::render(sf::RenderTarget* target)
{

	target->draw(this->map);
	
}

void Map::updateMapTitle(int posX, int posY, int numberOfTitle)
{

	if (!tileset.loadFromFile("tileset.png"))
		std::cout << "cannot load" << std::endl;
	
	
	tileValues[posY][posX] = numberOfTitle; 
	this->mapTitle[posY * m_width + posX] = numberOfTitle;
	map.initBoard(m_width, m_height, tileSize, tileValues);
	//this->mapTitle[posX * WIDTH + posY] = numberOfTitle;
	//this->mapTitle[0] = 0;

	//std::cout << mapTitle[0] << std::endl;
	
	//map.initBoard(m_width, m_height, tileSize, tileValues);
	
	//map.initBoard(m_width, m_height, tileSize, tileValues);
	

}

int Map::getCurrentTile(int posX, int posY)
{	
	int currentTile;
	currentTile = tileValues[posY][posX];
	return currentTile;
}

unsigned int Map::getTile(const double& frac, const unsigned int& divisions)
{
	
	double tileSize = 2.2f / (double)divisions;

	double currentTile = -1.f;
	unsigned int ret = 0;
	do {
		currentTile += tileSize;

		if (frac <= currentTile)
		{

			return ret;
		}
		ret++;
	} while (ret < divisions);

	return ret - 1;

}
