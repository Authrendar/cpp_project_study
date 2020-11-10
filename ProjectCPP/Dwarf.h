#pragma once
#include "Entity.h"
class Dwarf :public Entity
{
public:
	Dwarf(int number, sf::Vector2f pos);
	virtual ~Dwarf();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	virtual float getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

	int getNumberOfDwarf() { return this->number; }

	void setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY);

private:
	int number;

	void moveDwarf();
	std::vector<int> m_pathPosX; std::vector<int> m_pathPosY;
	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float velX, velY;
};

