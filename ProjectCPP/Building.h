#pragma once
#include "Object.h"
#include "Dwarf.h"
class Building :
	public Object
{
public:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	virtual int getPosX() = 0;
	virtual int getPosY() = 0;

	virtual std::string getObjectType() = 0;

	virtual void setAbilityToInteraction(bool) = 0;
	virtual bool getAbilityToInteraction() = 0;

	virtual int getBuildStatus() = 0; 
	virtual void checkIfDwarfNextToBuilding(Dwarf& dwarf) = 0;
	virtual bool getIsDwarfNextToBuilding() = 0;


	virtual void changeTexture(int buildingState) = 0; //W zaleznosci od typu budynku, kazdy budynek ma swoje okreslone wartosci textur jakie moze zmieniac
	virtual void changeLevelTypeTexture() = 0;

	virtual void setLevelTypeOfBuilding(int type) = 0;
	virtual int getLeveLTypeOfBuilding() = 0;

	virtual void setBuildingStatus(int) = 0; //0 -> while building, 1->already built
	virtual int getBuildingStatus() = 0; 


	virtual int getBuildingGoods() = 0;
	virtual void setBuildingGoods(int, bool) = 0; //add or sub
};

