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
		m_bAlive = true;
		m_bUsingInformedMethod = true;
		m_currentIterationsToExploration = 5;
		m_currentTickTime = 0;
		m_iterationsToExploration = 5;
		m_lastTickTime = 0;
		currentDesire = AgentDesires::REST;

	}

	void Agent::Run()
	{
		this->m_lastTickTime = -1;
		while (m_bAlive)
		{
			time(&this->m_currentTickTime);
			if (this->m_currentTickTime - this->m_lastTickTime > 0)
			{
				this->m_lastTickTime = this->m_currentTickTime;
				if (this->m_currentIterationsToExploration >= this->m_iterationsToExploration)
				{
					
					this->m_currentIterationsToExploration = 0;
					observe();
					std::vector<std::pair<Node*, goals>> targetNodes = exploration();
					constructIntentions(targetNodes);
					
				}
				
				actions chosenAction = chooseAction();
				m_effector.executeAction(chosenAction);
				

				this->m_currentIterationsToExploration++;
			}
		}
	}

	void Agent::SwitchExplorationMethod()
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




	void Agent::chooseDesire() {

	}


	void Agent::observe() {

		beliefs.currentRoom = &beliefs.m_manor->getRoom(m_captor.getCurrentRoomIndex());
		beliefs.dustyRooms = m_captor.getDustyRooms();
		beliefs.roomsWithJewel = m_captor.getRoomsWithJewel();
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
