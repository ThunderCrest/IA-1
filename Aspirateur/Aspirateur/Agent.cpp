#include "Agent.h"
#include "Manor.h"
#include "Node.h"
#include "Environment.h"
#include <cstdlib>
#include <algorithm>


	Agent::Agent(Manor* manor) : m_effector(*this), m_captor(*this)
	{
		this->beliefs.m_manor = manor;
		beliefs.currentRoom = &this->beliefs.m_manor->getRoom(24);
		beliefs.currentRoom->setAgent(true);
		beliefs.performanceMesure = 0;
		beliefs.lastPerformanceMesure = 0;
		m_bAlive = true;
		m_bUsingInformedMethod = true;
		m_bFirstIterationDone = false;
		m_currentTickTime = 0;
		m_minIterations = 1;
		m_maxIterations = 30;
		m_iterationsToExploration = (m_minIterations + m_maxIterations) / 2;
		m_currentIterationsToExploration = m_iterationsToExploration;
		m_iterationModifier = -1;
		m_lastTickTime = 0;
		currentDesire = AgentDesires::REST;

	}

	void Agent::run()
	{
		this->m_lastTickTime = -1;

		observe();
		std::vector<std::pair<Node*, goals>> targetNodes = exploration();
		constructIntentions(targetNodes);

		while (m_bAlive)
		{
			time(&this->m_currentTickTime);
			if (this->m_currentTickTime - this->m_lastTickTime > 0)
			{
				this->m_lastTickTime = this->m_currentTickTime;

				if(m_bFirstIterationDone)
				{
					if (this->m_currentIterationsToExploration >= this->m_iterationsToExploration)
					{
						this->m_currentIterationsToExploration = 0;
						observe();
						updateState();
						if(currentDesire == AgentDesires::CLEAN)
						{
							std::vector<std::pair<Node*, goals>> targetNodes = exploration();
							constructIntentions(targetNodes);
						}
						else if (currentDesire == AgentDesires::REST)
						{
							intentions.clear();
						}
					}

					actions chosenAction = chooseAction();
					m_effector.executeAction(chosenAction);

					this->m_currentIterationsToExploration++;
				}
				else
				{
					actions chosenAction = chooseAction();
					m_effector.executeAction(chosenAction);
					if(intentions.size() < 1)
					{
						m_bFirstIterationDone = true;
					}
				}
			}
		}
	}

	void Agent::switchExplorationMethod()
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




	void Agent::updateState() 
	{
		if(beliefs.roomsWithJewel.size() == 0 && beliefs.dustyRooms.size() == 0)
		{
			currentDesire = AgentDesires::REST;
		}
		else
		{
			currentDesire = AgentDesires::CLEAN;
		}

		if(beliefs.performanceMesure > beliefs.lastPerformanceMesure)
		{
			if(m_iterationModifier > 0)
			{
				m_iterationsToExploration = (m_iterationsToExploration + m_maxIterations) / 2;
			}
			else
			{
				m_iterationsToExploration = (m_iterationsToExploration + m_minIterations) / 2;
			}
			m_iterationModifier *= -1;
		}
	}


	void Agent::observe() {

		beliefs.currentRoom = &beliefs.m_manor->getRoom(m_captor.getCurrentRoomIndex());
		beliefs.dustyRooms = m_captor.getDustyRooms();
		beliefs.roomsWithJewel = m_captor.getRoomsWithJewel();
		beliefs.lastPerformanceMesure = beliefs.performanceMesure;
		beliefs.performanceMesure = m_captor.getPerformanceMesure();
	}



	void Agent::constructIntentions(std::vector<std::pair<Node*, goals>> targetNodes) { //chooseIntentions
		intentions.clear();

		for (auto pair : targetNodes)
		{
			std::vector<actions> actions;
			Node* currentNode = pair.first;
			while (currentNode != nullptr)
			{
				if (currentNode->actionToReach != actions::none)
				{
					actions.insert(actions.begin(), currentNode->actionToReach);
				}
				currentNode = currentNode->parent;
			}
			switch (pair.second)
			{
			case goals::pickupJewel:
				actions.insert(actions.end(), actions::pick);
				break;
			case goals::vacuum:
				actions.insert(actions.end(), actions::aspirate);
				break;
			}
			intentions.insert(intentions.end(), actions.begin(), actions.end());
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

	std::vector<std::pair<Node*, goals>> Agent::exploration() {
		
		Problem problem;
		problem.manor = beliefs.m_manor;

		problem.startingRoom = beliefs.currentRoom;
		std::vector<std::pair<Node*, goals>> resultNodes;
		std::vector<Room*> jewelRooms = beliefs.roomsWithJewel;
		std::vector<Room*> dustyRooms = beliefs.dustyRooms;

		while(jewelRooms.size() > 0 || dustyRooms.size() > 0)
		{
			std::vector<Room*> targetRooms;
			targetRooms.insert(targetRooms.end(), jewelRooms.begin(), jewelRooms.end());
			targetRooms.insert(targetRooms.end(), dustyRooms.begin(), dustyRooms.end());
			std::sort(targetRooms.begin(), targetRooms.end(), [problem, jewelRooms](const Room* leftRoom, const Room* rightRoom)
				{
					int leftDistance = AStarExploration::BirdEyeViewDistance(problem.startingRoom, leftRoom);
					int rightDistance = AStarExploration::BirdEyeViewDistance(problem.startingRoom, rightRoom);

					if(leftDistance != rightDistance)
					{
						return leftDistance < rightDistance;
					}
					else
					{						
						return std::find(jewelRooms.begin(), jewelRooms.end(), leftRoom) != jewelRooms.end() && std::find(jewelRooms.begin(), jewelRooms.end(), rightRoom) == jewelRooms.end();
					}
				});

			problem.targetRoom = targetRooms.front();
			auto it = std::find(jewelRooms.begin(), jewelRooms.end(), problem.targetRoom);
			if (it != jewelRooms.end())
			{
				jewelRooms.erase(it);
				problem.goal = goals::pickupJewel;
			}
			else if ((it = std::find(dustyRooms.begin(), dustyRooms.end(), problem.targetRoom)) != dustyRooms.end())
			{
				dustyRooms.erase(it);
				problem.goal = goals::vacuum;
			}

			Node* node = nullptr;
			if (m_bUsingInformedMethod)
			{
				node = aStar.graphSearch(problem);
			}
			else
			{
				node = aStar.graphSearch(problem);

			}
			if (node != nullptr)
			{
				resultNodes.push_back(std::pair<Node*, goals>(node, problem.goal));
				problem.startingRoom = node->room;
			}
		}

		return resultNodes;
	}

	void Agent::setEnvironment(Environment& environment)
	{
		this->environment = &environment;
	}
