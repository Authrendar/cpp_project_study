#include "PathFinding.h"

PathFinding::PathFinding(sf::RenderWindow* window, sf::Vector2u WINDOW_SIZE):window{window}
{
	this->WINDOW_SIZE = WINDOW_SIZE;

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


bool PathFinding::SolveAStar(int posX, int posY)
{
	
	std::cout << "Current pos of dwarf: " << posX << " : " << posY << std::endl;
		// reset navigation graph - default all node states
		for (int x = 0; x < nMapWidth; x++) { //TUTAJ TRZEBA ZMIENIC!!!
			for (int y = 0; y < nMapHeight; y++) {
				nodes[y * nMapWidth + x].bVisited = false;
				nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
				nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
				nodes[y * nMapWidth + x].parent = nullptr;			// No Parents
				if ((this->levelVec[y * nMapWidth + x] == 2)) {
					nodes[y * nMapWidth + x].bObstacle = false;
				}
				if ((this->levelVec[y * nMapWidth + x] == 1)) {
					//std::cout << x << " : " << y << std::endl;
					nodes[y * nMapWidth + x].bObstacle = true;

				}
				
				
				//if ((this->levelVec[y * nMapWidth + x] == 0) || (this->levelVec[y * nMapWidth + x] == 1))
					//nodes[y * nMapWidth + x].bObstacle = true;
				
				
			}
		}
		auto distance = [](sNode* a, sNode* b)	// for convenience
		{
			return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
		};

		auto heuristic = [distance](sNode* a, sNode* b)		// so we can experiment with heuristic 
		{
			return distance(a, b);
		};

		
		sNode* nodeCurrent = nodeStart;
		nodeStart->fLocalGoal = 0.f;
		nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

		// Add start node to not tested list - this will ensure it gets tested.
		// As the algorithm progress, newly discovered nodes get added to this list, and will themselves be tested later
		list<sNode*> listNotTestedNodes;
		listNotTestedNodes.push_back(nodeStart);

		// If the not tested list contains nodes, there may be better paths which not yet been explored.
		// However, we will also stop searching when we reach the target - there may well be better paths but this one will do - it won't be the longest
		while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)	// find absolutely shorest path // && nodeCurrent != nodeEnd)
		{
			// Sort untested nodes by global goal, so lowest it first
			listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

			// Front of listedNotTestedNodes is potentially the lowest distance node.
			// Our list may also contain nodes that have been visited, so ditch these...
			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();

			// ...or abort because there are no valid nodes left to test
			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true;	// We only explore a node once

			// Check each of this node's neighbors...
			for (auto nodeNeighbor : nodeCurrent->vecNeighbors) {
				// ... and only if the neighbor is not visted and is not an obstacle, add it to NotTested List
				
				if (!nodeNeighbor->bVisited && nodeNeighbor->bObstacle == 0)
				{
					listNotTestedNodes.push_back(nodeNeighbor);
				}

				// Calculate the neighbors potential lowest parent distance
				float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbor);

				// If choosing to path through this node is a lower distance than what the neighbor currently has set, update the neighbor to use this node
				// as the path source, and set its distance scores as necessary
				if (fPossiblyLowerGoal < nodeNeighbor->fLocalGoal) {
					nodeNeighbor->parent = nodeCurrent;
					nodeNeighbor->fLocalGoal = fPossiblyLowerGoal;

					// The best path length to the neighbor being tested has changed, so update the neighbor's score.
					// The heuristic is used to globally bias the path algorithm, so its knows if it's getter better or worse.
					// At some point the algorithm will realize this path is worse and abandon it, and then we go and search along the next best path.
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
				// We can also connect diagonally
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

