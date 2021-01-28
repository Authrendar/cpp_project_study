#include "Sawmill.h"

Sawmill::Sawmill(sf::Vector2f pos)
{
	this->rectTexture = sf::IntRect(0, 0, 24, 24);


	if (!this->m_texture.loadFromFile("sawmill.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}

	
	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setPosition(pos);
	

	this->buildingType = "Sawmill";
	this->m_canBeDeleted = false;
	this->m_buildStatus = 0;

	this->buildingTimer = 0.f;
	this->m_buildingStatus = 0;

	//this->m_woodValue = 0;
	this->m_nextToSawmill = false;

	this->m_woodValue = 0;
	this->m_planksValue = 0;
}

Sawmill::~Sawmill()
{
}

void Sawmill::update(const float& dt)
{
}

void Sawmill::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Sawmill::setAbilityToInteraction(bool)
{
}

void Sawmill::setBuildingStatus(int)
{
}

void Sawmill::changeTexture(int buildingState)
{
	this->setBuildingStatus(buildingState);
	if (buildingState == 3) {
		this->rectTexture = sf::IntRect(24, 0, 24, 24);
		if (!this->m_texture.loadFromFile("sawmill.png", this->rectTexture)) {
			std::cout << "Couldn't find any texture" << std::endl;
		}

		this->m_sprite.setTexture(m_texture);
	}
}

void Sawmill::checkIfDwarfNextToBuilding(Dwarf& dwarf)
{
	if ((dwarf.getCurrentJob() == 4)) {

		if ((this->getPosX() + 1 == int(dwarf.getPosX())) && (this->getPosY() == int(dwarf.getPosY())))
			this->m_nextToSawmill = true;

		if ((this->getPosX() - 1 == int(dwarf.getPosX())) && (this->getPosY() == int(dwarf.getPosY())))
			this->m_nextToSawmill = true;

		if ((this->getPosY() - 1 == int(dwarf.getPosY())) && (this->getPosX() == int(dwarf.getPosX())))
			this->m_nextToSawmill = true;

		if ((this->getPosY() + 1 == int(dwarf.getPosY())) && (this->getPosX() == int(dwarf.getPosX())))
			this->m_nextToSawmill = true;

	}
	else
		this->m_nextToSawmill = false;
}

void Sawmill::changeLevelTypeTexture()
{
}

void Sawmill::setLevelTypeOfBuilding(int type)
{
}

void Sawmill::setBuildingGoods(int woodValue, int typeOfGoods)
{
	if (typeOfGoods == 0) // wood
	{
		this->m_planksValue = this->m_planksValue +  woodValue + 10;
		std::cout << "sawmill planks: " << m_planksValue << "\n";

	}
}
