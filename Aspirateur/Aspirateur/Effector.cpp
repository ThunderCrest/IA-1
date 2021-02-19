#include "Effector.h"
#include "Agent.h"
#include "Environment.h"

	Effector::Effector(Agent &agent) 
	{
		this->_agent = &agent; //ajouter environnement
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
		if (this->_agent->beliefs.currentRoom->getX() < 4) //sinon on est sur le bord de la grille
		{
			this->_agent->beliefs.currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->beliefs.currentRoom->getX() + 5*this->_agent->beliefs.currentRoom->getY();
			if (index+1 < 25)
			{
				this->_agent->environment->increaseScore();
				this->_agent->beliefs.currentRoom = &this->_agent->beliefs.m_manor->getRoom(index+1);
				this->_agent->beliefs.currentRoom->setAgent(true);
			}
		}
		
	}
	void Effector::goLeft() {
		if (this->_agent->beliefs.currentRoom->getX() > 0) //sinon on est sur le bord de la grille
		{
			this->_agent->beliefs.currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->beliefs.currentRoom->getX() + 5 * this->_agent->beliefs.currentRoom->getY();
			if (index - 1 < 25 && index -1 >= 0)
			{
				this->_agent->environment->increaseScore();
				this->_agent->beliefs.currentRoom = &this->_agent->beliefs.m_manor->getRoom(index - 1);
				this->_agent->beliefs.currentRoom->setAgent(true);
			}
		}
	}
	void Effector::goTop() {
		if (this->_agent->beliefs.currentRoom->getY() > 0 ) //sinon on est sur le bord de la grille
		{
			this->_agent->beliefs.currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->beliefs.currentRoom->getX() + 5 * this->_agent->beliefs.currentRoom->getY();
			if (index-5 < 25 && index-5 >=0)
			{
				this->_agent->environment->increaseScore();
				this->_agent->beliefs.currentRoom = &this->_agent->beliefs.m_manor->getRoom(index -5);
				this->_agent->beliefs.currentRoom->setAgent(true);
			}
		}
	}
	void Effector::goBottom() {
		if (this->_agent->beliefs.currentRoom->getY() < 4) //sinon on est sur le bord de la grille
		{
			this->_agent->beliefs.currentRoom->setAgent(false); //Il n'est plus dans la pièce
			int index = this->_agent->beliefs.currentRoom->getX() + 5 * this->_agent->beliefs.currentRoom->getY();
			if (index + 5 < 25)
			{
				//gain de point car on fait une action
				this->_agent->environment->increaseScore();
				this->_agent->beliefs.currentRoom = &this->_agent->beliefs.m_manor->getRoom(index + 5);
				this->_agent->beliefs.currentRoom->setAgent(true);
			}
		}
	}
	void Effector::aspirate() {
		if (this->_agent->beliefs.currentRoom->getDirt()) {
			//perte de point car on nettoie ( c'est bien )
			this->_agent->environment->decreaseScore(3);
			//gain de point parce que l'on fait une action
			this->_agent->environment->increaseScore();

			this->_agent->beliefs.currentRoom->setDirt(false);
			if (this->_agent->beliefs.currentRoom->getJewel()) {
				//gain de point ( c'est pas bien )
				this->_agent->environment->increaseScore();

				this->_agent->beliefs.currentRoom->setJewel(false);
			}
		}


	}
	void Effector::pick() {
		if (this->_agent->beliefs.currentRoom->getJewel())
		{
			//perte de point ( c'est bien )
			this->_agent->environment->decreaseScore(2);
			this->_agent->beliefs.currentRoom->setJewel(false);
		}
	}