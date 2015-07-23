#include "AStar.h"
#include <math.h>  
#include <algorithm>
#include <string>
#include <iostream>

AStar::AStar(Node *startNode, Node *targetNode){
	AStarNode *currentNode = new AStarNode(startNode, 0, DistanceBetween(startNode, targetNode));
	mOpenList.push_back(currentNode);

	bool foundTarget = false;

	while (!foundTarget){
		for (size_t i = 0; i < currentNode->mNode->mNeighbours.size(); i++){
			Waypoint *waypoint = (Waypoint *)currentNode->mNode->mNeighbours.at(i);

			if (!isInOpenList(waypoint->OtherNode(currentNode->mNode)) && waypoint->OtherNode(currentNode->mNode) != startNode){
				AStarNode *newNode = new AStarNode(waypoint->OtherNode(currentNode->mNode), currentNode->mDistance, (int)DistanceBetween(waypoint->OtherNode(currentNode->mNode), targetNode));
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

		if (!mOpenList.empty()){
			struct distanceSort {
				bool operator ()(AStarNode * const a, AStarNode * const b) const {
					return ((a->mDistance + a->mDistanceToTravel) > (b->mDistance + b->mDistanceToTravel));
				}
			};

			sort(mOpenList.begin(), mOpenList.end(), distanceSort());

			AStarNode *first = mOpenList.at(mOpenList.size() - 1);
			if (first->mNode == startNode){
				first = mOpenList.at(mOpenList.size() - 2);
				mOpenList.pop_back();
			}
			mOpenList.pop_back();
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
 	return mClosedList.at(0)->mNode;
}

AStar::~AStar(){
	mOpenList.erase(mOpenList.begin(), mOpenList.end());
	mClosedList.erase(mClosedList.begin(), mClosedList.end());
}

double AStar::DistanceBetween(Node *a, Node *b){
	double x = b->GetX() - a->GetX();
	double y = b->GetY() - a->GetY();

	double distance = 0;

	distance = sqrt(x*x + y*y);

	return distance;
}
