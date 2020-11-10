#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{

	
	initObjects();
	pathSystem = new PathFinding(this->window,sf::Vector2u(800.f,600.f));
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
	this->pathSystem->SolveAStar();
	this->pathSystem->update();
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

sf::View GameState::getView()
{
	return this->m_view;
}

void GameState::initMap()
{
	
	this->map = new Map();
	this->m_view = sf::View(sf::FloatRect(0, 0, 400.f, 300.f));


	this->pathSystem->setLevelData(this->map->getLevelData());
	this->pathSystem->setStartEndNodes(dwarves[0]->getPosX(), dwarves[0]->getPosY(), trees[0]->getPosX(), trees[0]->getPosY());
	
	
}

void GameState::initObjects()
{
	dwarves.push_back(new Dwarf(0, sf::Vector2f(this->grid_map_size * 2, this->grid_map_size * 3)));
	trees.push_back(new Tree(sf::Vector2f(this->grid_map_size * 0, this->grid_map_size * 6)));

}

