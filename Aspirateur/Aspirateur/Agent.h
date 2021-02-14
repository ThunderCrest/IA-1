#pragma once

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

	Manor* m_manor;

	bool m_bAlive;
	bool m_bUsingInformedMethod;

	AgentBeliefs currentBelief;

	AgentDesires currentDesire;

	time_t m_lastTickTime;
	time_t m_currentTickTime;

	int m_iterationsToExploration; 
	int m_currentIterationsToExploration;

	std::vector<Room*> dirtyRooms;
	std::vector<Room*> jewelRooms;

public:

	Agent(Manor* manor);

	void run();

	void killAgent() { m_bAlive = false; }

	void switchExplorationMethod();

	void chooseDesire();

	void choseeBelief();

	void getCurrentRoom();
	
	void getDestination();

	void observe();
	
	std::vector<actions> constructSolution();

	std::vector<nodes*> expand();

	void treeSearch();
};

