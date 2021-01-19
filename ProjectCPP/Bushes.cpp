#include "Bushes.h"

Bushes::Bushes(sf::Vector2f pos, bool withBerries)
{
	if(!withBerries)
		this->m_rectTexture = sf::IntRect(48, 12, 12, 12);
	else
		this->m_rectTexture = sf::IntRect(0, 24, 12, 12);


	if (!this->m_texture.loadFromFile("tileset.png", this->m_rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	this->m_sprite.setTexture(m_texture);
	this->m_sprite.setOrigin(0, 0);
	this->m_sprite.setPosition(pos);

	this->m_withBerries = withBerries;
	this->m_canInteract = false;
	if (withBerries)
		this->m_nameOfObject = "bushesBerries";
	else
		this->m_nameOfObject = "bushesEmpty";
}

Bushes::~Bushes()
{
}

void Bushes::update(const float& dt)
{
}

void Bushes::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

int Bushes::getPosX()
{
	return this->m_sprite.getPosition().x /12;
}

int Bushes::getPosY()
{
	return this->m_sprite.getPosition().y / 12;
}

std::string Bushes::getObjectType()
{
	return this->m_nameOfObject;
}

void Bushes::changeStateOfBushes(bool withBerries)
{

}

void Bushes::changeTexture(sf::IntRect rectTexture)
{
	this->m_rectTexture = rectTexture;
	if (!this->m_texture.loadFromFile("tileset.png", this->m_rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	
	this->m_sprite.setTexture(m_texture);
}
