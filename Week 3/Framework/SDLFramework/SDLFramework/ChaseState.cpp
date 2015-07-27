#include "ChaseState.h"
#include "AStar.h"

ChaseState::ChaseState() : State("Aan het jagen"){
	mMoveTarget = true;
}


ChaseState::~ChaseState(){
}

void ChaseState::Move(){
	Character *target = (Character *)mTarget;
	AStar *aStar = new AStar(mOwner->mCurrentLocation, target->mCurrentLocation);
	Node *newNode = aStar->getNextNode();
	delete aStar;

	if (newNode == nullptr){
		return;
	}

	if (mOwner->mCurrentLocation != nullptr){
		mOwner->mCurrentLocation->removeCharacter(mOwner);
	}
	
	mOwner->mCurrentLocation = newNode;
	mOwner->mCurrentLocation->setCharacter(mOwner);
}