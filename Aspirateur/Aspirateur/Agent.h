#pragma once

#include "JewelPickupEffector.h"
#include "VacuumEffector.h"
#include "Manor.h"
#include <vector>;

class nodes;

enum class AgentBeliefs {
	AGENTMOVING,
	AGENTCLEANING,
	AGENTPICKING
};

enum class AgentDesires {
	CLEAN,
	REST
};

enum class actions { //à mettre dans effecteur
	goRight,
	aspirate,
	pick,
}; //puis executeAction(actions) dans effecteur;

class Agent
{
private:
	JewelPickupEffector m_jewelPickupEffector;
	VacuumEffector m_vacuumEffector;

	Manor* m_manor;

	bool m_bAlive;
	bool m_bUsingInformedMethod;

	AgentBeliefs currentBelief;

	AgentDesires currentDesire;

	time_t m_lastTickTime;
	time_t m_currentTickTime;

	int m_iterationsToExploration; 
	int m_currentIterationsToExploration;

public:

	Agent(Manor* manor);

	void Run();

	void KillAgent() { m_bAlive = false; }

	void SwitchExplorationMethod();

	void chooseDesire();

	void choseeBelief();

	void getCurrentRoom();
	
	void getDestination();

	void observe();
	
	std::vector<actions> constructSolution();

	std::vector<nodes*> expand();

	void treeSearch();
};

