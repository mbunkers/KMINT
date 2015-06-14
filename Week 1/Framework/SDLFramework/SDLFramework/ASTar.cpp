#include "AStar.h"
#include <math.h>  
#include <algorithm>

AStar::AStar(Node *startNode, Node *targetNode){
	Node *currentNode = startNode;

	bool foundTarget = false;

	while (!foundTarget){
		for (size_t i = 0; i < currentNode->mNeighbours.size(); i++){
			Waypoint *waypoint = (Waypoint *)currentNode->mNeighbours.at(i);

			if (!isInOpenList(waypoint->OtherNode(currentNode)) && waypoint->OtherNode(currentNode) != startNode){
				mOpenList.push_back(new AStarNode(waypoint->OtherNode(currentNode), waypoint->Distance(), DistanceBetween(currentNode, targetNode)));
			}
		}

		if (!mOpenList.empty()){
			struct distanceSort {
				bool operator ()(AStarNode * const a, AStarNode * const b) const {
					return ((a->mDistance + a->mDistanceToTravel) < (b->mDistance + b->mDistanceToTravel));
						return true;
				}
			};

			sort(mOpenList.begin(), mOpenList.end(), distanceSort());

			AStarNode *first = mOpenList.at(0);
			mClosedList.push_back(first);
			mOpenList.erase(mOpenList.begin());
			currentNode = first->mNode;

			if (currentNode == targetNode){
				foundTarget = true;
			}
		}
	}
}

bool AStar::isInOpenList(Node *node){
	for (size_t i = 0; i < mClosedList.size(); i++){
		AStarNode *aStarNode = mClosedList.at(i);
		if (aStarNode->mNode == node){
			return true;
		}
	}
	return false;
}

Node * AStar::getNextNode(){
	Node *node = mClosedList.at(0)->mNode;
//	mClosedList.erase(mClosedList.begin());
	return node;
}

AStar::~AStar(){
	mOpenList.erase(mOpenList.begin(), mOpenList.end());
	mClosedList.erase(mClosedList.begin(), mClosedList.end());
}

double AStar::DistanceBetween(Node *a, Node *b){
	double x = a->GetX() - b->GetX();
	double y = a->GetX() - b->GetX();

	double distance = 0;

	distance = sqrt(x*x + y*y);

	return distance;
}
