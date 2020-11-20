#pragma once
#include "Entity.h"
class Tree :public Entity
{
public:
	Tree(sf::Vector2f pos);
	virtual ~Tree();


	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual float getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

private:
	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int hp;
};

