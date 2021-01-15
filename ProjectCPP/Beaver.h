#pragma once
#include "Animal.h"
class Beaver :public Animal
{
public:
	Beaver(sf::Vector2f pos);
	virtual ~Beaver();
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget* target);


	virtual int getPosX();
	virtual int getPosY();

	virtual int getHP();
	virtual int getStrength();

	virtual void setIsWalking(bool isWalking) {
		this->m_isWalking = isWalking;
	}
	virtual void setCanSetRandom(bool canSetRandom) {
		this->m_canSetRandom = canSetRandom;
	}

	virtual bool getPanicFactor();

	virtual bool getIsWalking() {
		return this->m_isWalking;
	}
	virtual bool getCanSetRandom() {
		return this->m_canSetRandom;
	}

	

private:
	sf::Texture m_texture;
	sf::IntRect rectTexture;
	sf::Sprite m_sprite;

	sf::Clock moveBeaverClock;
	float moveBeaverTime;

	float randomTimeRestart;
	int m_hp, m_strength;
	bool m_panicLevel;
	bool m_isWalking;
	bool m_canSetRandom;
	
};

