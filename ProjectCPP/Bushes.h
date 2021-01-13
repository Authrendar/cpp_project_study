#pragma once
#include "Entity.h"
class Bushes :
	public Entity
{
public:
	Bushes(sf::Vector2f pos, bool withBerries);
	virtual ~Bushes();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual float getPosX();
	virtual float getPosY();

	void changeTexture(bool withBerries);

private:
	sf::Texture m_texture;
	sf::IntRect rectTexture;
	sf::Sprite m_sprite;

	bool m_withBerries;

};

