#pragma once
#include "Animal.h"
class Beaver :public Animal
{
public:
	Beaver(sf::Vector2f pos);
	virtual ~Beaver();
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget* target);


	virtual float getPosX();
	virtual float getPosY();

	virtual int getHP();
	virtual int getStrength();

	virtual void movementController();

	virtual bool getPanicFactor();

private:
	sf::Texture m_texture;
	sf::IntRect rectTexture;
	sf::Sprite m_sprite;

	int m_hp, m_strength;
	bool m_panicLevel;
};

