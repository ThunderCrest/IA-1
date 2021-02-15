#include "Effector.h"
#include "Agent.h"


	Effector::Effector(Agent &agent) 
	{
		this->_agent = &agent;
	}

	void Effector::executeAction(actions action)
	{
		switch (action)
		{
		case actions::goRight:
			goRight();
			break;
		case actions::goLeft:
			goLeft();
			break;
		case actions::goTop:
			goTop();
			break;
		case actions::goBottom:
			goBottom();
			break;
		case actions::pick:
			pick();
			break;
		case actions::aspirate:
			aspirate();
			break;
		default:
			break;
		}
	}

	void Effector::executeActions(std::vector<actions> &actions) {
		for (auto& action : actions)
		{
			executeAction(action);
		}

	}

	void Effector::goRight() {
		if (this->_agent->currentRoom->getX() < 4) //sinon on est sur le bord de la grille
		{
			this->_agent->currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->currentRoom->getX() + 5*this->_agent->currentRoom->getY();
			if (index+1 < 25)
			{
				this->_agent->currentRoom = &this->_agent->m_manor->getRoom(index+1);
				this->_agent->currentRoom->setAgent(true);

			}
		}
		
	}
	void Effector::goLeft() {
		if (this->_agent->currentRoom->getX() > 0) //sinon on est sur le bord de la grille
		{
			this->_agent->currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->currentRoom->getX() + 5 * this->_agent->currentRoom->getY();
			if (index - 1 < 25 && index -1 >= 0)
			{
				this->_agent->currentRoom = &this->_agent->m_manor->getRoom(index - 1);
				this->_agent->currentRoom->setAgent(true);
			}
		}
	}
	void Effector::goTop() {
		if (this->_agent->currentRoom->getY() > 0 ) //sinon on est sur le bord de la grille
		{
			this->_agent->currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->currentRoom->getX() + 5 * this->_agent->currentRoom->getY();
			if (index-5 < 25 && index-5 >=0)
			{
				this->_agent->currentRoom = &this->_agent->m_manor->getRoom(index -5);
				this->_agent->currentRoom->setAgent(true);

			}
		}
	}
	void Effector::goBottom() {
		if (this->_agent->currentRoom->getY() < 4) //sinon on est sur le bord de la grille
		{
			this->_agent->currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->currentRoom->getX() + 5 * this->_agent->currentRoom->getY();
			if (index + 5 < 25)
			{
				this->_agent->currentRoom = &this->_agent->m_manor->getRoom(index + 5);
				this->_agent->currentRoom->setAgent(true);
			}
		}
	}
	void Effector::aspirate() {
		this->_agent->currentRoom->setDirt(false);
		this->_agent->currentRoom->setJewel(false);

	}
	void Effector::pick() {
		this->_agent->currentRoom->setJewel(false);
	}