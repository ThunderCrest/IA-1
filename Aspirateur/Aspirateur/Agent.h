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
	int performanceMesure;
	int lastPerformanceMesure;
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
	bool m_bFirstIterationDone;

	AgentDesires currentDesire;

	time_t m_lastTickTime;
	time_t m_currentTickTime;

	int m_iterationsToExploration;
	int m_previousIterationsToExploration;
	int m_currentIterationsToExploration;
	int m_minIterations;
	int m_maxIterations;
	int m_iterationModifier;

	int m_currentIterationsToLearning;
	int m_iterationsToLearning;

	AStarExploration aStar;
	IterativeDeepeningSearch IDS;

	std::vector<actions> intentions;


	void updateState();

	void updateIterationsAmount();

	void observe();

	void constructIntentions(std::vector<std::pair<Node*, goals>> targetNodes);

	actions chooseAction();

	std::vector<std::pair<Node*, goals>> exploration();

public:

	Agent(Manor* manor);

	Beliefs beliefs;

	Environment*environment;

	void setEnvironment(Environment& environment);

	void run();

	void killAgent() { m_bAlive = false; }

	void switchExplorationMethod();

	bool getFirstIterationDone() { return m_bFirstIterationDone; }

	bool getUsingInformedMethod() { return m_bUsingInformedMethod; }

	int getIterationsToExploration() { return m_iterationsToExploration; }
};
