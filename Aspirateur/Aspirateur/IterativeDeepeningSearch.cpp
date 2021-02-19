#include "IterativeDeepeningSearch.h"
#include "Node.h"

//Le test d'atteinte de but test si la salle du noeud courant et est la salle cible
bool IterativeDeepeningSearch::goalTest(Problem problem, Node* node)
{
	if (node->room == problem.targetRoom) return true;
	return false;
}

std::vector<Node*> IterativeDeepeningSearch::expand(Node* node, Problem problem)
{
	std::vector<Node*> successors;

	std::vector<std::pair<actions, Room*>> results = getSuccessors(problem, node->room);
	for (auto result : results)
	{
		bool alreadyExists = false;
		Node* currentNode = nullptr;
		//Si il y a déjà un noeud pour la salle, on l'utilise
		if (roomToNode.find(result.second) != roomToNode.end())
		{
			currentNode = roomToNode.at(result.second);
			alreadyExists = true;
		}
		else
		{
			currentNode = new Node();
		}
		//Si le coût du déplacement est plus petit que le coût courant pour ce rendre au Noeud, on le mets à jour. Le coût par défaut est INT_MAX
		if (node->cost + 1 < currentNode->cost)
		{
			currentNode->actionToReach = result.first;
			currentNode->room = result.second;
			currentNode->parent = node;
			currentNode->cost = node->cost + 1;
			currentNode->depth = node->depth + 1;

			//Si le noeud existait déjà pour la salle, on ne l'ajoute pas aux successeurs, pour éviter des boucles
			if (!alreadyExists)
			{
				successors.push_back(currentNode);
				roomToNode.insert({ currentNode->room, currentNode });
			}
		}
	}

	return successors;
}

//La méthode retourne les paires contenant les salles successeurs accompagnées des actions pour s'y rendre
std::vector<std::pair<actions, Room*>> IterativeDeepeningSearch::getSuccessors(Problem problem, Room* room)
{
	std::vector<std::pair<actions, Room*>> successors;

	Room* currentRoom = nullptr;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			currentRoom = problem.manor->getRoomInDirection(room, actions::goLeft);
			if (currentRoom != nullptr)
			{
				successors.push_back(std::pair<actions, Room*>(actions::goLeft, currentRoom));
			}
			break;
		case 1:
			currentRoom = problem.manor->getRoomInDirection(room, actions::goRight);
			if (currentRoom != nullptr)
			{
				successors.push_back(std::pair<actions, Room*>(actions::goRight, currentRoom));
			}
			break;
		case 2:
			currentRoom = problem.manor->getRoomInDirection(room, actions::goTop);
			if (currentRoom != nullptr)
			{
				successors.push_back(std::pair<actions, Room*>(actions::goTop, currentRoom));
			}
			break;
		case 3:
			currentRoom = problem.manor->getRoomInDirection(room, actions::goBottom);
			if (currentRoom != nullptr)
			{
				successors.push_back(std::pair<actions, Room*>(actions::goBottom, currentRoom));
			}
			break;
		}
	}
	return successors;
}

DLSResult IterativeDeepeningSearch::DepthLimitedSearch(Problem problem, int limit)
{
	roomToNode.clear();

	Node* initialNode = new Node();
	initialNode->room = problem.startingRoom;
	initialNode->cost = 0;
	initialNode->estimatedCost = 0;
	roomToNode.insert({ initialNode->room, initialNode });

	return RecursiveDLS(initialNode, problem, limit);
}

DLSResult IterativeDeepeningSearch::RecursiveDLS(Node* node, Problem problem, int limit)
{
	bool cutoffHappened = false;
	DLSResult result;
	if(goalTest(problem, node))
	{
		result.resultNode = node;
		result.result = Result::success;
		return result;
	}
	else if (node->depth == limit)
	{
		result.result = Result::cutoff;
		return result;
	}
	else
	{
		std::vector<Node*> successors = expand(node, problem);
		for(Node* successor : successors)
		{
			DLSResult successorResult = RecursiveDLS(successor, problem, limit);
			if(successorResult.result == Result::cutoff)
			{
				cutoffHappened = true;
			}
			else if(successorResult.result != Result::failure)
			{
				return successorResult;
			}
		}
	}
	if(cutoffHappened)
	{
		result.result = Result::cutoff;
	}
	else
	{
		result.result = Result::failure;
	}
	return result;
}

//La profondeur est limitée à 25, puisque nous avons 25 salles dans l'environnement
Node* IterativeDeepeningSearch::treeSearch(Problem problem)
{
	DLSResult result;
	for(int depth = 0; depth < 25; depth++)
	{
		result = DepthLimitedSearch(problem, depth);
		if (result.result != Result::cutoff) return result.resultNode;
	}
	return nullptr;
}
