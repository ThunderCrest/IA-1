#pragma once

#include "Effector.h"
#include "Captor.h"
#include "Manor.h"
#include "AStarExploration.h"
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

enum class goals {
	vacuum,
	pickupJewel
};

class Agent
{
private:
	/*
	JewelPickupEffector m_jewelPickupEffector;
	VacuumEffector m_vacuumEffector;
	*/
	Effector m_effector;
	Captor m_captor;

	bool m_bAlive;
	bool m_bUsingInformedMethod;

	AgentBeliefs currentBelief;

	AgentDesires currentDesire;

	time_t m_lastTickTime;
	time_t m_currentTickTime;

	int m_iterationsToExploration;
	int m_currentIterationsToExploration;

	AStarExploration aStar;

	std::vector<actions> intentions;


	void chooseDesire();

	void choseeBelief();

	void getDestination();

	void observe();

	void constructIntentions(Node* node);

	actions chooseAction();

	std::vector<nodes*> expand();

	Node* treeSearch();

public:
	Manor* m_manor;
	Room* currentRoom;

	Agent(Manor* manor);

	void Run();

	void KillAgent() { m_bAlive = false; }

	void SwitchExplorationMethod();
};
