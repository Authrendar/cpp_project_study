#include "Interface.h"

Interface::Interface()
{
	if (!this->mainFont.loadFromFile("mainFont.ttf")) {
		std::cout << "Could not find any fonts..." << std::endl;
	}
	else
		std::cout << "Font found" << std::endl;

	

	this->m_interfaceText = this->createText(30, sf::Vector2f(10, 30), "Interface menu", sf::Color::White);
	
	this->lineBetweenStats.setSize(sf::Vector2f(800.f, 2.f));
	this->lineBetweenStats.setPosition(sf::Vector2f(0, 30.f));
	this->lineBetweenStats.setFillColor(sf::Color::White);

	this->interfaceView = new sf::View(sf::FloatRect(0.f, 0.f, 800.f, 900.f));
	this->interfaceView->setViewport(sf::FloatRect(0.f, 0.85f, 1.f, 1.f));
	


	//Stats
	this->m_valueOfWood = 0;
	this->m_valueOfWoodString = "Wood: " + std::to_string(this->m_valueOfWood);
	this->m_textValueOfWood = createText(25, sf::Vector2f(5, -5), this->m_valueOfWoodString, sf::Color::Green);


	this->cursorPosition = createText(25, sf::Vector2f(600, -5), this->posOfCursorString, sf::Color::Yellow);
	

}

Interface::~Interface()
{
}

void Interface::render(sf::RenderTarget* target)
{
	target->draw(this->lineBetweenStats);
	target->draw(this->m_interfaceText);
	target->draw(this->m_textValueOfWood);
	target->draw(this->cursorPosition);
}

void Interface::update()
{
	
}

void Interface::setCursorPosition(int posX, int posY)
{
	this->posOfCursorString = "Cursor pos: " + std::to_string(posX) + ":" + std::to_string(posY);
	this->cursorPosition.setString(this->posOfCursorString);
}


void Interface::updateWoodValue(int valueOfWood)
{

	this->m_valueOfWood += valueOfWood;
	this->m_valueOfWoodString = "Wood: " + std::to_string(this->m_valueOfWood);
	this->m_textValueOfWood.setString(this->m_valueOfWoodString);
}

sf::Text Interface::createText(int characterSize, sf::Vector2f pos, std::string stringText, sf::Color color)
{
	sf::Text text;
	text.setFont(this->mainFont);
	text.setCharacterSize(characterSize);
	text.setPosition(pos);
	text.setFillColor(color);
	text.setString(stringText);
	return text;
}
