#include "PathFinding.h"

PathFinding::PathFinding(sf::RenderWindow* window, sf::Vector2u WINDOW_SIZE):window{window}
{
	this->WINDOW_SIZE = WINDOW_SIZE;

	this->nMapWidth = WINDOW_SIZE.x / 80;
	this->nMapHeight = WINDOW_SIZE.y / 75;

	
	nodes = new sNode[nMapWidth * nMapHeight];
	
	std::cout << nMapWidth * nMapHeight << std::endl;
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

void PathFinding::setLevelData(std::vector<int> map)
{
	for (int i = 0; i < map.size(); i++) {
		this->levelVec.push_back(map[i]);
	}
}

void PathFinding::setStartEndNodes(int x1, int y1, int x2, int y2)
{
	this->nodeStart = &nodes[y1 * 10 + x1];
	this->nodeEnd = &nodes[y2 * 10 + x2];
	
}

/*void PathFinding::toggleDiagnols()
{
	for (auto x = 0; x < nMapWidth; x++) {
		for (auto y = 0; y < nMapHeight; y++) {
			nodes[y * nMapWidth + x].x = x;		// ...because we give each node its own coordinates
			nodes[y * nMapWidth + x].y = y;
			nodes[y * nMapWidth + x].bObstacle = nodes[y * nMapWidth + x].bObstacle;
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;
			nodes[y * nMapWidth + x].vecNeighbors.clear();

		}
	}
	// Create connections - in this case nodes are on a regular grid
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

			// if diagnals are included
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
}*/

bool PathFinding::SolveAStar()
{
		// reset navigation graph - default all node states
		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				nodes[y * nMapWidth + x].bVisited = false;
				nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
				nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
				nodes[y * nMapWidth + x].parent = nullptr;			// No Parents


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

void PathFinding::update()
{
	if (nodeEnd != nullptr) {
		sNode* p = nodeEnd;
		int counter = 0;
		while (p->parent != nullptr) {


			/*sf::Vertex line[]
			{
				sf::Vertex(sf::Vector2f(p->x * this->nNodeSize + this->nNodeSize / 2 + 3, p->y * this->nNodeSize + this->nNodeSize / 2 + 3)),
				sf::Vertex(sf::Vector2f(p->parent->x * this->nNodeSize + this->nNodeSize / 2 + 3, p->parent->y * this->nNodeSize + this->nNodeSize / 2 + 3))
			};
			line->color = sf::Color{ 255,218,185,255 };

			//this->window->draw(line, 2, sf::Lines);

			// Set next node to this node's parent */
	
			//std::cout << "pxy: " << p->x<<":"<<p->y << ", ";
			//std::cout << "parentx: " << p->parent->x <<":" <<p->parent->y <<", " << std::endl;
			//std::cout << this->nodeStart->x << std::endl;
			/*if ((p->parent->x != nodeStart->x)&&(!p->parent->y != nodeStart->y)) {
				this->posX.push_back(p->parent->x);
				this->posY.push_back(p->parent->y);
				//std::cout << p->parent->x << std::endl;
				//std::cout << p->parent->y << std::endl;
				std::cout << "parentx: " << p->parent->x << ":" << p->parent->y << ", " << std::endl;
			}
			*/
			
			counter++;
			if ((p->x != nodeStart->x) || (p->y != nodeStart->y))
			{
				std::cout << "x: " << p->x << "| y: " << p->y << std::endl;
				this->posX.push_back(p->x);
				this->posY.push_back(p->y);
				//std::cout << "X: " << p->x << std::endl;
			}
			
			p = p->parent;
		}

		std::cout << std::endl;
		//std::cout << this->posX.size() << std::endl;
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

void PathFinding::drawMap()
{
	// Draw Nodes on top

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		SolveAStar();
	}

	
}