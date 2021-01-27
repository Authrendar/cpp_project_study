#pragma once
#include "Building.h"
class Sawmill :
	public Building
{
public:
	Sawmill(sf::Vector2f pos);
	virtual ~Sawmill();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual int getPosX() { return this->m_sprite.getPosition().x / 12; }
	virtual int getPosY() { return this->m_sprite.getPosition().y / 12; }

	virtual std::string getObjectType() { return this->buildingType; }

	virtual void setAbilityToInteraction(bool);
	virtual bool getAbilityToInteraction() { return true; }

	virtual int getBuildStatus() { return this->m_buildStatus; }

	virtual void setBuildingStatus(int);
	virtual int getBuildingStatus() { return this->m_buildingStatus; }

	virtual void changeTexture(int buildingState);

	virtual void checkIfDwarfNextToBuilding(Dwarf& dwarf);

	virtual bool getIsDwarfNextToBuilding() { return this->m_nextToSawmill; }
	virtual void changeLevelTypeTexture();

	virtual void setLevelTypeOfBuilding(int type);
	virtual int getLeveLTypeOfBuilding() {
		return this->m_levelTypeOfBuilding;
	}
	virtual int getBuildingGoods() { return 0; }
	virtual void setBuildingGoods(int, bool) { ; }




private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect rectTexture;

	sf::Clock buildingClock;
	float buildingTimer;

	bool m_canBeDeleted;


	
	std::string buildingType;

	int m_buildStatus;
	int m_buildingStatus;

	bool m_nextToSawmill;
	//int m_woodValue;

	int m_levelTypeOfBuilding;
};

