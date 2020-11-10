#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{
	initObjects();
	initMap();
	
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
	

	this->pathTime = this->pathFindingClock.getElapsedTime().asSeconds();
	this->gameTime = this->gameClock.getElapsedTime().asSeconds();

	if (gameTime > .5f) {

		
		gameClock.restart();
	}

	if (pathTime > 0.5f) {
		
		this->pathSystem->setStartEndNodes(trees[0]->getPosX(), trees[0]->getPosY(), dwarves[0]->getPosX(), dwarves[0]->getPosY());

		this->pathSystem->SolveAStar();
		this->pathSystem->update();


		dwarves[0]->setInstructionsMove(this->pathSystem->getXPos(), this->pathSystem->getYPos());
		dwarves[0]->update(dt);
		
		this->pathSystem->clearPathVector();
		this->pathFindingClock.restart();
		
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
	trees.push_back(new Tree(sf::Vector2f(this->grid_map_size * 0, this->grid_map_size * 6)));

}

