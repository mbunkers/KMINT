#include "SearchState.h"
#include "AStar.h"
#include "Item.h"

SearchState::SearchState() : State(){
	mMoveTarget = true;
}

SearchState::~SearchState(){
}

void SearchState::Update(){
	if (mOwner->CheckCollision(mOwner->mItem)){
		mOwner->mItem->setPosition(FWApplication::GetInstance()->itemSpawnPoint());

		if (mOwner->mItem->mIsWeapon){
			mOwner->hide();
			mOwner->mSteering->reset();
		}
		else {
			mOwner->invincible();
			mOwner->mSteering->reset();
		}
	}
}

void SearchState::Move(float deltaTime){
	Item *target = (Item *)mTarget;
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

	if (mOwner->mCurrentLocation->mItem == target){
		mOwner->changeState();
	}
}
