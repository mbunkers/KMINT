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

double Waypoint::Distance(){
	double x = mFirstNode->GetX() - mSecondNode->GetX();
	double y = mFirstNode->GetX() - mSecondNode->GetX();

	double distance = 0;

	distance = sqrt(x*x + y*y);

	return distance;
}

Node* Waypoint::OtherNode(Node *node){
	if (mFirstNode == node){
		return mSecondNode;
	}
	return mFirstNode;
}
