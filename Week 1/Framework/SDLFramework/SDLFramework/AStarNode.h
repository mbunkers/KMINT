#pragma once

#include "Node.h"

class AStarNode{
private:

public:
	AStarNode(Node *node, int distance, int distanceToTravel);
	~AStarNode();

	int mDistance = 1;
	int mDistanceToTravel = 0;
	Node *mNode = nullptr;
};