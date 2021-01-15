#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Map.h"
class Animal 
{
public:
	
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;


	virtual int getPosX() = 0;
	virtual int getPosY() = 0;

	virtual int getHP() = 0;
	virtual int getStrength() = 0;

	void movementController(Map &m_map);
	void moveAnimal();

	virtual bool getPanicFactor() = 0;
	
	virtual bool getIsWalking() = 0;
	virtual bool getCanSetRandom() = 0;

	virtual void setIsWalking(bool) = 0;

	int getVelX() {
		return this->m_velX;
	}

	int getVelY() {
		return this->m_velY;
	}
	
	virtual void setCanSetRandom(bool) = 0;

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
	
	
private:
	
	std::vector<int> directions;
	bool up, down, left, right;
	const int n_up = 0, n_down = 1, n_left = 2, n_right = 3;
	int m_velX, m_velY;
	sf::Sprite m_sprite;
};

