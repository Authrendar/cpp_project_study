#pragma once
#include "Entity.h"
class Dwarf :public Entity
{
public:
	Dwarf(int number, sf::Vector2f pos);
	virtual ~Dwarf();

	virtual void update(float& dt);
	virtual void render(sf::RenderTarget* target);
	virtual float getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

	int getNumberOfDwarf() { return this->number; }

private:
	int number;

	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

