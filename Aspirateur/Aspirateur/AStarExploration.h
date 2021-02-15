#pragma once

#include <vector>
#include <map>
#include <utility>
#include <stdlib.h>
#include "Problem.h"

class Node;
enum class actions;
class AStarExploration
{
private:

	std::vector<Node*> fringe;

	std::map<Room*, Node*> roomToNode;

	bool goalTest(Problem problem, Node* node);

	std::vector<Node*> expand(Node* node, Problem problem);

	std::vector<std::pair<actions, Room*>> getSuccessors(Problem problem, Room* room);

	int manhattanDistance(Room* currentRoom, Room* targetRoom);
	int BirdEyeViewDistance(Room* currentRoom, Room* targetRoom);

public:

	Node* graphSearch(Problem problem);
};

