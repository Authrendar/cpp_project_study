#include "Cursor.h"

Cursor::Cursor()
	:rectTexture(sf::FloatRect(0,12,12,12))
{
	if (!this->m_cursorTexture.loadFromFile("tileset.png",this->rectTexture)) {
		std::cout << "Couldn't find any texture" << std::endl;
	}

	this->m_cursorSprite.setTexture(m_cursorTexture);
	this->m_cursorSprite.setColor(sf::Color::Yellow);
	this->m_cursorSprite.setPosition(sf::Vector2f(16*12,12*12)); // Tworzy sie zawsze "na œrodku"
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
		this->keyTime = this->keyClock.getElapsedTime().asSeconds();
		if (keyTime > 0.2f) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				
				this->isButtonQClicked = true;
				

				keyClock.restart();

			}
		}
		//std::cout <<"TILE SIZE: " <<tiles.size() << std::endl;
	}
}

void Cursor::render(sf::RenderTarget* target)
{
	if(this->isActive)
		target->draw(this->m_cursorSprite);
}

void Cursor::viewController(sf::View &map_View)
{
	
}

void Cursor::setCurrnetTile(int tile)
{
	switch (tile)
	{
	case 0:
		currentTile = STONE;
		mn_currentTile = 0;
		break;
	case 1:
		currentTile = TREE;
		mn_currentTile = 1;
		break;
	case 2:
		currentTile = GRASS;
		mn_currentTile = 2;
		break;
	case 3:
		currentTile = SAND;
		mn_currentTile = 3;
		break;
	case 4:
		currentTile = WATER;
		mn_currentTile = 4;
		break;
	default:
		break;
	}
}



