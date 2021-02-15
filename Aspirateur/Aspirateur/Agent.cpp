#include "Agent.h"
#include "Manor.h"
#include <cstdlib>


	Agent::Agent(Manor* manor) : m_effector(*this), m_captor(*this)
	{
		currentRoom = new Room(0, 0);
		this->m_manor = manor;
		m_bAlive = true;
		m_bUsingInformedMethod = true;
		m_currentIterationsToExploration = 0;
		m_currentTickTime = 0;
		m_iterationsToExploration = 0;
		m_lastTickTime = 0;
		currentBelief = AgentBeliefs::AGENTMOVING;
		currentDesire = AgentDesires::REST;
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

