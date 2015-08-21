#include "WanderingState.h"
#include "ChaseState.h"

WanderingState::WanderingState(): State("Aan het wandelen"){
}


WanderingState::~WanderingState(){
}

void WanderingState::Move(){
	if (mOwner != nullptr){

		if (dynamic_cast<WanderingState *>(((Character *)FWApplication::GetInstance()->getCow())->mCurrentState)){
			Node *enemyNode = nullptr;
			for (size_t i = 0; i < mOwner->mCurrentLocation->mNeighbours.size(); i++){
				Waypoint *waypoint = (Waypoint *)mOwner->mCurrentLocation->mNeighbours.at(i);
				Node *node = waypoint->OtherNode(mOwner->mCurrentLocation);
				if (node->hasCharacter()){
					enemyNode = node;
					break;
				}
			}

			if (enemyNode != nullptr){
				mOwner->changeState();
			}
		}

		Waypoint *waypoint = nullptr;

		while (waypoint == nullptr){
			int size = mOwner->mCurrentLocation->mNeighbours.size();
			int random = (0 + rand() % (int)size);

			waypoint = (Waypoint *)mOwner->mCurrentLocation->mNeighbours.at(random);
			Node *newNode = waypoint->OtherNode(mOwner->mCurrentLocation);
			if (newNode->hasCharacter()){
				Character *character = newNode->mCharacters.at(0);

				if (dynamic_cast<ChaseState *>(character->mCurrentState)){
					waypoint = nullptr;
				}
			}
		}

		if (mOwner->mCurrentLocation != nullptr){
			mOwner->mCurrentLocation->removeCharacter(mOwner);			
		}
		waypoint->OtherNode(mOwner->mCurrentLocation)->setCharacter(mOwner);
		mOwner->mCurrentLocation = waypoint->OtherNode(mOwner->mCurrentLocation);
	}
}
