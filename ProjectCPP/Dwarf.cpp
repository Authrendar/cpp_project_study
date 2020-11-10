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
}

Dwarf::~Dwarf()
{
}

void Dwarf::update(const float& dt)
{
	std::cout << "Dwarf update" << std::endl;
	moveDwarf();
	
	this->m_sprite.move(this->velX, this->velY);
	this->velX = 0;
	this->velY = 0;
	
	//std::cout << std::endl;
}

void Dwarf::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Dwarf::setInstructionsMove(int pathPosX, int pathPosY /*std::vector<int> pathPosX, std::vector<int> pathPosY */ )
{
	this->m_pathPosX = pathPosX;
	this->m_pathPosY = pathPosY;
}

void Dwarf::moveDwarf()
{
	std::cout <<"DWARF PATHPOSX " <<m_pathPosX << std::endl;
	
		if (m_pathPosX < this->getPosX())
		{
			//std::cout << "Pos: " << this->getPosX() << std::endl;
			this->velX = -12;
			this->velY = 0;
		}
		if (m_pathPosX > this->getPosX())
		{
			//std::cout << "Pos: " << this->getPosX() << std::endl;
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


