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
	
	//std::cout << this->m_pathPosX << " : " << this->m_pathPosY << std::endl;
	//std::cout << std::endl;
	
	std::cout << "m_posX: " << this->m_pathPosX << std::endl;
	std::cout << "m_posY: " << this->m_pathPosY << std::endl;
	moveDwarf();
	setSelectedDwarfColor();
	this->m_sprite.move(this->velX, this->velY);
	this->velX = 0;
	this->velY = 0;
	

	std::cout << std::endl;
}

void Dwarf::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Dwarf::setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY)
{

	this->vecInsX.push_back(pathPosX);
	this->vecInsY.push_back(pathPosY);
	for (int i = 1; i < this->vecInsX[0].size(); i++) {
		std::cout << "x : " << this->vecInsX[0][i] << " y:" << this->vecInsY[0][i] << std::endl;
		if ((this->getPosX() == this->vecInsX[0][i-1])&&(this->getPosY() == this->vecInsY[0][i-1])) {
			m_pathPosX = this->vecInsX[0][i];
			m_pathPosY = this->vecInsY[0][i];
		}
	}

	//this->m_pathPosX = pathPosX;
	//this->m_pathPosY = pathPosY;
	
	
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

void Dwarf::setSelectedDwarfColor()
{	
	if (getIsSelected())
		this->m_sprite.setColor(sf::Color::Red);
	else
		this->m_sprite.setColor(sf::Color::Blue);
}

void Dwarf::clearPathVec()
{
	
	this->vecInsX.clear();
	this->vecInsY.clear();
	
}

void Dwarf::setIns()
{

}

void Dwarf::moveDwarf()
{
	
	
	switch (this->dwarf_states) {
	case States::IDLE:
		//std::cout << "Dwarf standing " << ", ";
		break;

	case States::WALK:
		//std::cout << "Dwarf x: " << this->m_pathPosX << " y: " << this->m_pathPosY << std::endl;
		for (int i = 0; i < pathLength.size(); i++) {
			//std::cout << "Path length: " << this->pathLength[i] << std::endl;
		}
		
		
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
		if ((m_pathPosX < 0) || (m_pathPosY < 0))
			this->dwarf_states = IDLE;
			

		break;
	case States::CUTTING:

		break;
	}


}	


