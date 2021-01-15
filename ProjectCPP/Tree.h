#pragma once
#include "Entity.h"
class Tree :public Entity
{
public:
	Tree(sf::Vector2f pos, int index);
	virtual ~Tree();


	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual float getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

	int getIndexOfTree() { return this->m_Stats.index; }
	int getHpOfTree() { return this->m_Stats.hp; }
	int getValueOfWood() { return this->m_Stats.valueOfWood; }

	void cutTheTree(int strength);

private:
	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Clock breakOfCutting;
	float time_breakOfCutting;
	

	struct stats {
		int hp;
		int index;
		int valueOfWood;
	};
	stats m_Stats;
};

