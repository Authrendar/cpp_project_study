#include "PathFinding.h"

PathFinding::PathFinding()
{
	//this->WINDOW_SIZE = WINDOW_SIZE;

	this->nMapWidth = 50; //Width of map title, now window 
	this->nMapHeight = 50; // same here but height

	this->updateDataLevel();
	
}

void PathFinding::setLevelData(std::vector<int> map)
{
	this->levelVec.clear();

	for (int i = 0; i < map.size(); i++) {
		this->levelVec.push_back(map[i]);
	}
	
}


void PathFinding::setStartEndNodes(int x1, int y1, int x2, int y2)
{
	this->nodeStart = &nodes[y1 * 50 + x1];
	this->nodeEnd = &nodes[y2 * 50 + x2];
	
}

void PathFinding::setObstacleNode(int posX, int posY)
{
	this->dwarfPosX = posX;
	this->dwarfPosY = posY;
}


bool PathFinding::SolveAStar()
{
	
	//std::cout << "Current pos of dwarf: " << posX << " : " << posY << std::endl;
		// reset navigation graph - default all node states
		for (int x = 0; x < nMapWidth; x++) { //TUTAJ TRZEBA ZMIENIC!!!
			for (int y = 0; y < nMapHeight; y++) {
				nodes[y * nMapWidth + x].bVisited = false;
				nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
				nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
				nodes[y * nMapWidth + x].parent = nullptr;			
				if ((this->levelVec[y * nMapWidth + x] == 2)) {
					nodes[y * nMapWidth + x].bObstacle = false;
				}
				if ((this->levelVec[y * nMapWidth + x] == 1)) {
					//std::cout << x << " : " << y << std::endl;
					nodes[y * nMapWidth + x].bObstacle = true;

				}
				if ((this->levelVec[y * nMapWidth + x] == 4)) {
					//std::cout << x << " : " << y << std::endl;
					nodes[y * nMapWidth + x].bObstacle = true;

				}
				
				
				
				//if ((this->levelVec[y * nMapWidth + x] == 0) || (this->levelVec[y * nMapWidth + x] == 1))
					//nodes[y * nMapWidth + x].bObstacle = true;
				
				
			}
		}
		auto distance = [](sNode* a, sNode* b)	
		{
			return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
		};

		auto heuristic = [distance](sNode* a, sNode* b)	
		{
			return distance(a, b);
		};

		
		sNode* nodeCurrent = nodeStart;
		nodeStart->fLocalGoal = 0.f;
		nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

		
		list<sNode*> listNotTestedNodes;
		listNotTestedNodes.push_back(nodeStart);

		while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)	//szukanie najkrotszej sciezki path // && nodeCurrent != nodeEnd)
		{
			
			listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

			
			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();

			

			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true;	

			
			for (auto nodeNeighbor : nodeCurrent->vecNeighbors) {
				
				
				if (!nodeNeighbor->bVisited && nodeNeighbor->bObstacle == 0)
					listNotTestedNodes.push_back(nodeNeighbor);
				

				float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbor);

				if (fPossiblyLowerGoal < nodeNeighbor->fLocalGoal) {
					nodeNeighbor->parent = nodeCurrent;
					nodeNeighbor->fLocalGoal = fPossiblyLowerGoal;
					nodeNeighbor->fGlobalGoal = nodeNeighbor->fLocalGoal + heuristic(nodeNeighbor, nodeEnd);
				}


			}
		}

		return true;
}

void PathFinding::updateDataLevel()
{
	nodes = new sNode[nMapWidth * nMapHeight];

	//std::cout << nMapWidth * nMapHeight << std::endl;
	for (auto x = 0; x < nMapWidth; x++) {
		for (auto y = 0; y < nMapHeight; y++) {
			nodes[y * nMapWidth + x].x = x;
			nodes[y * nMapWidth + x].y = y;
			nodes[y * nMapWidth + x].bObstacle = false;
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;

		}
	}


	for (auto x = 0; x < nMapWidth; x++) {
		for (auto y = 0; y < nMapHeight; y++) {
			if (y > 0)
				nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
			if (y < nMapHeight - 1)
				nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
			if (x > 0)
				nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
			if (x < nMapWidth - 1)
				nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);



			if (b8Connection) {
				
				if (y > 0 && x > 0)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
				if (y < nMapHeight - 1 && x>0)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
				if (y > 0 && x < nMapWidth - 1)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
				if (y < nMapHeight - 1 && x < nMapWidth - 1)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
			}
		}
	}
}

void PathFinding::update()
{

	if (nodeEnd != nullptr) {
		
		sNode* p = nodeEnd;
		while (p->parent != nullptr) {
			
			if ((p->x != nodeStart->x) || (p->y != nodeStart->y))
			{
				this->posX.push_back(p->x);
				this->posY.push_back(p->y);
			}
			p = p->parent;
		}
	}
}

void PathFinding::clearPathVector()
{
	this->posX.clear();
	this->posY.clear();
}


std::vector<int> PathFinding::getPathPosX()
{
	return this->posX;
}

std::vector<int> PathFinding::getPathPosY()
{
	return this->posY;
}

