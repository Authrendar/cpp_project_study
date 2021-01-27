#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Object.h"
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



	void setPosition(int x, int y) {
		this->m_cursorSprite.setPosition(sf::Vector2f(x * 12, y * 12));
	}

	void setCurrentObject(Object &obj);


	
	
	//buttons
	void setButtonQState(bool button) { this->isButtonQClicked = button; }
	bool getIsQButtonClicked() { return this->isButtonQClicked; }

	void setButtonRState(bool button) { this->isButtonRClicked = button; }
	bool getIsRButtonClicked() { return this->isButtonRClicked; }

	void setButtonTState(bool button) { this->isButtonTClicked = button; }
	bool getIsTButtonClicked() { return this->isButtonTClicked; }

	bool getObjectCanBePlaced() { return this->m_objectCanBePlaced; }
	void setObjectCanBePlaced(bool objCanBePlaced) { this->m_objectCanBePlaced = objCanBePlaced; }
	
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
	
	//Buttons
	bool isButtonQClicked = false;
	bool isButtonRClicked = false;
	bool isButtonTClicked = false;

	bool m_objectCanBePlaced = true;
};