#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Entity
{
public:

	Entity();

	virtual ~Entity();

	virtual void update(float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	virtual float getPosX() = 0;
	virtual float getPosY() = 0;

private:

	
};

