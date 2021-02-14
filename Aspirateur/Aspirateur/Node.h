#pragma once

#include "Agent.h"

class Room;
class Node
{
private:
	Room* room;
	Node* parent;
	actions actionToReach;

public:

	Node()
	{
		room = nullptr;
		parent = nullptr;
		actionToReach = actions::pick;
	}

	Node(Room* newRoom, Node* parentNode, actions action)
	{
		room = newRoom;
		parent = parentNode;
		actionToReach = action;
	}

	Room* getRoom() { return room; }
	void setRoom(Room* value) { room = value; }

	Node* getParent() { return parent; }
	void setParent(Node* value) { parent = value; }

	actions getActionToReach() { return actionToReach; }
	void setActionToReach(actions value) { actionToReach = value; }
};

