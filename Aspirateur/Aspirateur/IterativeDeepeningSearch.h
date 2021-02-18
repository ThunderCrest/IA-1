#pragma once

#include <vector>
#include <map>
#include <utility>
#include <stdlib.h>
#include "Problem.h"

enum class actions;
class Node;

enum class Result
{
	success,
	failure,
	cutoff
};

struct DLSResult 
{
	Node* resultNode = nullptr;
	Result result = Result::failure;
};

class IterativeDeepeningSearch
{
private:

	std::map<Room*, Node*> roomToNode;

	bool goalTest(Problem problem, Node* node);

	std::vector<Node*> expand(Node* node, Problem problem);

	std::vector<std::pair<actions, Room*>> getSuccessors(Problem problem, Room* room);

	DLSResult DepthLimitedSearch(Problem problem, int limit);

	DLSResult RecursiveDLS(Node* node, Problem problem, int limit);



public:
	Node* treeSearch(Problem problem);
};

