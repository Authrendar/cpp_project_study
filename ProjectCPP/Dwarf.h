#pragma once
#include "Entity.h"
class Dwarf :public Entity
{
private:
	enum States :signed int {
		IDLE = 0,
		WALK = 1,
		CUTTING = 2
	};

	enum Job :signed int {
		FREE,
		LUMBERJACK,
		MINER
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
	virtual float getPosX() { return this->m_sprite.getPosition().x / 12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y / 12; }

	void setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY, int index, int dwarfState);

	void setDwarfState(int state);
	void setDwarfJob(int job);



	
	bool getIsSelected() { return this->isSelected; }

	int getNumberOfDwarf() { return this->number; }

	Job getCurrentJob() const { return dwarf_job; }

	int getDwarfHp() const { return this->m_stats.hp; }
	int getDwarfStrength() const { return this->m_stats.strength; }
	int getDwarfLvl() const { return this->m_stats.lvl; }

	void clearPathVec();

	bool isSelected;

	std::vector<std::vector<int>> vecInsX;
	std::vector<std::vector<int>> vecInsY;
	std::vector<int> vecSizes;

private:

	void moveDwarf();
	void setDwarfColor();

	int velX, velY;
	int number;
	int m_pathPosX, m_pathPosY;

	States dwarf_states;
	Job dwarf_job;
	
	sf::Clock pathDwarfClock;
	float pathTime;

	

	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;


	


protected:
	

	
};

