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
	int number;

	States dwarf_states;
	Job dwarf_job;
	void moveDwarf();
	//std::vector<int> m_pathPosX; std::vector<int> m_pathPosY;
	int m_pathPosX, m_pathPosY;
	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int velX, velY;


public:
	Dwarf(int number, sf::Vector2f pos);
	virtual ~Dwarf();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	virtual float getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

	int getNumberOfDwarf() { return this->number; }

	void setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY);

	void setDwarfState(int state);
	void setDwarfJob(int job);

	Job getCurrentJob() const { return dwarf_job; }
	void setSelectedDwarfColor();
	
	bool isSelected;

	std::vector<int> d_posX;
	std::vector<int> d_posY;
	std::vector<int> pathLength;
	void clearPathVec();

	void setIns();
	//std::vector<int> getLengthPath() { return this->d_posX; }
	
	
	//void sortPathVec();

	bool getIsSelected() {  return this->isSelected; }
	


	int getPathPosX() {
		for (int i = 0; i < this->vecInsX[0].size(); i++) {
			return this->vecInsX[0][i];
		}
		
	}
	int getPathPosY() {
		for (int i = 0; i < this->vecInsY[0].size(); i++) {
			return this->vecInsY[0][i];
		}

	}
	std::vector<std::vector<int>> vecInsX;
	std::vector<std::vector<int>> vecInsY;
protected:
	

	
};

