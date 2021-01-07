#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{
	m_cursor = new Cursor();
	initMap();
	initObjects();
	
}

GameState::~GameState()
{
	m_cursor->~Cursor();
}

void GameState::endState()
{
	this->dwarves.clear();
	this->trees.clear();
		
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();

}

void GameState::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->keyboardUpdate();

	this->gameTime = this->gameClock.getElapsedTime().asSeconds();

	
	if (gameTime > 0.1f) {

		this->m_cursor->update(dt);
		this->m_cursor->setCurrnetTile(this->map->getCurrentTile(this->m_cursor->getPosX(), this->m_cursor->getPosY()));
		this->createObjects();
		this->lumberjackUpdate();
		this->pathSystem->setLevelData(this->map->getLevelData());
		for (auto& dwarf : dwarves) {
			dwarf->update(dt);
		}
		
		
		this->gameClock.restart();

		
	}
}

void GameState::render(sf::RenderTarget* target)
{	
	this->map->render(window);
	this->window->setView(*m_view);
	this->m_cursor->viewController(*this->m_view);
	for (auto& dwarf : dwarves) {
		dwarf->render(window);
	}
	this->m_cursor->render(target);
	for (auto& tree : trees) {
		tree->render(window);
	}
	

	
}

void GameState::initMap()
{

	this->map = new Map();
	this->m_view =new sf::View(sf::FloatRect(0, 0, 400.f, 300.f));
	
	
	pathSystem = new PathFinding(this->window, sf::Vector2u(800.f, 600.f));
	this->pathSystem->setLevelData(this->map->getLevelData());
	
	

}
void GameState::initObjects()
{
	
	dwarves.push_back(new Dwarf(1, sf::Vector2f(this->grid_map_size*2, this->grid_map_size*2)));
	dwarves.push_back(new Dwarf(2, sf::Vector2f(this->grid_map_size * 8, this->grid_map_size * 2)));
	dwarves.push_back(new Dwarf(3, sf::Vector2f(this->grid_map_size * 4, this->grid_map_size * 7)));
	

	/*for (int i = 0; i < 3; i++) {
		dwarves.push_back(new Dwarf(i + 1, sf::Vector2f(this->grid_map_size * 5 + grid_map_size*(i + 2), this->grid_map_size * 4 + grid_map_size*(i + 1))));
	} */
	/*for (int i = 0; i < this->map->getLevelData().size() / 20; i++) {
		for (int j = 0; j < this->map->getLevelData().size() / 20; j++) {
			if (this->map->getLevelData()[i + j * this->map->getLevelData().size() / 20] == 1) {
				this->trees.push_back(new Tree(sf::Vector2f(this->grid_map_size * i, this->grid_map_size * j), i * this->map->getLevelData().size() / 20 + j));
				std::cout << "Drzewko " <<   i <<":" << j <<std::endl;
				
			}
		}
	}*/
	//std::cout << "Tree: " << trees.size() << std::endl;
	//std::cout << "Size of one dwarf object: " << sizeof(trees[0]) << std::endl;
	
}

void GameState::keyboardUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		this->m_cursor->setCursorActive(true);
		
	}
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 3) {

				if (!dwarf->getIsSelected()) {
					std::cout << "wybrales dwarfa o numerze " << dwarf->getNumberOfDwarf() << std::endl;
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

void GameState::createObjects()
{

	if (this->m_cursor->getIsButtonClicked()) {
		if (this->m_cursor->getCurrentTile() == 1) {
			for (int i = 0; i < trees.size(); i++) {
				if ((this->m_cursor->getPosX() == trees[i]->getPosX()) && (this->m_cursor->getPosY() == trees[i]->getPosY())) {
					trees.erase(trees.begin() + i);
				}
			}

			this->trees.push_back(new Tree(sf::Vector2f(this->m_cursor->getPosX() * this->grid_map_size, this->m_cursor->getPosY() * this->grid_map_size), 0));
			
		}
		this->m_cursor->setButtonState(false);
		
	}

	//std::cout << "Tree size: " << trees.size() << std::endl;
}

void GameState::lumberjackUpdate()
{
	for (auto& dwarf : dwarves) { //Path to tree

		if (dwarf->getCurrentJob() == 1)
		{
			
			for (int i = 0; i < trees.size(); i++) {

				this->pathSystem->setStartEndNodes(trees[i]->getPosX(), trees[i]->getPosY(), dwarf->getPosX(), dwarf->getPosY());
				//this->pathSystem->setObstacleNode(dwarf->getPosX(), dwarf->getPosY());
				
				this->pathSystem->SolveAStar(dwarf->getPosX(),dwarf->getPosY());
				this->pathSystem->update();
				dwarf->setInstructionsMove(this->pathSystem->getPathPosX(), this->pathSystem->getPathPosY(), this->trees.size(), 2); //2 to wartosc stanu dwarfa - w tym przypadku to CUTTING
				this->pathSystem->clearPathVector();
				

			}
			dwarf->clearPathVec();
		}
	}

	/* #####################*/

	//Cutting trees

	for (auto& dwarf : dwarves) {
		if ((dwarf->getCurrentJob() == 1)&&(trees.size()>0)) {
			std::vector <int> indexVec;
			for (int i = 0; i < trees.size(); i++) {
				
				
					if ((this->trees[i]->getPosX() + 1 == dwarf->getPosX()) && (this->trees[i]->getPosY() == dwarf->getPosY()))
					{
						indexVec.push_back(i);
						//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;

						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosX() - 1 == dwarf->getPosX()) && (this->trees[i]->getPosY() == dwarf->getPosY()))
					{
						indexVec.push_back(i);
					//	std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosY() - 1 == dwarf->getPosY()) && (this->trees[i]->getPosX() == dwarf->getPosX()))
					{
						indexVec.push_back(i);
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosY() + 1 == dwarf->getPosY()) && (this->trees[i]->getPosX() == dwarf->getPosX()))
					{
						indexVec.push_back(i);
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					
					if (trees[i]->getHpOfTree() == 0) {
						this->map->updateMapTitle(trees[i]->getPosX(), trees[i]->getPosY(), 2);
						//std::cout << "Trees: " << trees[i]->getPosX() << ":" << trees[i]->getPosY() << std::endl;
						this->trees.erase(trees.begin() + i);
						indexVec.clear();
						
					}
					
				
			}
		}
		else
		{
			dwarf->setDwarfState(0);
		}
	}
}

