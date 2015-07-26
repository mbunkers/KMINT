#include "AStarNode.h"

AStarNode::AStarNode(Node *node, double distance, double distanceToTravel){
	mNode = node;
	mDistance = distance;
	mDistanceToTravel = distanceToTravel;
}
