#include "Stock.h"

Stock::Stock(sf::Vector2f pos, int typeOfStock)
{
	this->rectTexture = sf::IntRect(24, 24, 12, 12);


	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}

	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setPosition(pos);

	this->buildingType= "Stock";
	this->m_canBeDeleted = false;
	this->m_buildStatus = 0;

	this->buildingTimer = 0.f;
	this->m_buildingStatus = 0;
	
	this->m_woodValue = 0;
	this->m_nextToStock = false;
}

Stock::~Stock()
{
}

void Stock::update(const float& dt)
{
	
	
}

void Stock::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Stock::setAbilityToInteraction(bool canBeDeleted)
{
	this->m_canBeDeleted = canBeDeleted;
}

void Stock::setBuildingStatus(int buildingStatus)
{
	this->m_buildingStatus = buildingStatus;
}

void Stock::changeTexture(int buildingState)
{
	this->setBuildingStatus(buildingState);
	if (buildingState == 3) {
		this->rectTexture = sf::IntRect(36, 24, 12, 12);
		if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
			std::cout << "Couldn't find any texture" << std::endl;
		}

		this->m_sprite.setTexture(m_texture);
	}
}

void Stock::checkIfDwarfNextToBuilding(Dwarf& dwarf)
{
	if ((dwarf.getCurrentJob() == 1) && (dwarf.isDwarfMustPutAway())) {

		if ((this->getPosX() + 1 == int(dwarf.getPosX())) && (this->getPosY() == int(dwarf.getPosY())))
			this->m_nextToStock = true;
		
		if ((this->getPosX() - 1 == int(dwarf.getPosX())) && (this->getPosY() == int(dwarf.getPosY())))
			this->m_nextToStock = true;
		
		if ((this->getPosY() - 1 == int(dwarf.getPosY())) && (this->getPosX() == int(dwarf.getPosX())))
			this->m_nextToStock = true;
		
		if ((this->getPosY() + 1 == int(dwarf.getPosY())) && (this->getPosX() == int(dwarf.getPosX())))
			this->m_nextToStock = true;
		
	}
	else 
		this->m_nextToStock = false;
	
}


