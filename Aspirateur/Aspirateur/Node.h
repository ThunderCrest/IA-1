#pragma once

#include "Agent.h"

class Room;
struct Node
{
	Room* room = nullptr;
	Node* parent = nullptr;
	actions actionToReach = actions::none;
	int cost = INT_MAX;
	int estimatedCost = INT_MAX;
	int depth = 0;
};

