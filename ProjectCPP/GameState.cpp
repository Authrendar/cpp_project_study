#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{
	m_cursor = new Cursor();
	initMap();
	initObjects();

	srand(time(NULL));
	
}

GameState::~GameState()
{
	delete this->m_cursor;
	delete this->map;
	delete this->m_interface;
	delete this->m_view;

	this->dwarves.clear();
	this->animals.clear();
	this->bushes.clear();
	this->trees.clear();
	
	
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

		if(this->m_cursor->getCursorActive())
			this->m_interface->setCursorPosition(this->m_cursor->getPosX(), this->m_cursor->getPosY());

		this->setTileToRemove();
		
		this->pathSystem->setLevelData(this->map->getLevelData());
		//this->setBuildingToBuild(); // XD
		
		this->lumberjackUpdate();
		this->setBuildingToBuild();
		for (auto& dwarf : dwarves) {
			dwarf->update(dt);
			if (dwarf->getIsSelected())
				this->m_interface->setDataFromDwarf(dwarf->getNumberOfDwarf(), dwarf->getDwarfHp(), dwarf->getCurrentJob(), dwarf->getCurrentState(), dwarf->getDwarfStrength(), dwarf->getDwarfLvl());
			

		}
		for (auto& animal : animals) {
			animal->movementController(*this->map);
			animal->update(dt);
		}
		for (auto& bush : bushes) {
			this->m_cursor->setCurrentObject(*bush);
		}
		
		
		this->gameClock.restart();

		
	}
}

void GameState::render(sf::RenderTarget* target)
{
	
	this->map->render(window);
	this->window->setView(this->m_interface->getInterfaceView());
	this->m_interface->render(target);
	this->window->setView(*m_view);
	
	if(this->m_cursor->getCursorActive())
		this->m_cursor->viewController(*this->m_view);
	for (auto& dwarf : dwarves) {
		dwarf->render(window);
	}
	for (auto& tree : trees) {
		tree->render(window);
	}
	for (auto& animal : animals) {
		animal->render(window);
	}
	for (auto& bush : bushes) {
		bush->render(window);
	}
	if(this->m_preparedBuilding!= nullptr)
		this->m_preparedBuilding->render(target);
	this->m_cursor->render(target);
	
	
	
}

void GameState::initMap()
{

	this->map = new Map();
	this->map->initMap();
	this->m_view =new sf::View(sf::FloatRect(0, 0, 396.f, 396.f));
	
	this->m_interface = new Interface();
	
	this->m_view->setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.85f));
	

	
	
	pathSystem = new PathFinding(this->window, sf::Vector2u(800.f, 600.f));
	this->pathSystem->setLevelData(this->map->getLevelData());
	

	
	

}
void GameState::initObjects()
{
	//Create Dwarves by random positions
	int posX;
	int posY;
	for (int i = 0; i < 3; i++) {
		do {
			posX = rand() % 15+5;
			posY = rand() % 15+5;
		} while (this->map->getCurrentTile(posX, posY) != 2);
		dwarves.push_back(new Dwarf(i+1, sf::Vector2f(this->grid_map_size * posX, this->grid_map_size * posY)));
	}
	//Create Beavers by random 
	int valueOfBeavers = rand() % 6 + 2;
	posX = 0;
	posY = 0;
	for (int i = 0; i < valueOfBeavers; i++) {
		do {
			posX = rand() % 48 + 1;
			posY = rand() % 48 + 1;
		} while (this->map->getCurrentTile(posX, posY) != 3);
		this->animals.push_back(new Beaver(sf::Vector2f(this->grid_map_size *posX, this->grid_map_size * posY)));
	}

	//Create bushes by random
	int valueOfBushes= rand() % 20 + 5;
	posX = 0;
	posY = 0;
	int withBerries = 0;
	for (int i = 0; i < valueOfBushes; i++) {
		do {
			posX = rand() % 48 + 1;
			posY = rand() % 48 + 1;
			withBerries = rand() % 2 + 0;
		} while (this->map->getCurrentTile(posX, posY) != 2);
		this->bushes.push_back(new Bushes(sf::Vector2f(this->grid_map_size * posX, this->grid_map_size * posY),withBerries));
	}
	
	//m_beaver = new Beaver(sf::Vector2f(this->grid_map_size*10, this->grid_map_size*10));
	//Beaver m_beaver(sf::Vector2f(this->grid_map_size*10, this->grid_map_size*10));
	
	// ostatnia liczba to typ skladu zapasow

	
	
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
					dwarf->isSelected = true;
					this->m_cursor->setPosition(dwarf->getPosX(), dwarf->getPosY());
						
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 2) {
				
				if (!dwarf->getIsSelected()) {
					dwarf->isSelected = true;
					this->m_cursor->setPosition(dwarf->getPosX(), dwarf->getPosY());
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 3) {

				if (!dwarf->getIsSelected()) {

					dwarf->isSelected = true;
					this->m_cursor->setPosition(dwarf->getPosX(), dwarf->getPosY());
				}
			}
		}
		if (dwarf->getIsSelected()) {
			this->keyPressTime = this->keyPressClock.getElapsedTime().asSeconds();
			if (this->keyPressTime > 0.2f){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {

					if (dwarf->getCurrentJob() != 1)
					{
						dwarf->setDwarfJob(1);
					}
					else {
						dwarf->setDwarfJob(0);
						
						
					}
					this->keyPressClock.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {

					if (dwarf->getCurrentJob() != 3)
					{
						dwarf->setDwarfJob(3);
					}
					else {
						dwarf->setDwarfJob(0);


					}
					this->keyPressClock.restart();
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{	
			if (dwarf->getIsSelected())
			{
				dwarf->isSelected = false;
				this->m_interface->resetData();
					
			}

		}
	}
}

void GameState::setTileToRemove()
{

	if (this->m_cursor->getIsQButtonClicked()) {
		if (this->m_cursor->getCurrentTile() == 1) {
			for (auto& dwarf : dwarves) {
				dwarf->setIsGoing(false);
			}
			for (int i = 0; i < trees.size(); i++) {
				if ((this->m_cursor->getPosX() == trees[i]->getPosX()) && (this->m_cursor->getPosY() == trees[i]->getPosY())) {
					trees.erase(trees.begin() + i);
				}
			}
			if(this->trees.size()<6)
				this->trees.push_back(new Tree(sf::Vector2f(this->m_cursor->getPosX() * this->grid_map_size, this->m_cursor->getPosY() * this->grid_map_size), 0));
			
		}

		
		this->m_cursor->setButtonQState(false);
		
	}

	//std::cout << "Tree size: " << trees.size() << std::endl;
}

void GameState::setBuildingToBuild()
{
	
	
	if (this->m_cursor->getIsRButtonClicked()) {

		if (this->m_cursor->getCurrentTile() == 2) {
			this->m_preparedBuilding = new Stock(sf::Vector2f(this->m_cursor->getPosX() * this->grid_map_size, this->m_cursor->getPosY() * this->grid_map_size), 0); // ostatnia liczba to typ skladu zapaso

			
		}
		this->m_cursor->setButtonRState(false);
	}
	

	for (auto& dwarf : dwarves) {
		if (dwarf->getCurrentJob() == 3) {
			if (this->m_preparedBuilding != nullptr) {
				if (!dwarf->getIsGoing()) {
					this->pathSystem->setStartEndNodes(this->m_preparedBuilding->getPosX(), this->m_preparedBuilding->getPosY(), dwarf->getPosX(), dwarf->getPosY());
					this->pathSystem->SolveAStar();
					this->pathSystem->update();

					dwarf->setIsGoing(true);
				}
				
				dwarf->setInstructionsMove(this->pathSystem->getPathPosX(), this->pathSystem->getPathPosY(), 1, 1); 
				
				
				
				
			}
			dwarf->clearPathVec();
		}
	}


	//Build the building
	for (auto& dwarf : dwarves) {
		if (dwarf->getCurrentJob() == 3) {
			if (this->m_preparedBuilding != nullptr) {
				if ((this->m_preparedBuilding->getPosX() + 1 == int(dwarf->getPosX())) && (this->m_preparedBuilding->getPosY() == int(dwarf->getPosY())))
				{
					//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;
					std::cout << "No elo" << std::endl;
					dwarf->setDwarfState(1);
					
				}
				if ((this->m_preparedBuilding->getPosX() - 1 == int(dwarf->getPosX())) && (this->m_preparedBuilding->getPosY() == int(dwarf->getPosY())))
				{
					std::cout << "No elo" << std::endl;
					//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;
					dwarf->setDwarfState(1);

				}
				if ((this->m_preparedBuilding->getPosY() - 1 == int(dwarf->getPosY())) && (this->m_preparedBuilding->getPosX() == int(dwarf->getPosX())))
				{
					std::cout << "No elo" << std::endl;
					//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;
					dwarf->setDwarfState(1);

				}
				if ((this->m_preparedBuilding->getPosY() + 1 ==int( dwarf->getPosY())) && (this->m_preparedBuilding->getPosX() == int(dwarf->getPosX())))
				{
					std::cout << "No elo" << std::endl;
					//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;
					dwarf->setDwarfState(1);

				}
			}
		}
	}


	
}

void GameState::lumberjackUpdate()
{

	for (auto& dwarf : dwarves) { //Path to tree
		if (!dwarf->isDwarfMustPutAway()) {
			if (dwarf->getCurrentJob() == 1)
			{
				for (int i = 0; i < trees.size(); i++) {

					if (!dwarf->getIsGoing()) {
						this->pathSystem->setStartEndNodes(trees[i]->getPosX(), trees[i]->getPosY(), dwarf->getPosX(), dwarf->getPosY());
						this->pathSystem->SolveAStar();
						this->pathSystem->update();
					}
					
					dwarf->setInstructionsMove(this->pathSystem->getPathPosX(), this->pathSystem->getPathPosY(), this->trees.size(), 1); //2 to wartosc stanu dwarfa - w tym przypadku to CUTTING

					if (i == trees.size() - 1)
						dwarf->setIsGoing(true);

					
				}
				dwarf->clearPathVec();
				

			}

		}
	}

	/* #####################*/

	//Cutting trees

	for (auto& dwarf : dwarves) {
		if (!dwarf->isDwarfMustPutAway()){
			if ((dwarf->getCurrentJob() == 1) && (trees.size() > 0)) {
				std::vector <int> indexVec;
				for (int i = 0; i < trees.size(); i++) {


					if ((this->trees[i]->getPosX() + 1 == dwarf->getPosX()) && (this->trees[i]->getPosY() == dwarf->getPosY()))
					{
						indexVec.push_back(i);
						//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;
						dwarf->setDwarfState(2);
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosX() - 1 == dwarf->getPosX()) && (this->trees[i]->getPosY() == dwarf->getPosY()))
					{
						indexVec.push_back(i);
						dwarf->setDwarfState(2);
						//	std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosY() - 1 == dwarf->getPosY()) && (this->trees[i]->getPosX() == dwarf->getPosX()))
					{
						indexVec.push_back(i);
						dwarf->setDwarfState(2);
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosY() + 1 == dwarf->getPosY()) && (this->trees[i]->getPosX() == dwarf->getPosX()))
					{
						indexVec.push_back(i);
						dwarf->setDwarfState(2);
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[indexVec[0]]->cutTheTree(dwarf->getDwarfStrength());
					}

					if (trees[i]->getHpOfTree() == 0) {
						this->map->updateMapTitle(trees[i]->getPosX(), trees[i]->getPosY(), 2);
						//std::cout << "Trees: " << trees[i]->getPosX() << ":" << trees[i]->getPosY() << std::endl;
						this->m_interface->updateWoodValue(trees[i]->getValueOfWood());
						dwarf->setWoodValue(trees[i]->getValueOfWood());
						this->trees.erase(trees.begin() + i);

						this->pathSystem->clearPathVector();

						dwarf->setDwarfState(0);
						dwarf->setIsGoing(false);


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
}

