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

	

	if (pathTime >0.2f) {
		
		
		for (int i = 0; i < this->trees.size(); i++) {
			this->pathSystem->setStartEndNodes(trees[i]->getPosX(), trees[i]->getPosY(), dwarves[0]->getPosX(), dwarves[0]->getPosY());
			this->pathSystem->SolveAStar();
			this->pathSystem->update();
			if(this->pathSystem->getPathPosX().size()>0)
			this->pathLength.push_back(this->pathSystem->getPathPosX().size());	

			if (i == this->trees.size() - 1) {
				std::sort(this->pathLength.begin(), this->pathLength.end());
				//std::cout << this->pathSystem->getXPos() << std::endl;
				this->dwarves[0]->setInstructionsMove(this->pathSystem->getXPos(), this->pathSystem->getYPos());
			}
			this->pathSystem->clearPathVector();
		}
		
		
		
		this->pathLength.clear();	
		dwarves[0]->update(dt);
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
	dwarves.push_back(new Dwarf(0, sf::Vector2f(this->grid_map_size * 5, this->grid_map_size * 4)));
	
	for (int i = 0; i < 2; i++) {
		dwarves.push_back(new Dwarf(i + 1, sf::Vector2f(this->grid_map_size * 5 + grid_map_size*(i + 1), this->grid_map_size * 4 + grid_map_size*(i + 1))));
	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		std::cout << "wybrales dwarfa o nr 1..." << std::endl;
}

