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
	moveDwarf();
	this->m_sprite.move(this->velX, this->velY);
	this->m_pathPosX.clear();
	this->m_pathPosY.clear();
	std::cout << std::endl;
}

void Dwarf::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Dwarf::setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY)
{
	for (int i = 0; i < pathPosX.size(); i++) {
		this->m_pathPosX.push_back(pathPosX[i]);
		this->m_pathPosY.push_back(pathPosY[i]);
		
	}
}

void Dwarf::moveDwarf()
{
	for (int i = 0; i < this->m_pathPosX.size(); i++) {
		if (m_pathPosX[i] > this->m_sprite.getPosition().x / 12)
		{
			this->velX = 12;
			this->velY = 0;
		}
		if (m_pathPosX[i] < this->m_sprite.getPosition().x / 12)
		{
			this->velX = -12;
			this->velY = 0;
		}
		if (m_pathPosY[i] > this->m_sprite.getPosition().y / 12)
		{
			this->velX = 0;
			this->velY = 12;
		}
		if (m_pathPosY[i] < this->m_sprite.getPosition().y / 12)
		{
			this->velX = 0;
			this->velY = -12;
		}
		if ((m_pathPosX[i] == this->m_sprite.getPosition().x / 12) && (m_pathPosY[i] == this->m_sprite.getPosition().y / 12))
		{
			this->velX = 0;
			this->velY = 0;
		}

	}
		
			
	

}	


