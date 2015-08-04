#include "FleeState.h"


FleeState::FleeState(){
	mMoveTarget = false;
}


FleeState::~FleeState(){
}

void FleeState::Move(float deltaTime){
	Waypoint *waypoint = nullptr;
	while (waypoint == nullptr){
		int size = mOwner->mCurrentLocation->mNeighbours.size();
		int random = (0 + rand() % (int)size);

		Waypoint *newWaypoint = (Waypoint *) mOwner->mCurrentLocation->mNeighbours.at(random);
		Node *node = newWaypoint->OtherNode(mOwner->mCurrentLocation);
		if (!node->hasCharacter()){
			waypoint = newWaypoint;
		}
	}

	if (mOwner->mCurrentLocation != nullptr){
		mOwner->mCurrentLocation->removeCharacter(mOwner);
	}
	waypoint->OtherNode(mOwner->mCurrentLocation)->setCharacter(mOwner);
	mOwner->mCurrentLocation = waypoint->OtherNode(mOwner->mCurrentLocation);
}
