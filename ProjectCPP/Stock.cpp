#include "Stock.h"

Stock::Stock(sf::Vector2f pos, int typeOfStock)
{
	this->rectTexture = sf::IntRect(24, 24, 12, 12);


	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}

	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setPosition(pos);

	this->buildingStatus = "building";
	this->m_canBeDeleted = false;
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
	std::cout << "kurwa";
}


