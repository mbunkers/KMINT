#include "AStar.h"
#include <math.h>  
#include <algorithm>
#include <string>
#include <iostream>

AStar::AStar(Node *startNode, Node *targetNode){
	if (startNode == nullptr){
		return;
	}
	AStarNode *currentNode = new AStarNode(startNode, 0, (int)DistanceBetween(startNode, targetNode));
	mOpenList.push_back(currentNode);

	bool foundTarget = false;

	while (!foundTarget){
		for (size_t i = 0; i < currentNode->mNode->mNeighbours.size(); i++){
			Waypoint *waypoint = (Waypoint *)currentNode->mNode->mNeighbours.at(i);

			if (waypoint->OtherNode(currentNode->mNode) != nullptr){
				if (!isInOpenList(waypoint->OtherNode(currentNode->mNode)) && waypoint->OtherNode(currentNode->mNode) != startNode){
					AStarNode *newNode = new AStarNode(waypoint->OtherNode(currentNode->mNode), currentNode->mDistance,(int)DistanceBetween(waypoint->OtherNode(currentNode->mNode), targetNode));
					bool present = false;
					for (size_t i = 0; i < mClosedList.size(); i++){
						AStarNode *aStarNode = mClosedList.at(i);
						if (aStarNode->mNode == waypoint->OtherNode(currentNode->mNode)){

							if (aStarNode->mDistance + aStarNode->mDistanceToTravel < currentNode->mDistance + currentNode->mDistanceToTravel){
								mOpenList.erase(mOpenList.begin() + i);
								mOpenList.push_back(newNode);
							}

							present = true;
							break;
						}
					}
					if (!present){
						mOpenList.push_back(newNode);
					}
				}
			}
		}

		if (!mOpenList.empty()){
			struct distanceSort {
				bool operator ()(AStarNode * const a, AStarNode * const b) const {
					return ((a->mDistance + a->mDistanceToTravel) > (b->mDistance + b->mDistanceToTravel));
						return true;
				}
			};

			sort(mOpenList.begin(), mOpenList.end(), distanceSort());

			AStarNode *first = mOpenList.at(0);
			first = mOpenList.at(mOpenList.size() - 1);
			mOpenList.pop_back();
			
			mOpenList.erase(mOpenList.begin());
			first->mDistance += currentNode->mDistance;
			mClosedList.push_back(first);
			currentNode = mClosedList.at(mClosedList.size() - 1);
			

			if (currentNode->mNode == targetNode){
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
	if (mClosedList.size() == 0){
		return nullptr;
	}
 	return mClosedList.at(0)->mNode;
}

AStar::~AStar(){
	mOpenList.erase(mOpenList.begin(), mOpenList.end());
	mClosedList.erase(mClosedList.begin(), mClosedList.end());
}

double AStar::DistanceBetween(Node *a, Node *b){
	if (a == nullptr || b == nullptr){
		return 0;
	}
	double x = a->GetX() - b->GetX();
	double y = a->GetX() - b->GetX();

	double distance = 0;

	distance = sqrt(x*x + y*y);

	return distance;
}
