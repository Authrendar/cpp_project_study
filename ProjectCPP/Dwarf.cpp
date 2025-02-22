#include "Dwarf.h"

Dwarf::Dwarf(int number, sf::Vector2f pos)
	:m_woodValue(0),
	m_stoneValue(0),
	m_berriesValue(0),
	m_meatValue(0),
	mustPutAway(false)
{
	this->m_number = number;
	this->rectTexture = sf::IntRect(12, 12, 12, 12);
	

	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	this->m_sprite.setTexture(m_texture);
	this->m_sprite.setOrigin(0, 0);
	this->m_sprite.setPosition(pos);
	//this->m_sprite.setColor(sf::Color::Blue);
	sf::Color color = this->m_sprite.getColor();
	
	this->velX = 0; this->velY = 0;
	this->dwarf_states = IDLE;
	this->dwarf_job = FREE;
	isSelected = false;

	this->m_stats.hp = 100;
	this->m_stats.strength = 10;
	this->m_stats.lvl = 1;
	
	this->isThereAnyStock = false;


}

Dwarf::~Dwarf()
{
	this->vecInsX.clear();
	this->vecInsY.clear();
	this->vecSizes.clear();
}

void Dwarf::update(const float& dt)
{
	
	moveDwarf();
	setDwarfColor();
	this->m_sprite.move(this->velX, this->velY);
	this->velX = 0;
	this->velY = 0;
	
	
}

void Dwarf::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Dwarf::path_setPositions(int x, int y)
{
	if(this->getUpdateInstructions())
		this->findPath->setStartEndNodes(x, y, this->getPosX(),this->getPosY());

}

void Dwarf::path_setMap(std::vector<int> map)
{
	if (this->getUpdateInstructions()) {
		this->findPath = new PathFinding();
		this->findPath->setLevelData(map);
	}
}

void Dwarf::path_findPath(int size)
{
	if (this->getUpdateInstructions()) {
		this->findPath->SolveAStar();
		this->findPath->update();
		this->setInstructionsMove(this->findPath->getPathPosX(), this->findPath->getPathPosY(), size, 1);
		this->setUpdateInstructions(false);
			
	}
	
	
}

void Dwarf::setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY, int index, int dwarfState)
{	
		this->vecSizes.push_back(pathPosX.size());
		this->vecInsX.push_back(pathPosX);
		this->vecInsY.push_back(pathPosY);
		this->setDwarfState(dwarfState);
		this->m_index = index;
}

void Dwarf::path_InstructionSolution()
{
	
		if (m_index > 0) {
			
				std::sort(this->vecSizes.begin(), std::partition(vecSizes.begin(), vecSizes.end(), [](int n) { return n != 0; }));
				vecSizes.resize(1);
	
				for (int i = 0; i < this->vecInsX.size(); i++) {
					if ((this->vecSizes[0] == this->vecInsX[i].size()) && (this->vecSizes[0] == this->vecInsY[i].size()))
						for (int j = 1; j < this->vecInsX[i].size(); j++) {
						//	std::cout << this->vecInsX[i].size() << std::endl;
							if ((this->getPosX() == this->vecInsX[i][j - 1]) && (this->getPosY() == this->vecInsY[i][j - 1])) {
								this->m_pathPosX = this->vecInsX[i][j];
								this->m_pathPosY = this->vecInsY[i][j];
								
							}
						}
					
				}
			
		}
}

void Dwarf::setDwarfState(int states)
{
	switch (states) {
	case 0:
		this->dwarf_states = IDLE;
		break;
	case 1:
		this->dwarf_states = WALK;
		break;
	case 2:
		this->dwarf_states = CUTTING;
		break;
	case 3: dwarf_states = BUILDING;
		break;
	}
}

void Dwarf::setDwarfJob(int job)
{
	switch(job) {
	case 0:
		this->dwarf_job = FREE;
		break;
	case 1:
		this->dwarf_job = LUMBERJACK;
		break;
	case 2:
		this->dwarf_job = MINER;
		break;
	case 3:
		this->dwarf_job = BUILDER;
		break;
	case 4:
		this->dwarf_job = PORTER;
		break;
	}
}

void Dwarf::setWoodValue(int woodValue)
{
	this->m_woodValue += woodValue;

	if (m_woodValue == 20)
		this->mustPutAway = true;
	
	if (this->getCurrentJob() == 4) {
		if (m_woodValue > 0) {
			this->mustPutAway = true;
			
		}
	}

	//std::cout << "Dwarf value of wood: " << this->m_woodValue << " is he must put away? " << this->mustPutAway << std::endl;
}

void Dwarf::resetWoodValue()
{
	this->m_woodValue = 0;
	this->mustPutAway = false;

}

void Dwarf::setDwarfColor()
{	
	if (getIsSelected())
		this->m_sprite.setColor(sf::Color::Red);
	else
		this->m_sprite.setColor(sf::Color::Blue);

	if (dwarf_job == LUMBERJACK) {
		if(this->m_sprite.getColor() == sf::Color::Blue)
			this->m_sprite.setColor(sf::Color::Cyan);
		if (this->getIsSelected())
			this->m_sprite.setColor(sf::Color::Yellow);
	}
	if (dwarf_job == BUILDER) {
		if (this->m_sprite.getColor() == sf::Color::Blue)
			this->m_sprite.setColor(sf::Color(255, 69, 0));
		if (this->getIsSelected())
			this->m_sprite.setColor(sf::Color(165, 42, 42));
	}

	if (dwarf_job == PORTER) {
		if (this->m_sprite.getColor() == sf::Color::Blue)
			this->m_sprite.setColor(sf::Color(75, 0, 130));
		if (this->getIsSelected())
			this->m_sprite.setColor(sf::Color(238, 130, 238));
	}
}



void Dwarf::clearPathVec()
{
	this->vecSizes.clear();
	this->vecInsX.clear();
	this->vecInsY.clear();
	
	
}

void Dwarf::path_clearPathVec()
{	if(this->vecSizes.size()>0)
		this->findPath->clearPathVector();
}

void Dwarf::moveDwarf()
{
	
	
	switch (this->dwarf_states) {
	case States::IDLE:
		
		//this->setIsGoing(false);
		
		break;

	case States::WALK:
		
		if ((m_pathPosX > 0) || (m_pathPosY > 0)) {
			if (m_pathPosX < this->getPosX())
			{
				this->velX = -12;
				this->velY = 0;
			}
			if (m_pathPosX > this->getPosX())
			{
				this->velX = 12;
				this->velY = 0;
			}
			if (m_pathPosY < this->getPosY()) {
				this->velX = 0;
				this->velY = -12;
			}
			if (m_pathPosY > this->getPosY()) {
				this->velX = 0;
				this->velY = 12;
			}

		}
		
		//std::cout << this->m_pathPosX << std::endl;
		
		break;
	case States::CUTTING:
		//this->clearPathVec();
		//this->findPath->clearPathVector();
		break;
	case States::BUILDING:

		break;
	}


}	
