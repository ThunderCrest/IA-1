#include "Agent.h"
#include "Manor.h"
#include <cstdlib>


Agent::Agent(Manor* manor)
{
	this->m_manor = manor;
	m_bAlive = true;
	m_bUsingInformedMethod = true;
	m_currentIterationsToExploration = 0;
	m_currentTickTime = 0;
	m_iterationsToExploration = 0;
	m_lastTickTime = 0;
	currentBelief= AgentBeliefs::AGENTMOVING;
	currentDesire = AgentDesires::REST;
}

void Agent::run()
{
	this->m_lastTickTime = -1;
	while(m_bAlive)
	{
		time(&this->m_currentTickTime);
		if(this->m_currentTickTime - this->m_lastTickTime > 0)
		{
			this->m_lastTickTime = this->m_currentTickTime;
			//std::cout << m_lastTickTime << std::endl;
		    
		    if(this->m_currentIterationsToExploration >= this->m_iterationsToExploration)
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

void Agent::switchExplorationMethod()
{
	m_bUsingInformedMethod = !m_bUsingInformedMethod;
	if(m_bUsingInformedMethod)
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

void Agent::choseeBelief(){
}

void Agent::getCurrentRoom() {

}

void Agent::observe() {

	//update sa position
	//update les salles avec de la poussière
	//update les salles avec des bijoux
	//update sa mesure de performance
	//Choose Belief/intentions/desire
}



std::vector<actions> Agent::constructSolution() { //chooseIntentions
	return std::vector<actions>();
};



class nodes; //à créer

std::vector<nodes*> Agent::expand() {

	//dépends des méthodes d'exploration
	//A*, IDS
	return std::vector<nodes*>();
}

void Agent::treeSearch() {
	//use expand
}