#include "Waypoint.h"

Waypoint::Waypoint(Node *node1, Node *node2, int distance){
	mDistance = distance;
	mFirstNode = node1;
	mSecondNode = node2;
}


Waypoint::~Waypoint(){
}

void Waypoint::Update(float dt){

}

int Waypoint::Distance(){
	return mDistance;
}

Node* Waypoint::OtherNode(Node *node){
	if (mFirstNode == node){
		return mSecondNode;
	}
	return mFirstNode;
}
