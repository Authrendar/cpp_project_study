#include "ObjectRenderMenager.h"

void ObjectRenderMenager::setLevelData(std::vector<int> levelData)
{
	for (auto tile : levelData) {
		this->m_levelData.push_back(tile);
	}

	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 50; y++) {
			if (this->checkTileType(x,y) == 2) // Grass
				this->m_tiles.push_back(new Grass(x, y, 2));
			if (this->checkTileType(x, y) == 4) // Water
				this->m_tiles.push_back(new Water(x, y, 4));
		}
	}

}

void ObjectRenderMenager::setObjectsOnMap()
{
	this->setReservoir();
}

void ObjectRenderMenager::setReservoir()
{

	/*for (auto& tile : m_tiles) {
		if (tile->getTileType() == 4) {
			
			
		}
	}*/
	//std::cout << m_Cursor->getPosX() << ":" << m_Cursor->getPosY() << std::endl;
	//int x = m_water->getPosX();
	//int y = m_water->getPosY();
	

	/*for (auto& tile : this->m_tiles) {
		if (tile->getTileType() == 4) {
			std::cout << "Water pos: " << tile->getPosX() << ":" << tile->getPosY() << std::endl;
		}
		m_water = new Tile(tile->getPosX(), tile->getPosY(), tile->getTileType());
			m_Cursor = new CheckingCursor(tile->getPosX(), tile->getPosY());
	}*/
}
