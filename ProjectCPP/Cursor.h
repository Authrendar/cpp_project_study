#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class Cursor
{
public:
	Cursor();
	virtual ~Cursor();

	void update(const float &dt);
	void render(sf::RenderTarget* target);


	void setCursorActive(bool activate) { this->isActive = activate; }
	bool getCursorActive() { return this->isActive; }
	void viewController(sf::View &map_View);

	int getPosX() { return this->m_cursorSprite.getPosition().x / this->grid_map_size; }
	int getPosY() { return this->m_cursorSprite.getPosition().y / this->grid_map_size; }

	void setCurrnetTile(int tile);
	int getCurrentTile() { return this->mn_currentTile; }

	bool isButtonQClicked = false;
	void setButtonState(bool button) { this->isButtonQClicked = button; }
	bool getIsButtonClicked() { return this->isButtonQClicked; }

	
private:

	sf::Texture m_cursorTexture;
	sf::Sprite m_cursorSprite;
	sf::IntRect rectTexture;

	sf::Clock keyClock;
	float keyTime;
	int grid_map_size = 12;
	bool isActive;
	
	int mn_currentTile;

	enum Tile :signed int {
		STONE,
		TREE,
		GRASS,
		SAND,
		WATER
	};

	Tile currentTile;
	

	
};