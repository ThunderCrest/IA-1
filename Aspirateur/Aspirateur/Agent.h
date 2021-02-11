#pragma once

#include "JewelPickupEffector.h"
#include "VacuumEffector.h"

class Manor;

class Agent
{
private:
	JewelPickupEffector m_jewelPickupEffector;
	VacuumEffector m_vacuumEffector;

	Manor* m_manor;

	bool m_bAlive;
	bool m_bUsingInformedMethod;

	time_t m_lastTickTime;
	time_t m_currentTickTime;

	int m_iterationsToExploration;
	int m_currentIterationsToExploration;

public:

	Agent(Manor* manor);

	void Run();

	void KillAgent() { m_bAlive = false; }

	void SwitchExplorationMethod();
};

