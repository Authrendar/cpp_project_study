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


	void setTileToRemove();
	void setBuildingToBuild(); //no niezla nazwa funkcji XD
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
	Building* m_preparedBuilding;

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
	void builderUpdate();
	void cuttingTrees(Dwarf *dwarf);
	//void resetPathInstructions();
	//Dwarves variables
	
};

#endif // !GAMESTATE_H