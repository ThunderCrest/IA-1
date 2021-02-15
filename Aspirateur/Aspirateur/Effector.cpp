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
			this->_agent->currentRoom->setAgent(0); //Il n'est plus dans la pièce
			int index = this->_agent->currentRoom->getX() + 5*this->_agent->currentRoom->getY();
			if (index < 25)
			{
				this->_agent->currentRoom = &this->_agent->m_manor->getRooms()[index];
			}
		}
		
	}
	void Effector::goLeft() {

	}
	void Effector::goTop() {

	}
	void Effector::goBottom() {

	}
	void Effector::aspirate() {

	}
	void Effector::pick() {

	}