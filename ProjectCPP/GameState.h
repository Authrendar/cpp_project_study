#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Interface.h"
//#include "PathFinding.h"
#include "Dwarf.h"
#include "Map.h"
#include "Tree.h"
#include "Cursor.h"
#include "Animal.h"
#include "Beaver.h"
#include "Bushes.h"
#include "Stock.h"
#include "Sawmill.h"
class GameState :
	public State
{
public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();
	void endState();

	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);


private:

	//Init functions
	void initMap();
	void initObjects();
	void keyboardUpdate();


	
	//Map variables
	Map *map;
	sf::View *m_view;
	const int grid_map_size = 12;

	PathFinding* pathSystem;
	std::vector<PathFinding*> pathSystemVec;
	//Objects
	std::vector<Dwarf*> dwarves;
	std::vector<Tree*> trees;
	std::vector<Animal*> animals;
	std::vector<Bushes*> bushes;
	std::vector<PathFinding*> vec_pathSystem;
	std::vector<Building*> buildings;
	Building* m_preparedBuilding;



	//Counters
	
	int m_StockCounter = 0;
	int m_SawmillCounter = 0;
	//Interface
	Interface* m_interface;

	Cursor *m_cursor;
	sf::Clock gameClock;

	
	float gameTime;

	sf::Clock pathFindingClock;
	float pathTime;


	sf::Clock keyPressClock;
	float keyPressTime;

	void lumberjackUpdate(Dwarf *dwarf);
	void builderUpdate(Dwarf *dwarf);
	void cuttingTrees(Dwarf *dwarf);
	void setTileToRemove();
	void setBuildingToBuild(Dwarf *dwarf); //no niezla nazwa funkcji XD
	void porterUpdate(Dwarf* dwarf);
	void carryingWood(Dwarf* dwarf);
	//void resetPathInstructions();
	//Dwarves variables
	bool resetPaths = false;
	
};

#endif // !GAMESTATE_H