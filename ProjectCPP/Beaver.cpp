#include "Beaver.h"

Beaver::Beaver(sf::Vector2f pos)
{
	this->rectTexture = sf::IntRect(36, 12, 12, 12);


	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	this->m_sprite.setTexture(m_texture);
	this->m_sprite.setOrigin(0, 0);
	this->m_sprite.setPosition(pos);

	this->m_hp = 100;
	this->m_panicLevel = false;
	this->m_strength = 1;
}

Beaver::~Beaver()
{
}

void Beaver::update(const float& dt)
{
}

void Beaver::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

float Beaver::getPosX()
{
	return this->m_sprite.getPosition().x/12;
}

float Beaver::getPosY()
{
	return this->m_sprite.getPosition().y / 12;
}

int Beaver::getHP()
{
	return this->m_hp;
}

int Beaver::getStrength()
{
	return this->m_strength;
}

void Beaver::movementController()
{
}

bool Beaver::getPanicFactor()
{
	return this->m_panicLevel;
}
