#pragma once
#include "Entity.h"
#include "PathFinding.h"
class Dwarf :public Entity
{
private:
	enum States :signed int {
		IDLE = 0,
		WALK = 1,
		CUTTING = 2,
		BUILDING =3,
		WORKING = 4
	};

	enum Job :signed int {
		FREE,
		LUMBERJACK,
		MINER,
		BUILDER,
		PORTER
	};
	struct stats {
		int hp;
		int strength;
		int lvl;
	};
	
	stats m_stats;

public:
	Dwarf(int number, sf::Vector2f pos);
	virtual ~Dwarf();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	virtual float getPosX() { return this->m_sprite.getPosition().x /12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

	//Path finding functions
	void path_setPositions(int x, int y);
	void path_setMap(std::vector<int> map);
	void path_findPath(int size);
	void path_InstructionSolution();
	void setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY, int index, int dwarfState);

	void setDwarfState(int state);
	void setDwarfJob(int job);



	//Stat set
	void setWoodValue(int woodValue);
	int getWoodValue() { return this->m_woodValue; }
	void resetWoodValue();

	void setDwarfMustPutAway(bool mustPutAway) { this->mustPutAway = mustPutAway; }
	bool isDwarfMustPutAway() { return this->mustPutAway; }
	
	
	bool getIsSelected() { return this->isSelected; }

	int getNumberOfDwarf() { return this->m_number; }

	Job getCurrentJob() const { return dwarf_job; }
	States getCurrentState() const { return dwarf_states; }

	int getDwarfHp() const { return this->m_stats.hp; }
	int getDwarfStrength() const { return this->m_stats.strength; }
	int getDwarfLvl() const { return this->m_stats.lvl; }
	

	void clearPathVec();
	void path_clearPathVec();

	bool isSelected;

	std::vector<std::vector<int>> vecInsX;
	std::vector<std::vector<int>> vecInsY;
	std::vector<int> vecSizes;

	void setIsGoing(bool isGoing) {
		this->m_isGoing = isGoing;
	}

	bool getIsGoing() {
		return this->m_isGoing;
	}

	void setUpdateInstructions(bool updateInstructions) {
		this->m_updateInstructions = updateInstructions;
	}

	bool getUpdateInstructions() {
		return this->m_updateInstructions;
	}

	void setIsThereAnyStock(bool anyStock) {
		this->isThereAnyStock = anyStock;
	}

	bool getIsThereAnyStock() {
		return this->isThereAnyStock;
	}

private:

	void moveDwarf();
	void setDwarfColor();



	int m_index;

	int velX, velY;
	int m_number;
	int m_pathPosX, m_pathPosY;

	States dwarf_states;
	Job dwarf_job;
	
	sf::Clock pathDwarfClock;
	float pathTime;

	PathFinding* findPath;
	
	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	bool m_isGoing;
	bool m_updateInstructions;
	
	//Eq stats

	int m_woodValue, m_stoneValue, m_berriesValue, m_meatValue;
	bool mustPutAway;
	bool isThereAnyStock;
	
};

