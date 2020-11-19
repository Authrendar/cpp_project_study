#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{
	
	initMap();
	initObjects();
}

GameState::~GameState()
{

}

void GameState::endState()
{
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();

}

void GameState::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->keyboardUpdate();

	this->pathTime = this->pathFindingClock.getElapsedTime().asSeconds();
	this->gameTime = this->gameClock.getElapsedTime().asSeconds();

	if (pathTime >0.5f) {
		dwarves[0]->setDwarfState(1);
		dwarves[0]->setDwarfJob(1);
		dwarves[1]->setDwarfState(1);
		dwarves[1]->setDwarfJob(1);
		dwarves[2]->setDwarfState(1);
		dwarves[2]->setDwarfJob(1);

		for (auto& dwarf : dwarves) {
			
			if (dwarf->getCurrentJob() == 1)
			{
				//int a = 0;
				for (int i = 0; i < trees.size(); i++) {

					this->pathSystem->setStartEndNodes(trees[i]->getPosX(), trees[i]->getPosY(), dwarf->getPosX(), dwarf->getPosY());
					this->pathSystem->SolveAStar();
					this->pathSystem->update();
					dwarf->setInstructionsMove(this->pathSystem->getPathPosX(), this->pathSystem->getPathPosY(), this->trees.size());
					this->pathSystem->clearPathVector();
				}
				dwarf->clearPathVec();
			}
		}

		
		this->pathLength.clear();	
		for (auto& dwarf : dwarves) {
			dwarf->update(dt);
		}
		this->pathFindingClock.restart();
		
	}
	if (gameTime > 2.f) {


		
		this->gameClock.restart();
	}
}

void GameState::render(sf::RenderTarget* target)
{	
	
	this->map->render(window);
	this->window->setView(this->m_view);
	for (auto& dwarf : dwarves) {
		dwarf->render(window);
	}
	for (auto& tree : trees) {
		tree->render(window);
	}

	
}

void GameState::initMap()
{

	this->map = new Map();
	this->m_view = sf::View(sf::FloatRect(0, 0, 400.f, 300.f));

	pathSystem = new PathFinding(this->window, sf::Vector2u(800.f, 600.f));
	this->pathSystem->setLevelData(this->map->getLevelData());
	
	

}
void GameState::initObjects()
{
	//dwarves.push_back(new Dwarf(0, sf::Vector2f(this->grid_map_size * 0, this->grid_map_size * 3)));
	dwarves.push_back(new Dwarf(1, sf::Vector2f(this->grid_map_size*6, this->grid_map_size*7)));
	dwarves.push_back(new Dwarf(1, sf::Vector2f(this->grid_map_size * 8, this->grid_map_size * 2)));
	dwarves.push_back(new Dwarf(1, sf::Vector2f(this->grid_map_size * 4, this->grid_map_size * 7)));

	/*for (int i = 0; i < 3; i++) {
		dwarves.push_back(new Dwarf(i + 1, sf::Vector2f(this->grid_map_size * 5 + grid_map_size*(i + 2), this->grid_map_size * 4 + grid_map_size*(i + 1))));
	} */
	for (int i = 0; i < this->map->getLevelData().size() / 8; i++) {
		for (int j = 0; j < this->map->getLevelData().size() / 10; j++) {
			if (this->map->getLevelData()[i + j * this->map->getLevelData().size() / 8] == 4) {
				this->trees.push_back(new Tree(sf::Vector2f(this->grid_map_size * i, this->grid_map_size * j)));
			}
		}
	}
	

}

void GameState::keyboardUpdate()
{
	
	for (auto& dwarf : dwarves) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 1) {
				if (!dwarf->getIsSelected()) {
					std::cout << "wybrales dwarfa o numerze " << dwarf->getNumberOfDwarf() << std::endl;
					dwarf->isSelected = true;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 2) {
				
				if (!dwarf->getIsSelected()) {
					std::cout << "wybrales dwarfa o numerze "<<dwarf->getNumberOfDwarf() << std::endl;
					dwarf->isSelected = true;
				}
			}
		}
		if (dwarf->getIsSelected()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			
				std::cout << "Dwarf number : " << dwarf->getNumberOfDwarf() << " is now a lumberjack!" << std::endl;
				dwarf->setDwarfJob(1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{	
			if (dwarf->getIsSelected())
			{
				std::cout << "Odznaczeni" << std::endl;
				dwarf->isSelected = false;
			}

		}
	}

	
	
}

