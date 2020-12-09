#include "Tree.h"

Tree::Tree(sf::Vector2f pos, int index)
{
	this->rectTexture = sf::IntRect(48, 0, 12, 12);


	if (!this->m_texture.loadFromFile("tileset.png", this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}
	this->m_sprite.setTexture(m_texture);
	this->m_sprite.setOrigin(0, 0);
	this->m_sprite.setPosition(pos);
	this->m_sprite.setColor(sf::Color::Green);

	this->m_Stats.index = index;
	this->m_Stats.hp = 20;
}

Tree::~Tree()
{
	
}

void Tree::update(const float& dt)
{
	
	
}

void Tree::render(sf::RenderTarget* target)
{
	target->draw(this->m_sprite);
}

void Tree::cutTheTree(int strength)
{
	this->time_breakOfCutting = this->breakOfCutting.getElapsedTime().asSeconds();

	if (this->time_breakOfCutting > 1.f) {
		std::cout << "Hp " << this->m_Stats.hp << std::endl;
		this->m_Stats.hp-=strength;
		this->breakOfCutting.restart();
	}
	
}
