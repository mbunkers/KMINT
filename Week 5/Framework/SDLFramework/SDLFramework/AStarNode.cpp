#include "AStarNode.h"

AStarNode::AStarNode(Node *node, int distance, int distanceToTravel){
	mNode = node;
	mDistance = distance;
	mDistanceToTravel = distanceToTravel;
}
