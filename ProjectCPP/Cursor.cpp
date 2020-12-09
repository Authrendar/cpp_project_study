#include "Cursor.h"
#include <iostream>
Cursor::Cursor()
	:rectTexture(sf::FloatRect(0,12,12,12))
{
	if (!this->m_cursorTexture.loadFromFile("tileset.png",this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}

	this->m_cursorSprite.setTexture(m_cursorTexture);
	this->m_cursorSprite.setColor(sf::Color::Yellow);
	this->m_cursorSprite.setPosition(sf::Vector2f(0,0));
	this->isActive = false;
}

Cursor::~Cursor()
{

}

void Cursor::update(const float &dt)
{
	if (this->isActive) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->m_cursorSprite.move(this->grid_map_size, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->m_cursorSprite.move(-this->grid_map_size, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->m_cursorSprite.move(0, -this->grid_map_size);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->m_cursorSprite.move(0, this->grid_map_size);
		}
		//std::cout << currentTile << std::endl;
	}
}

void Cursor::render(sf::RenderTarget* target)
{
	if(this->isActive)
		target->draw(this->m_cursorSprite);
}

void Cursor::setCurrnetTile(int tile)
{
	switch (tile)
	{
	case 0:
		currentTile = STONE;
		break;
	case 1:
		currentTile = TREE;
		break;
	case 2:
		currentTile = GRASS;
		break;
	case 3:
		currentTile = SAND;
		break;
	case 4:
		currentTile = WATER;
		break;
	default:
		break;
	}
}
