#include "Bushes.h"

Bushes::Bushes(sf::Vector2f pos, bool withBerries)
{
	if(!withBerries)
		this->rectTexture = sf::IntRect(48, 12, 12, 12);
	else
		this->rectTexture = sf::IntRect(0, 24, 12, 12);


	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	this->m_sprite.setTexture(m_texture);
	this->m_sprite.setOrigin(0, 0);
	this->m_sprite.setPosition(pos);

	this->m_withBerries = withBerries;
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

float Bushes::getPosX()
{
	return 0.0f;
}

float Bushes::getPosY()
{
	return 0.0f;
}

void Bushes::changeTexture(bool withBerries)
{
}
