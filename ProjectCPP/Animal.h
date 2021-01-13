#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Entity.h"
class Animal :public Entity
{
public:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;


	virtual float getPosX() = 0;
	virtual float getPosY() = 0;

	virtual int getHP() = 0;
	virtual int getStrength() = 0;

	virtual void movementController() = 0;

	virtual bool getPanicFactor() = 0;


};

