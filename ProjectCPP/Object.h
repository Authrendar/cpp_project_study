#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Object
{
public:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	virtual int getPosX() = 0;
	virtual int getPosY() = 0;

	virtual std::string getObjectType() = 0;

	virtual void setAbilityToInteraction(bool) = 0;
	virtual bool getAbilityToInteraction() = 0;
};

