#pragma once

#include "Node.h"

class AStarNode{
private:

public:
	AStarNode(Node *node, double distance, double distanceToTravel);
	~AStarNode();

	double mDistance = 1;
	double mDistanceToTravel = 0;
	Node *mNode = nullptr;
};