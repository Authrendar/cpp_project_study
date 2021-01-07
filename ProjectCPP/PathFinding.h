#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
#include <utility>

using namespace std;



class PathFinding {
public:
	
	PathFinding(sf::RenderWindow* window, sf::Vector2u WINDOW_SIZE);

	void setLevelData(std::vector<int> map);
	void setStartEndNodes(int x1, int y1, int x2, int y2);
	void setObstacleNode(int posX, int posY);

	bool SolveAStar(int nMapWidth, int nMapHeight);

	void updateDataLevel();

	void update();
	void clearPathVector();

	std::vector<int> getPathPosX(); //{ return this->posX; }
	std::vector<int> getPathPosY(); //{ return this->posY; }
	//float d = 0.f;


private:
	struct sNode {
		bool bObstacle = false; //czy wezel jest przeszkoda
		bool bVisited = false; //Czy wezel zostal przeszukany
		float fGlobalGoal; //Odleglosc punktu do drugiego punktu w lini prostej???
		float fLocalGoal; //odleglosc do celu poprzez obranie alternatywnej trasy
		int x;
		int y;
		std::vector<sNode*>vecNeighbors;
		sNode* parent;
	};
	std::vector<int>levelVec;
	std::vector<int>posX; std::vector<int>posY;

	int dwarfPosX, dwarfPosY;
	sf::Vector2u WINDOW_SIZE;
	int nMapWidth;
	int nMapHeight;


	

	const int nNodeSize = 4; //32
	//const int nNodeBorder = 9; //9
	sNode* nodes = nullptr;
	sNode* nodeStart = nullptr;
	sNode* nodeEnd = nullptr;


	
	sf::Vector2i mousePos;

	sf::RenderWindow* window = nullptr;

	bool b8Connection = false;


};


