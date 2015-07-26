#include "SpeedWanderingState.h"

SpeedWanderingState::SpeedWanderingState() : State("Aan het snelwandelen"){
}


SpeedWanderingState::~SpeedWanderingState(){
}

void SpeedWanderingState::Move(){
	Node *startLocation = mOwner->mCurrentLocation;
	moveOnce(nullptr);
	moveOnce(startLocation);
}

void SpeedWanderingState::moveOnce(Node *node){
	if (mOwner != nullptr){

		Waypoint *waypoint = nullptr;

		while (waypoint == nullptr){
			int size = mOwner->mCurrentLocation->mNeighbours.size();
			int random = (0 + rand() % (int)size);

			waypoint = (Waypoint *)mOwner->mCurrentLocation->mNeighbours.at(random);
			Node *newNode = waypoint->OtherNode(mOwner->mCurrentLocation);
			if (newNode == node){
				waypoint = nullptr;
			}
		}

		if (mOwner->mCurrentLocation != nullptr){
			mOwner->mCurrentLocation->removeCharacter(mOwner);
		}
		waypoint->OtherNode(mOwner->mCurrentLocation)->setCharacter(mOwner);
		mOwner->mCurrentLocation = waypoint->OtherNode(mOwner->mCurrentLocation);
	}
}
