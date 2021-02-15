#pragma once

#include "Effector.h"
#include "Captor.h"
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

	public:
		Manor* m_manor;
		Room* currentRoom;

		Agent(Manor* manor);

		void Run();

		void KillAgent() { m_bAlive = false; }

		void SwitchExplorationMethod();

		void chooseDesire();

		void choseeBelief();

		void getDestination();

		void observe();

		std::vector<actions> constructSolution();

		std::vector<nodes*> expand();

		void treeSearch();
	};
