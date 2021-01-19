#pragma once
#include "Object.h"
class Bushes :
	public Object
{
public:
	Bushes(sf::Vector2f pos, bool withBerries);
	virtual ~Bushes();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual int getPosX();
	virtual int getPosY();

	virtual std::string getObjectType();
	void changeStateOfBushes(bool withBerries);

	virtual void setAbilityToInteraction(bool canInteract) {

		this->m_canInteract = canInteract;

		if (canInteract) {
			this->changeTexture(sf::IntRect(12, 24, 12, 12));
		}
		else
			this->changeTexture(sf::IntRect(0, 24, 12, 12));
	}

	virtual bool getAbilityToInteraction() {
		return this->m_canInteract;
	}

private:
	sf::Texture m_texture;
	sf::IntRect m_rectTexture;
	sf::Sprite m_sprite;

	std::string m_nameOfObject;
	bool m_withBerries;

	bool m_canInteract;

	void changeTexture(sf::IntRect rectTexture);

};

