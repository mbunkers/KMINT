#include "SearchState.h"
#include "AStar.h"

SearchState::SearchState() : State(){
	
}


SearchState::~SearchState(){
}


void SearchState::Move(){
	Character *target = (Character *)mTarget;
	AStar *aStar = new AStar(mOwner->mCurrentLocation, target->mCurrentLocation);
	Node *newNode = aStar->getNextNode();

	//if (newNode->mCharacter != nullptr){
	//	newNode->mCharacter->mCurrentLocation->removeCharacter(newNode->m);
	//	mFinished = true;
	//}

	if (mOwner->mCurrentLocation != nullptr){
		mOwner->mCurrentLocation->removeCharacter(mOwner);
		mOwner->mCurrentLocation = newNode;
		mOwner->mCurrentLocation->setCharacter(mOwner);
	}
}
