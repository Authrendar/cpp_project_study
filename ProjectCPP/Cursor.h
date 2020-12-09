#pragma once
#include <SFML/Graphics.hpp>
class Cursor
{
public:
	Cursor();
	virtual ~Cursor();

	void update(const float &dt);
	void render(sf::RenderTarget* target);


	void setCursorActive(bool activate) { this->isActive = activate; }
	bool getCursorActive() { return this->isActive; }

	int getPosX() { return this->m_cursorSprite.getPosition().x / 12; }
	int getPosY() { return this->m_cursorSprite.getPosition().y / 12; }

	void setCurrnetTile(int tile);
	int getCurrentTile() { return this->mn_currentTile; }

	void setTileActive(bool tileActive);
	bool getTileActive() { return this->tileActive; }
private:

	sf::Texture m_cursorTexture;
	sf::Sprite m_cursorSprite;
	sf::IntRect rectTexture;

	int grid_map_size = 12;
	bool isActive;
	bool tileActive;
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