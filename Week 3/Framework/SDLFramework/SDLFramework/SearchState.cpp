#include "SearchState.h"
#include "AStar.h"
#include "Item.h"

SearchState::SearchState() : State("Aan het zoeken naar een item"){
	mMoveTarget = true;
}

SearchState::~SearchState(){
}


void SearchState::Move(){
	Item *target = (Item *)mTarget;
	AStar *aStar = new AStar(mOwner->mCurrentLocation, target->mCurrentLocation);
	Node *newNode = aStar->getNextNode();
	delete aStar;

	if (newNode == nullptr){
		return;
	}
	if (newNode->hasCharacter()){
		Waypoint *waypoint = nullptr;

		while (waypoint == nullptr){
			int size = mOwner->mCurrentLocation->mNeighbours.size();
			int random = (0 + rand() % (int)size);

			waypoint = (Waypoint *)mOwner->mCurrentLocation->mNeighbours.at(random);
			Node *newNode = waypoint->OtherNode(mOwner->mCurrentLocation);
			if (newNode->hasCharacter()){
				waypoint = nullptr;
			}
		}

		if (mOwner->mCurrentLocation != nullptr){
			mOwner->mCurrentLocation->removeCharacter(mOwner);
		}
		waypoint->OtherNode(mOwner->mCurrentLocation)->setCharacter(mOwner);
		mOwner->mCurrentLocation = waypoint->OtherNode(mOwner->mCurrentLocation);
	}
	else {
		if (mOwner->mCurrentLocation != nullptr){
			mOwner->mCurrentLocation->removeCharacter(mOwner);
		}
		mOwner->mCurrentLocation = newNode;
		mOwner->mCurrentLocation->setCharacter(mOwner);

		if (mOwner->mCurrentLocation->mItem == target){
			mOwner->chase((Character *)FWApplication::GetInstance()->getCow());
			mOwner->mItem = (Item *)mTarget;
		}
	}
}

string SearchState::name(){
	if (dynamic_cast<Item *>(mTarget)){
		Item *item = (Item *)mTarget;
		if (item->mIsWeapon){
			return State::name() + ", Wapen";
		}
		return State::name() + ", Pil";
	}
	return State::name();
}
