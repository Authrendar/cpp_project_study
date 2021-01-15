#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
class Interface
{
public:
	Interface();
	virtual ~Interface();

	void render(sf::RenderTarget* target);

	sf::View getInterfaceView() {
		return *this->interfaceView;
	}

	void update();

	void setCursorPosition(int posX, int posY);


	void updateWoodValue(int valueOfWood);

private:

	sf::View *interfaceView;

	sf::Font mainFont;
	sf::Text m_interfaceText;

	sf::RectangleShape lineBetweenStats;

	sf::Text createText(int characterSize, sf::Vector2f pos, std::string stringText, sf::Color color);

	sf::Text cursorPosition;
	std::string posOfCursorString;
	//Main stats of colony
	sf::Text m_textValueOfWood;
	std::string m_valueOfWoodString;
	int m_valueOfWood;
};

