#include "Agent.h"
#include "Manor.h"
#include "Node.h"
#include <cstdlib>


	Agent::Agent(Manor* manor) : m_effector(*this), m_captor(*this)
	{
		this->m_manor = manor;
		currentRoom = &this->m_manor->getRoom(24);
		m_bAlive = true;
		m_bUsingInformedMethod = true;
		m_currentIterationsToExploration = 0;
		m_currentTickTime = 0;
		m_iterationsToExploration = 0;
		m_lastTickTime = 0;
		currentBelief = AgentBeliefs::AGENTMOVING;
		currentDesire = AgentDesires::REST;

		Problem problem;
		problem.manor = manor;
		problem.startingRoom = currentRoom;
		problem.targetRoom = &this->m_manor->getRoom(13);

		Node* currentNode = aStar.graphSearch(problem);
		while(currentNode != nullptr)
		{
			intentions.insert(intentions.begin(), currentNode->actionToReach);
			currentNode = currentNode->parent;
		}
	}

	void Agent::Run()
	{
		this->m_lastTickTime = -1;
		while (m_bAlive)
		{
			time(&this->m_currentTickTime);
			if (this->m_currentTickTime - this->m_lastTickTime > 0)
			{
				this->m_lastTickTime = this->m_currentTickTime;
				//std::cout << m_lastTickTime << std::endl;
				//std::cout << this->m_captor.getCurrentRoomIndex() << std::endl;
				if (this->m_currentIterationsToExploration >= this->m_iterationsToExploration)
				{
					this->m_currentIterationsToExploration = 0;
					//Observe
					//Explore TreeSearch
					//Do it
					if(intentions.size() > 0)
					{
						m_effector.executeAction(intentions.front());
						intentions.erase(intentions.begin());
					}
				}



				this->m_currentIterationsToExploration++;
			}
		}
	}

	void Agent::SwitchExplorationMethod()
	{
		m_bUsingInformedMethod = !m_bUsingInformedMethod;
		if (m_bUsingInformedMethod)
		{
			std::cout << "Using Informed" << std::endl;
		}
		else
		{
			std::cout << "Using Uninformed" << std::endl;
		}
	}




	void Agent::chooseDesire() {

	}

	void choseeBelief() {
	}

	void Agent::observe() {

		//update sa position
		//update les salles avec de la poussi�re
		//update les salles avec des bijoux
		//update sa mesure de performance
		//update la room ou il est
		//Choose Belief/intentions/desire
	}



	std::vector<actions> Agent::constructSolution() { //chooseIntentions
		std::vector<actions> actionsToDo;
		actionsToDo.push_back(actions::aspirate);
		return actionsToDo;
	};

	std::vector<nodes*> Agent::expand() {

		//dépends des méthodes d'exploration
		//A*, IDS
		std::vector<nodes*> nodes;
		return nodes;
	}

	void Agent::treeSearch() {
		//use expand
	}

