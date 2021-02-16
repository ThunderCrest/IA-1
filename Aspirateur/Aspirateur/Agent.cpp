#include "Agent.h"
#include "Manor.h"
#include "Node.h"
#include "Environment.h"
#include <cstdlib>


	Agent::Agent(Manor* manor) : m_effector(*this), m_captor(*this)
	{
		this->beliefs.m_manor = manor;
		beliefs.currentRoom = &this->beliefs.m_manor->getRoom(24);
		beliefs.currentRoom->setAgent(true);
		m_bAlive = true;
		m_bUsingInformedMethod = true;
		m_currentIterationsToExploration = 0;
		m_currentTickTime = 0;
		m_iterationsToExploration = 0;
		m_lastTickTime = 0;
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
					Node* targetNode = exploration();
					constructIntentions(targetNode);
					
				}
				
				actions chosenAction = chooseAction();
				m_effector.executeAction(chosenAction);
				

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


	void Agent::observe() {

		//update sa position
		//update les salles avec de la poussi�re
		//update les salles avec des bijoux
		//update sa mesure de performance
		//update la room ou il est
		//Choose Belief/intentions/desire
	}



	void Agent::constructIntentions(Node* node) { //chooseIntentions
		intentions.clear();
		while (node != nullptr)
		{
			if(node->actionToReach != actions::none)
			{
				intentions.insert(intentions.begin(), node->actionToReach);
			}
			node = node->parent;
		}
	};

	actions Agent::chooseAction()
	{
		if (intentions.size() > 0)
		{
			actions chosenAction = intentions.front();
			intentions.erase(intentions.begin());
			return chosenAction;
		}
		return actions::none;
	}

	std::vector<nodes*> Agent::expand() {

		//dépends des méthodes d'exploration
		//A*, IDS
		std::vector<nodes*> nodes;
		return nodes;
	}

	Node* Agent::exploration() {
		if(m_bUsingInformedMethod)
		{
			Problem problem;
			problem.startingRoom = beliefs.currentRoom;
			problem.manor = beliefs.m_manor;
			problem.targetRoom = &beliefs.m_manor->getRoom(2);
			return aStar.graphSearch(problem);
		}
		else
		{
			return nullptr;
		}
	}

	void Agent::setEnvironment(Environment& environment)
	{
		this->environment = &environment;
	}
