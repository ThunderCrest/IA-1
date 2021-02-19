#include "AStarExploration.h"
#include "Node.h"
#include <algorithm>
#include <math.h>

//La méthode de recherche
Node* AStarExploration::graphSearch(Problem problem)
{
	roomToNode.clear();
	fringe.clear();

	//initialisation du noeud de départ
	Node* initialNode = new Node();
	initialNode->room = problem.startingRoom;
	initialNode->cost = 0;
	initialNode->estimatedCost = 0;
	fringe.push_back(initialNode);
	roomToNode.insert({ initialNode->room, initialNode });
	Node* currentNode = nullptr;

	while(fringe.size() > 0)
	{
		currentNode = fringe.front();
		fringe.erase(fringe.begin());
		if (goalTest(problem, currentNode)) return currentNode;
		std::vector<Node*> expansionResult = expand(currentNode, problem);
		fringe.insert(fringe.end(), expansionResult.begin(), expansionResult.end());
		std::sort(fringe.begin(), fringe.end(), [](Node* leftNode, Node* rightNode) { return leftNode->estimatedCost < rightNode->estimatedCost; });
 	}

	return nullptr;
}

//Le test d'atteinte de but test si la salle du noeud courant et est la salle cible
bool AStarExploration::goalTest(Problem problem, Node* node)
{
	if (node->room == problem.targetRoom) return true;
	return false;
}

std::vector<Node*> AStarExploration::expand(Node* node, Problem problem)
{
	std::vector<Node*> successors;

	std::vector<std::pair<actions, Room*>> results = getSuccessors(problem, node->room);
	for(auto result : results)
	{
		bool alreadyExists = false;
		Node* currentNode = nullptr;
		//Si il y a déjà un noeud pour la salle, on l'utilise
		if(roomToNode.find(result.second) != roomToNode.end())
		{
			currentNode = roomToNode.at(result.second);
			alreadyExists = true;
		}
		else
		{
			currentNode = new Node();
		}
		//Si le coût du déplacement est plus petit que le coût courant pour ce rendre au Noeud, on le mets à jour. Le coût par défaut est INT_MAX
		if(node->cost + 1 < currentNode->cost)
		{
			currentNode->actionToReach = result.first;
			currentNode->room = result.second;
			currentNode->parent = node;
			currentNode->cost = node->cost + 1;
			//utilisation de l'heuristique pour calculer le coût estimer jusqu'à la cible
			currentNode->estimatedCost = node->cost + StraightLineDistance(currentNode->room, problem.targetRoom);
			currentNode->depth = node->depth + 1;

			//Si le noeud existait déjà pour la salle, on ne l'ajoute pas aux successeurs, pour éviter des boucles
			if(!alreadyExists)
			{
				successors.push_back(currentNode);
				roomToNode.insert({ currentNode->room, currentNode });
			}
		}
	}

	return successors;
}

//La méthode retourne les paires contenant les salles successeurs accompagnées des actions pour s'y rendre
std::vector<std::pair<actions, Room*>> AStarExploration::getSuccessors(Problem problem, Room* room)
{
	std::vector<std::pair<actions, Room*>> successors;
	
	Room* currentRoom = nullptr;
	for(int i = 0; i < 4; i++)
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

//Pour l'heuristique, nous avons utilisé la distance à vol d'oiseau
int AStarExploration::StraightLineDistance(const Room* currentRoom, const Room* targetRoom)
{
	int difX = currentRoom->getX() - targetRoom->getX();
	int difY = currentRoom->getY() - targetRoom->getY();
	return std::sqrt(difX * difX + difY * difY);
}
