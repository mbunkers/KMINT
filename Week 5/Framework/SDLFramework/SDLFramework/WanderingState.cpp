#include "WanderingState.h"
#include "ChaseState.h"

WanderingState::WanderingState(): State(){
}


WanderingState::~WanderingState(){
}

void WanderingState::Update(){
	SVector2D toPursuer = mOwner->mSteering->target()->position() - mOwner->position();

	if (toPursuer.LengthSq() < pow(300, 2)){
		mOwner->changeState();
		delete this;
	}
}

void WanderingState::Move(float deltaTime){
	if (mOwner != nullptr){

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
		else {
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
}
