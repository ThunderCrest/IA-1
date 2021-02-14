#pragma once

#include <vector>

class Node;

class AStarExploration
{

public:

	Node* treeSearch(/*Problem/Goal*/);

	bool goalTest(/*Problem/Goal, */Node* node);

	std::vector<Node*> expand(Node* node/*, Problem/Goal*/);
};

