#pragma once

#include "Effector.h"
#include "Captor.h"
#include "Manor.h"
#include "AStarExploration.h"
#include <vector>;

class nodes;
class Environment;

struct Beliefs { // toutes les croyances de l'agent
	Room * currentRoom;
	Manor* m_manor;
	std::vector<Room> dustyRooms;
	std::vector<Room> roomsWithJewel;
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

	std::vector<actions> intentions;


	void chooseDesire();

	void getDestination();

	void observe();

	void constructIntentions(Node* node);

	actions chooseAction();

	std::vector<nodes*> expand();

	Node* exploration();

public:

	Agent(Manor* manor);

	Beliefs beliefs;

	Environment*environment;

	void setEnvironment(Environment& environment);

	void Run();

	void KillAgent() { m_bAlive = false; }

	void SwitchExplorationMethod();
};
