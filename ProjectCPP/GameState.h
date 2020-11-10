#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

#include "PathFinding.h"
#include "Dwarf.h"
#include "Map.h"
#include "Tree.h"
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

	//Map variables
	Map *map;
	sf::View m_view;
	const int grid_map_size = 12;

	PathFinding* pathSystem;

	//Objects
	std::vector<Dwarf*> dwarves;
	std::vector<Tree*> trees;
	
	std::vector<int> pathPosX; std::vector <int> pathPosY;

	sf::Clock gameClock;
	float gameTime;

	sf::Clock pathFindingClock;
	float pathTime;


};

#endif // !GAMESTATE_H