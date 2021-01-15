#include "Animal.h"

void Animal::movementController(Map &m_map)
{
	this->up = false; this->right = false; this->down = false; this->left = false;
	if ((m_map.getCurrentTile(this->getPosX() + 1, this->getPosY())==2)||(m_map.getCurrentTile(this->getPosX() + 1, this->getPosY()) == 3)) {
		if(this->getPosX()+1<49)
			this->right = true;
	}
	if ((m_map.getCurrentTile(this->getPosX() - 1, this->getPosY()) == 2) || (m_map.getCurrentTile(this->getPosX() - 1, this->getPosY()) == 3)) {
		if (this->getPosX() - 1 > 1)
			this->left = true;
	}
	if ((m_map.getCurrentTile(this->getPosX(), this->getPosY()+1) == 2) || (m_map.getCurrentTile(this->getPosX(), this->getPosY()+1) == 3)) {
		if (this->getPosY()+1 <  49)
		this->down = true;
	}
	if ((m_map.getCurrentTile(this->getPosX(), this->getPosY() - 1) == 2) || (m_map.getCurrentTile(this->getPosX(), this->getPosY() - 1) == 3)) {
		if (this->getPosY() - 1 >1)
		this->up = true;
	}

	
	
}

void Animal::moveAnimal()
{
	if (this->up) this->directions.push_back(n_up);
	if (this->down) this->directions.push_back(n_down);
	if (this->left) this->directions.push_back(n_left);
	if (this->right) this->directions.push_back(n_right);

	int randomDirection = rand() % this -> directions.size() + 0;


	if (this->directions[randomDirection] == 0) {
		this->m_velX = 0;
		this->m_velY = -12;
	}
	if (this->directions[randomDirection] == 1) {
		this->m_velX = 0;
		this->m_velY = 12;
	}
	if (this->directions[randomDirection] == 2) {
		this->m_velX = -12;
		this->m_velY = 0;
	}
	if (this->directions[randomDirection] == 3) {
		this->m_velX = 12;
		this->m_velY = 0;
	}
	
	this->directions.clear();
	
}
