#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
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
	int getWoodValue() { return this->m_valueOfWood; }

	void updatePlanksValue(int valueOfPlanks);
	int getPlanksValue() { return this->m_valueOfPlanks; }

	void setDataFromDwarf(int id, int hp, int work,int state, int strength, int lvl);

	void resetData() {
		for (auto& data : vec_dwarfData) {
			data.setString(" ");
		}
	}
	
private:

	sf::View *interfaceView;
	sf::Texture interfaceTexture;
	sf::Sprite interfaceSprite;
	sf::Font mainFont;
	sf::Text createText(int characterSize, sf::Vector2f pos, std::string stringText, sf::Color color);


	sf::Text cursorPosition;
	std::string posOfCursorString;
	//Main stats of colony
	sf::Text m_textValueOfWood;
	std::string m_valueOfWoodString;

	sf::Text m_textValueOfPlanks;
	std::string m_valueOfPlanksString;

	int m_valueOfWood;
	int m_valueOfPlanks;
	std::vector<sf::Text> vec_dwarfData;

	//strings
	std::string dwarf_job;
	std::string dwarf_state;

};

