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

	void toggleDiagnols();
	bool SolveAStar();

	void update();

	//float d = 0.f;
	void drawMap();


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

	sf::Vector2u WINDOW_SIZE;
	int nMapWidth;
	int nMapHeight;


	int *mainlevelData;

	const int nNodeSize = 10; //32
	//const int nNodeBorder = 9; //9
	sNode* nodes = nullptr;
	sNode* nodeStart = nullptr;
	sNode* nodeEnd = nullptr;


	
	sf::Vector2i mousePos;

	sf::RenderWindow* window = nullptr;

	bool b8Connection = false;


};


