#include "Agent.h"
#include "Manor.h"
#include "Node.h"
#include "Environment.h"
#include <cstdlib>
#include <algorithm>


	Agent::Agent(Manor* manor) : m_effector(*this), m_captor(*this)
	{
		beliefs.m_manor = manor;
		beliefs.currentRoom = &this->beliefs.m_manor->getRoom(24);
		beliefs.currentRoom->setAgent(true);
		beliefs.performanceMesure = 0;
		beliefs.lastPerformanceMesure = INT_MIN;
		m_bAlive = true;
		m_bUsingInformedMethod = true;
		m_bFirstIterationDone = false;
		m_currentTickTime = 0;
		m_minIterations = 1;
		m_maxIterations = 30;
		m_iterationsToExploration = (m_minIterations + m_maxIterations) / 2;
		m_currentIterationsToExploration = m_iterationsToExploration;
		m_iterationModifier = 1;
		m_currentIterationsToLearning = 0;
		m_iterationsToLearning = 5;
		m_lastTickTime = 0;
		currentDesire = AgentDesires::REST;

	}

	//La méthode run est la fonction d'agent. Elle est exécutée dans son thread jusqu'à ce qu'elle soit tuée par l'utilisateur
	void Agent::run()
	{
		this->m_lastTickTime = -1;

		//La première phase d'epxloration est exécutée une seule fois au début la vie de l'agente
		observe();
		std::vector<std::pair<Node*, goals>> targetNodes = exploration();
		constructIntentions(targetNodes);

		while (m_bAlive)
		{
			//L'agent est limité a une exécution par seconde, pour avoir plus de faiclité à suivre son déplacement visuellement
			time(&m_currentTickTime);
			if (m_currentTickTime - m_lastTickTime > 0)
			{
				m_lastTickTime = m_currentTickTime;

				//On vérifie si la première exécution des intentions est terminée avant d'entrer dans le délai d'exploration apprenant
				if(m_bFirstIterationDone)
				{
					//m_iterationToExploration est la variable qui est apprise grâce à la mesure de performance
					if (m_currentIterationsToExploration >= m_iterationsToExploration)
					{
						m_currentIterationsToExploration = 0;
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

					m_currentIterationsToExploration++;
					m_currentIterationsToLearning++;
				}
				else
				{
					actions chosenAction = chooseAction();
					m_effector.executeAction(chosenAction);
					//Lorsqu'on a fini le plan initial
					if(intentions.size() < 1)
					{
						m_bFirstIterationDone = true;
						beliefs.performanceMesure = 0;
						beliefs.lastPerformanceMesure = 0;
					}
				}
			}
		}
	}

	void Agent::switchExplorationMethod()
	{
		m_bUsingInformedMethod = !m_bUsingInformedMethod;
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

		updateIterationsAmount();
	}

	//Mets à jour le nombre d'itérations entre chaque exploration
	//Si la mesure de performance est pire que la dernière, on fait la moyenne entre le nombre courant d'itérations et le nombre précédent
	//Si elle est meilleure, on fait la moyenne entre la valeur courant et la valeur minimale ou maximale, dépendamment de la direction du dernier changement
	//Un nombre minimal d'itérations doit être complété avant de mettre à jour la mesure de performance
	void Agent::updateIterationsAmount()
	{	
		if(m_currentIterationsToLearning > m_iterationsToLearning)
		{
			if (beliefs.performanceMesure - beliefs.lastPerformanceMesure > 5)
			{
				m_iterationModifier *= -1;
				m_iterationsToExploration = (m_iterationsToExploration + m_previousIterationsToExploration) / 2;
			}
			else if (beliefs.performanceMesure - beliefs.lastPerformanceMesure < -5)
			{
				if (m_iterationModifier > 0)
				{
					m_iterationsToExploration = (m_iterationsToExploration + m_maxIterations) / 2;
				}
				else
				{
					m_iterationsToExploration = (m_iterationsToExploration + m_minIterations) / 2;
				}
			}
			beliefs.lastPerformanceMesure = beliefs.performanceMesure;
			m_currentIterationsToLearning = 0;
		}
	}

	//Utilise les capteurs pour effectuer l'observation et mettre à jour les croyances de l'agent aspirateur
	void Agent::observe() {

		beliefs.currentRoom = &beliefs.m_manor->getRoom(m_captor.getCurrentRoomIndex());
		beliefs.dustyRooms = m_captor.getDustyRooms();
		beliefs.roomsWithJewel = m_captor.getRoomsWithJewel();
		beliefs.performanceMesure = m_captor.getPerformanceMesure();
	}


	//on construits les intentions à partir d'une liste de paires Noeud-But, où le Noeud contient un chemin pour se rendre à case case contenant de la poussière et/ou un bijou
	void Agent::constructIntentions(std::vector<std::pair<Node*, goals>> targetNodes) { //chooseIntentions
		intentions.clear();

		for (auto pair : targetNodes)
		{
			std::vector<actions> actions;
			Node* currentNode = pair.first;
			//On ajoute les actions liées aux chemins
			while (currentNode != nullptr)
			{
				if (currentNode->actionToReach != actions::none)
				{
					actions.insert(actions.begin(), currentNode->actionToReach);
				}
				currentNode = currentNode->parent;
			}
			//on ajoute l'action liée au buts
			switch (pair.second)
			{
			case goals::pickupJewel:
				actions.insert(actions.end(), actions::pick);
				break;
			case goals::vacuum:
				actions.insert(actions.end(), actions::aspirate);
				break;
			}
			//On ajoute toutes ces actions aux intentions
			intentions.insert(intentions.end(), actions.begin(), actions.end());
		}
	};

	//S'il reste des actions à effectuer, on prend la prochaine action de la liste d'intentions et on l'enlève de la liste
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

	//La méthode qui exécute l'exploration, retourne un vector contenant des paires de chemins et buts pour chaques pièces visées
	std::vector<std::pair<Node*, goals>> Agent::exploration() {
		
		Problem problem;
		problem.manor = beliefs.m_manor;

		problem.startingRoom = beliefs.currentRoom;
		std::vector<std::pair<Node*, goals>> resultNodes;
		std::vector<Room*> jewelRooms = beliefs.roomsWithJewel;
		std::vector<Room*> dustyRooms = beliefs.dustyRooms;

		//Pour chaque pièce non vide dans les croyances de l'agent, on détermine le chemin pour s'y rendre
		while(jewelRooms.size() > 0 || dustyRooms.size() > 0)
		{
			std::vector<Room*> targetRooms;
			targetRooms.insert(targetRooms.end(), jewelRooms.begin(), jewelRooms.end());
			targetRooms.insert(targetRooms.end(), dustyRooms.begin(), dustyRooms.end());
			//On trie les salles en ordre selon la distance entre les salles et l'agent, en priorisant les salles ayant des bijoux
			std::sort(targetRooms.begin(), targetRooms.end(), [problem, jewelRooms](const Room* leftRoom, const Room* rightRoom)
				{
					int leftDistance = AStarExploration::StraightLineDistance(problem.startingRoom, leftRoom);
					int rightDistance = AStarExploration::StraightLineDistance(problem.startingRoom, rightRoom);

					if(leftDistance != rightDistance)
					{
						return leftDistance < rightDistance;
					}
					else
					{						
						return std::find(jewelRooms.begin(), jewelRooms.end(), leftRoom) != jewelRooms.end() && std::find(jewelRooms.begin(), jewelRooms.end(), rightRoom) == jewelRooms.end();
					}
				});

			//On prend la première salle et on détermine le but selon la liste dans laquelle elle se trouve
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

			//On appelle une méthode d'exploration, selon celle qui a été choisi, dans ce cas A* pour l'informée et IDS pour la non-informée
			Node* node = nullptr;
			if (m_bUsingInformedMethod)
			{
				node = aStar.graphSearch(problem);
			}
			else
			{
				node = aStar.graphSearch(problem);

			}
			//Si l'exploration retourne un succès, on ajoute le noeud final à la liste et on associe sa salle comme étant la nouvelle salle de départ pour les prochaines salles des croyances
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
