#include "Dwarf.h"

Dwarf::Dwarf(int number, sf::Vector2f pos)
{
	this->number = number;
	this->rectTexture = sf::IntRect(12, 0, 12, 12);
	

	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	this->m_sprite.setTexture(m_texture);
	this->m_sprite.setOrigin(0, 0);
	this->m_sprite.setPosition(pos);
	this->m_sprite.setColor(sf::Color::Blue);
	
	this->velX = 0; this->velY = 0;
	this->dwarf_states = IDLE;
	this->dwarf_job = FREE;
	isSelected = false;
}

Dwarf::~Dwarf()
{
}

void Dwarf::update(const float& dt)
{
	moveDwarf();
	setDwarfColor();
	this->m_sprite.move(this->velX, this->velY);
	this->velX = 0;
	this->velY = 0;
	if (dwarf_job == LUMBERJACK) {
		dwarf_states = WALK;
	}

	
}

void Dwarf::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Dwarf::setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY, int index, int dwarfState)
{	

	this->vecSizes.push_back(pathPosX.size());
	this->vecInsX.push_back(pathPosX);
	this->vecInsY.push_back(pathPosY);

	 
	if (vecSizes.size() == index) {
		std::sort(this->vecSizes.begin(), std::partition(vecSizes.begin(), vecSizes.end(), [](int n) { return n != 0; }));
		if (this->vecSizes[0] < 2)
			this->setDwarfState(dwarfState);
		for (int i = 0; i < this->vecInsX.size(); i++) {
			if ((this->vecSizes[0] == this->vecInsX[i].size()) && (this->vecSizes[0] == this->vecInsY[i].size()))
				for (int j = 1; j < this->vecInsX[i].size(); j++) {
					if ((this->getPosX() == this->vecInsX[i][j - 1]) && (this->getPosY() == this->vecInsY[i][j - 1])) {
						this->m_pathPosX = this->vecInsX[i][j];
						this->m_pathPosY = this->vecInsY[i][j];
						
					}
					//std::cout << this->vecSizes[0] << std::endl;
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
	}
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
	}
}

void Dwarf::clearPathVec()
{
	this->vecSizes.clear();
	this->vecInsX.clear();
	this->vecInsY.clear();
	
}

void Dwarf::moveDwarf()
{
	
	
	switch (this->dwarf_states) {
	case States::IDLE:
		//std::cout << "Dwarf standing " << ", ";
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
		
		
			

		break;
	case States::CUTTING:
		std::cout << "CUTTING" << std::endl;
		break;
	}


}	
