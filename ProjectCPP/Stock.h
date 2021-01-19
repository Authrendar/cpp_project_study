#pragma once
#include "Building.h"
class Stock :
	public Building
{
public:
	Stock(sf::Vector2f pos, int typeOfStock);
	virtual ~Stock();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual int getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual int getPosY() { return this->m_sprite.getPosition().y/12; }

	virtual std::string getObjectType() { return this->buildingStatus; }

	virtual void setAbilityToInteraction(bool);
	virtual bool getAbilityToInteraction() { return true; }

	virtual int getBuildStatus() { return 0; }

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect rectTexture;

	bool m_canBeDeleted;

	std::string m_typeOfStock;
	std::string buildingStatus;
};

