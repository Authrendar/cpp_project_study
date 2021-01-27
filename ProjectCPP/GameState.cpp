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

		
		for (auto& dwarf : dwarves) {

			//Reset paths
			if (this->resetPaths) {
				this->lumberjackUpdate(dwarf);
				this->resetPaths = false;
			}
			this->cuttingTrees(dwarf);
			this->setBuildingToBuild(dwarf);
			this->carryingWood(dwarf);
			dwarf->update(dt);
			if (dwarf->getIsSelected())
				this->m_interface->setDataFromDwarf(dwarf->getNumberOfDwarf(), dwarf->getDwarfHp(), dwarf->getCurrentJob(), dwarf->getCurrentState(), dwarf->getDwarfStrength(), dwarf->getDwarfLvl());
			dwarf->path_InstructionSolution();
			
		}
		for (auto& animal : animals) {
			animal->movementController(*this->map);
			animal->update(dt);
		}
		for (auto& bush : bushes) {
			this->m_cursor->setCurrentObject(*bush);
		}
		for (auto& building : this->buildings) {
			
			building->update(dt);
			this->m_cursor->setCurrentObject(*building);
				
		}
		
		this->setTileToRemove();
		
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
	
	for (auto& tree : trees) {
		tree->render(window);
	}
	for (auto& animal : animals) {
		animal->render(window);
	}
	
	for (auto& building : buildings) {
		building->render(window);
	}
	for (auto& dwarf : dwarves) {
		dwarf->render(window);
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
	

	
	
	pathSystem = new PathFinding();
	//this->pathSystem->setLevelData(this->map->getLevelData());

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
						this->lumberjackUpdate(dwarf);
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
						this->builderUpdate(dwarf);
						
					}
					else {
						dwarf->setDwarfJob(0);


					}
					this->keyPressClock.restart();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
					
					if (dwarf->getCurrentJob() != 4)
					{
						dwarf->setDwarfJob(4);
						this->porterUpdate(dwarf);

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
			
			for (int i = 0; i < trees.size(); i++) {
				if ((this->m_cursor->getPosX() == trees[i]->getPosX()) && (this->m_cursor->getPosY() == trees[i]->getPosY())) {
					trees.erase(trees.begin() + i);
				}
			}
			if(this->trees.size()<6)
				this->trees.push_back(new Tree(sf::Vector2f(this->m_cursor->getPosX() * this->grid_map_size, this->m_cursor->getPosY() * this->grid_map_size), 0));

			for(auto &dwarf: this->dwarves)
				if(dwarf->getCurrentJob()==1)
					this->lumberjackUpdate(dwarf);
			
		}

		
		this->m_cursor->setButtonQState(false);
		
	}

		if (this->m_cursor->getIsRButtonClicked()) {
			
			if (this->m_cursor->getCurrentTile() == 2) {

				if (this->m_cursor->getObjectCanBePlaced()) {
					if (this->buildings.size() < 4) {
						this->m_preparedBuilding = new Stock(sf::Vector2f(this->m_cursor->getPosX() * this->grid_map_size, this->m_cursor->getPosY() * this->grid_map_size), 0); // ostatnia liczba to typ skladu zapaso
						this->m_StockCounter++;
					}
					
					for (auto& dwarf : this->dwarves)
						this->builderUpdate(dwarf);
				}
			}
			
			this->m_cursor->setButtonRState(false);
			
				
		}
		this->m_cursor->setObjectCanBePlaced(true);

		if (this->m_cursor->getIsTButtonClicked()) {

			if (this->m_cursor->getCurrentTile() == 2) {

				this->m_cursor->setCurrnetTile(this->map->getCurrentTile(this->m_cursor->getPosX()+1, this->m_cursor->getPosY()+1));
				if (this->m_cursor->getCurrentTile() == 2) {
					

					if (this->m_cursor->getObjectCanBePlaced()) {
						if (this->buildings.size() < 4) {
							this->m_preparedBuilding = new Sawmill(sf::Vector2f(this->m_cursor->getPosX() * this->grid_map_size, this->m_cursor->getPosY() * this->grid_map_size));  
							this->m_SawmillCounter++;

						}

						for (auto& dwarf : this->dwarves)
							this->builderUpdate(dwarf);
					}
				}
			}

			this->m_cursor->setButtonTState(false);


		}
		
}

void GameState::setBuildingToBuild(Dwarf *dwarf)
{

	//Build the building
		if (dwarf->getCurrentJob() == 3) {
			if (this->m_preparedBuilding != nullptr) {
				bool canBeDestroyed = false;
				if ((this->m_preparedBuilding->getPosX() + 1 == int(dwarf->getPosX())) && (this->m_preparedBuilding->getPosY() == int(dwarf->getPosY())))
				{
					
					this->pathSystem->clearPathVector();
					canBeDestroyed = true;
					dwarf->setDwarfState(3);
					
				}
				if ((this->m_preparedBuilding->getPosX() - 1 == int(dwarf->getPosX())) && (this->m_preparedBuilding->getPosY() == int(dwarf->getPosY())))
				{
					this->pathSystem->clearPathVector();
					dwarf->setDwarfState(3);
					canBeDestroyed = true;

				}
				if ((this->m_preparedBuilding->getPosY() - 1 == int(dwarf->getPosY())) && (this->m_preparedBuilding->getPosX() == int(dwarf->getPosX())))
				{
					this->pathSystem->clearPathVector();
					dwarf->setDwarfState(3);
					canBeDestroyed = true;

				}
				if ((this->m_preparedBuilding->getPosY() + 1 ==int( dwarf->getPosY())) && (this->m_preparedBuilding->getPosX() == int(dwarf->getPosX())))
				{
					this->pathSystem->clearPathVector();
					dwarf->setDwarfState(3);
					canBeDestroyed = true;

				}

				if (canBeDestroyed) {
					this->m_preparedBuilding->setBuildingStatus(2);
					this->m_preparedBuilding->changeTexture(3);
					this->buildings.push_back(m_preparedBuilding);
					canBeDestroyed = false;
					
					this->m_preparedBuilding = nullptr;
					dwarf->setDwarfState(0);
				}
			}
	}


		
}

void GameState::porterUpdate(Dwarf* dwarf)
{
	if (dwarf->getCurrentJob() == 4) {
		//if (dwarf->isDwarfMustPutAway()) {
			dwarf->path_clearPathVec();
			dwarf->clearPathVec();

			for (int i = 0; i < buildings.size(); i++) {

				if (this->buildings[i]->getObjectType() == "Stock") {
					dwarf->setIsThereAnyStock(true);
					dwarf->setUpdateInstructions(true);
					dwarf->path_setMap(this->map->getLevelData());
					dwarf->path_setPositions(this->buildings[i]->getPosX(), this->buildings[i]->getPosY());
					dwarf->path_findPath(this->m_StockCounter);
					if (i == this->m_StockCounter) {
						dwarf->setUpdateInstructions(false);
					}
				}
				else
					dwarf->setIsThereAnyStock(false);
			}
		}

	if (dwarf->getCurrentJob() == 4) {
		if (dwarf->isDwarfMustPutAway()) {
		dwarf->path_clearPathVec();
		dwarf->clearPathVec();

		for (int i = 0; i < buildings.size(); i++) {

			if (this->buildings[i]->getObjectType() == "Sawmill") {
				std::cout << "instrukcja do sawmill\n";
				dwarf->setUpdateInstructions(true);
				dwarf->path_setMap(this->map->getLevelData());
				dwarf->path_setPositions(this->buildings[i]->getPosX(), this->buildings[i]->getPosY());
				dwarf->path_findPath(this->m_SawmillCounter);
				if (i == this->m_SawmillCounter) {
					dwarf->setUpdateInstructions(false);
				}
			}
			
		}
	}
	}
}

void GameState::carryingWood(Dwarf* dwarf)
{
	if (dwarf->getCurrentJob() == 4) {
		if (!dwarf->isDwarfMustPutAway()) {
			for (auto& stock : this->buildings) {
				if (stock->getObjectType() == "Stock") {
					stock->checkIfDwarfNextToBuilding(*dwarf);
					
					if (stock->getIsDwarfNextToBuilding()) {
						
						if (stock->getBuildingGoods() >= 20) {
							dwarf->setWoodValue(20);
							dwarf->setWoodValue(stock->getBuildingGoods());
							this->m_interface->updateWoodValue(-stock->getBuildingGoods());
							stock->setBuildingGoods(-dwarf->getWoodValue(), 0);
						}
						if (stock->getBuildingGoods() < 20) {
							dwarf->setWoodValue(stock->getBuildingGoods());
							this->m_interface->updateWoodValue(-stock->getBuildingGoods());
							stock->setBuildingGoods(-dwarf->getWoodValue(), 0);
						}
						

						this->porterUpdate(dwarf);
					}
				}
			}
		}
	}
	
	
}

void GameState::lumberjackUpdate(Dwarf* dwarf)
{
	//Finding path for trees
	if (dwarf->getCurrentJob() == 1) {
		if (!dwarf->isDwarfMustPutAway()) {
			dwarf->path_clearPathVec();
			dwarf->clearPathVec();

			for (int i = 0; i < trees.size(); i++) {

				dwarf->setUpdateInstructions(true);
				dwarf->path_setMap(this->map->getLevelData());
				dwarf->path_setPositions(int(trees[i]->getPosX()), int(trees[i]->getPosY()));
				dwarf->path_findPath(trees.size());
				if (i == trees.size() - 1) {
					dwarf->setUpdateInstructions(false);
				}

			}

		}
	}
	
	//Finding path for stockpile
	if (dwarf->getCurrentJob() == 1) {
		if (dwarf->isDwarfMustPutAway()) {
			dwarf->path_clearPathVec();
			dwarf->clearPathVec();
			
			for (int i = 0; i<buildings.size(); i++) {

				if (this->buildings[i]->getObjectType() == "Stock") {
					dwarf->setIsThereAnyStock(true);
					dwarf->setUpdateInstructions(true);
					dwarf->path_setMap(this->map->getLevelData());
					dwarf->path_setPositions(this->buildings[i]->getPosX(), this->buildings[i]->getPosY());
					dwarf->path_findPath(this->m_StockCounter);
					if (i == this->m_StockCounter) {
						dwarf->setUpdateInstructions(false);
					}
				}
				else
					dwarf->setIsThereAnyStock(false);
			}
		}
	}
}

void GameState::builderUpdate(Dwarf *dwarf)
{
		if (dwarf->getCurrentJob() == 3) {
			if (this->m_preparedBuilding != nullptr) {
				dwarf->path_clearPathVec();
				dwarf->clearPathVec();

				dwarf->setUpdateInstructions(true);
				dwarf->path_setMap(this->map->getLevelData());
				dwarf->path_setPositions(this->m_preparedBuilding->getPosX(), this->m_preparedBuilding->getPosY());
				dwarf->path_findPath(1);
				dwarf->setUpdateInstructions(false);
			}
		}
}

void GameState::cuttingTrees(Dwarf *dwarf)
{	
		if (!dwarf->isDwarfMustPutAway()) {
			if (dwarf->getCurrentJob() == 1) {
				if (trees.size() > 0) {
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
							dwarf->setWoodValue(trees[i]->getValueOfWood());

							this->trees.erase(trees.begin() + i);
							this->resetPaths = true;
							this->lumberjackUpdate(dwarf);
							dwarf->setDwarfState(1);
							indexVec.clear();


						}


					}
					if (trees.size() == 0)
						dwarf->setDwarfState(0);
				}
				else
					dwarf->setDwarfState(0);


			}
		}

		if ((dwarf->isDwarfMustPutAway())&&(dwarf->getIsThereAnyStock()))
				dwarf->setDwarfState(1);

		//Check if dwarf is next to stock
		
			for (auto& stock : this->buildings) {

				if (stock->getObjectType() == "Stock") {
					stock->checkIfDwarfNextToBuilding(*dwarf);

					if (stock->getIsDwarfNextToBuilding()) {
						if (dwarf->getCurrentJob() == 1) {
						this->m_interface->updateWoodValue(dwarf->getWoodValue());
						stock->setBuildingGoods(dwarf->getWoodValue(), 1);
						dwarf->resetWoodValue();
						//dwarf->setUpdateInstructions(true);

						this->lumberjackUpdate(dwarf);
						stock->setLevelTypeOfBuilding(0);
						stock->changeLevelTypeTexture();
						
						}
				}
			}
		}
}

