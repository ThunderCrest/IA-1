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

public:

	Node* graphSearch(Problem problem);

	static int StraightLineDistance(const Room* currentRoom, const Room* targetRoom);
};

