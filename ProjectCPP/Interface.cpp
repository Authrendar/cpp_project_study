#include "Interface.h"

Interface::Interface()
{
	if (!this->mainFont.loadFromFile("mainFont.ttf")) {
		std::cout << "Could not find any fonts..." << std::endl;
	}
	else
		std::cout << "Font found" << std::endl;

	if (!this->interfaceTexture.loadFromFile("interface.png")) {
		std::cout << "Could not find interface texture..." << std::endl;
	}
	
	this->interfaceSprite.setTexture(this->interfaceTexture);
	this->interfaceSprite.setPosition(sf::Vector2f(0, 5));
	
	//this->m_interfaceText = this->createText(30, sf::Vector2f(10, 30), "Interface menu", sf::Color::White);
	

	this->interfaceView = new sf::View(sf::FloatRect(0.f, 0.f, 800.f, 900.f));
	this->interfaceView->setViewport(sf::FloatRect(0.f, 0.85f, 1.f, 1.f));
	

	//Stats
	this->m_valueOfWood = 0;
	this->m_valueOfPlanks = 0;
	this->m_textValueOfWood = createText(23, sf::Vector2f(60, 4), this->m_valueOfWoodString, sf::Color::Green);
	this->m_textValueOfWood.setString("0");
	this->cursorPosition = createText(23, sf::Vector2f(745, 4), this->posOfCursorString, sf::Color::Yellow);
	this->m_valueOfPlanksString = "0";
	this->m_textValueOfPlanks = createText(23, sf::Vector2f(265, 4), this->m_valueOfPlanksString, sf::Color(205, 133, 63));


	{
		this->vec_dwarfData.push_back(this->createText(20, sf::Vector2f(525, 33), " ", sf::Color::Red));
		this->vec_dwarfData.push_back(this->createText(20, sf::Vector2f(495, 53), " ", sf::Color::Red));
		this->vec_dwarfData.push_back(this->createText(20, sf::Vector2f(515, 73), " ", sf::Color::Blue));
		this->vec_dwarfData.push_back(this->createText(20, sf::Vector2f(520, 93), " ", sf::Color::Green));
		this->vec_dwarfData.push_back(this->createText(20, sf::Vector2f(545, 113), " ", sf::Color::Cyan));

	}
}

Interface::~Interface()
{
}

void Interface::render(sf::RenderTarget* target)
{
	target->draw(this->interfaceSprite);
	target->draw(this->m_textValueOfWood);
	target->draw(this->cursorPosition);
	target->draw(this->m_textValueOfPlanks);
	for (auto& data : vec_dwarfData) {
		target->draw(data);
	}
	
}

void Interface::update()
{
	
}

void Interface::setCursorPosition(int posX, int posY)
{
	this->posOfCursorString = std::to_string(posX) + ":" + std::to_string(posY);
	this->cursorPosition.setString(this->posOfCursorString);
}


void Interface::updateWoodValue(int valueOfWood)
{
	//std::cout <<"Value of wood w interfejsie przed: " <<valueOfWood << std::endl;
	this->m_valueOfWood = valueOfWood;
	//std::cout << "Value of wood w interfejsie po: " << valueOfWood << std::endl;

	this->m_valueOfWoodString = std::to_string(this->m_valueOfWood);
	this->m_textValueOfWood.setString(this->m_valueOfWoodString);
}

void Interface::updatePlanksValue(int valueOfPlanks)
{
	this->m_valueOfPlanks = valueOfPlanks;
	

	this->m_valueOfPlanksString = std::to_string(this->m_valueOfPlanks);
	this->m_textValueOfPlanks.setString(this->m_valueOfPlanksString);
}

void Interface::setDataFromDwarf(int id, int hp, int job, int state, int strength, int lvl)
{
	vec_dwarfData[0].setString(std::to_string(id));
	vec_dwarfData[1].setString(std::to_string(hp));

	if (job == 0)this->dwarf_job = "Free"; if (job == 1)this->dwarf_job = "Lumberjack"; if (job == 2)this->dwarf_job = "Miner"; if (job == 3)this->dwarf_job = "Builder";
	if (job == 4)this->dwarf_job = "Porter";
	vec_dwarfData[2].setString(this->dwarf_job);

	if (state == 0) this->dwarf_state = "Idle"; if (state == 1) this->dwarf_state = "Walking"; if (state == 2) this->dwarf_state = "Cutting"; if (state == 3) this->dwarf_state = "Building";
	vec_dwarfData[3].setString(this->dwarf_state);

	vec_dwarfData[4].setString(std::to_string(strength));
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
