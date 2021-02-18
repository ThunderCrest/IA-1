#pragma once

#include "Effector.h"
#include "Captor.h"
#include "Manor.h"
#include "AStarExploration.h"
#include "IterativeDeepeningSearch.h"
#include <vector>;

class nodes;
class Environment;

struct Beliefs { // toutes les croyances de l'agent
	Room * currentRoom;
	Manor* m_manor;
	std::vector<Room*> dustyRooms;
	std::vector<Room*> roomsWithJewel;
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
	Effector m_effector;
	Captor m_captor;

	bool m_bAlive;
	bool m_bUsingInformedMethod;

	AgentDesires currentDesire;

	time_t m_lastTickTime;
	time_t m_currentTickTime;

	int m_iterationsToExploration;
	int m_currentIterationsToExploration;

	AStarExploration aStar;
	IterativeDeepeningSearch IDS;

	std::vector<actions> intentions;


	void chooseDesire();

	void observe();

	void constructIntentions(std::vector<std::pair<Node*, goals>> targetNodes);

	actions chooseAction();

	std::vector<std::pair<Node*, goals>> exploration();

public:

	Agent(Manor* manor);

	Beliefs beliefs;

	Environment*environment;

	void setEnvironment(Environment& environment);

	void Run();

	void KillAgent() { m_bAlive = false; }

	void SwitchExplorationMethod();
};
