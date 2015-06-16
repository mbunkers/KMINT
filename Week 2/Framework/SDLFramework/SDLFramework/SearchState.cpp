#include "SearchState.h"
#include "AStar.h"
#include "Item.h"

SearchState::SearchState() : State(){
	mMoveTarget = true;
}


SearchState::~SearchState(){
}


void SearchState::Move(){
	Item *target = (Item *)mTarget;
	AStar *aStar = new AStar(mOwner->mCurrentLocation, target->mCurrentLocation);
	Node *newNode = aStar->getNextNode();

	if (newNode == nullptr){
		return;
	}

	if (mOwner->mCurrentLocation != nullptr){
		mOwner->mCurrentLocation->removeCharacter(mOwner);
	}
	mOwner->mCurrentLocation = newNode;
	mOwner->mCurrentLocation->setCharacter(mOwner);
}
