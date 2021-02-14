#include "AStarExploration.h"
#include "Node.h"

Node* AStarExploration::treeSearch()
{
	return nullptr;
}

bool AStarExploration::goalTest(Node* node)
{
	//switch(problem)
	//{
	//case Dirt:
	//	if (node->getRoom()->getDirt()) return true;
	//	break;
	//case Jewel:
	//	if (node->getRoom()->getJewel()) return true;
	//	break;
	//}
	return false;
}

std::vector<Node*> AStarExploration::expand(Node* node)
{
	return std::vector<Node*>();
}
