#include "Bunny.h"
#include "WanderingState.h"
#include "SearchState.h"
#include "FleeState.h"
#include "ChaseState.h"
#include "SleepState.h"
#include "SDL_render.h"

Bunny::Bunny(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	wander();
	mStateChangeCounter = 5;
}


Bunny::~Bunny(){
}

void Bunny::move(){
	mCurrentState->Move();
	mCurrentState->moveUpdate();
}

void Bunny::Update(float deltaTime){
	if (dynamic_cast<ChaseState *>(mCurrentState)){
		if (mItem != nullptr){
			if (mItem->mIsWeapon){
				for (size_t i = 0; i < mCurrentLocation->mNeighbours.size(); i++){
					Waypoint *waypoint = (Waypoint *)mCurrentLocation->mNeighbours.at(i);
					Node *node = waypoint->OtherNode(mCurrentLocation);
					if (node->hasCharacter()){
						((Character *)FWApplication::GetInstance()->getCow())->respawn();
						((Character *)FWApplication::GetInstance()->getCow())->chase(this);
						wander();
						mItem = nullptr;
						break;
					}
				}
			}
		}
	}
	else {
		if (dynamic_cast<WanderingState *>(mCurrentState)){
			if (mItem != nullptr){
				if (mCurrentLocation->mCharacters.size() > 1){
					Character *cow = (Character *)FWApplication::GetInstance()->getCow();
					cow->sleep();
					flee();
					cow->mCurrentState->setReset(5);
					mCurrentState->setReset(5);
					mItem == nullptr;
				}
			}
			else {
				Character *cow = (Character *)FWApplication::GetInstance()->getCow();
				if (dynamic_cast<ChaseState *>(cow->mCurrentState)){
					for (size_t i = 0; i < mCurrentLocation->mNeighbours.size(); i++){
						Waypoint *waypoint = (Waypoint *)mCurrentLocation->mNeighbours.at(i);
						Node *node = waypoint->OtherNode(mCurrentLocation);
						if (node->hasCharacter()){
							changeState();
							break;
						}
					}
				}
			}
		}
	}

	if (mCurrentState->willReset()){
		wander();
	}
}

void Bunny::changeState(){
	// Flee = 20%, search pill = 40%, search weapon = 40%
	vector<int> chances = vector<int>();
	chances.push_back(20);
	chances.push_back(40);
	chances.push_back(40);

	int random = (0 + rand() % (int)101);
	int choice = 0;
	for (size_t i = 0; i < chances.size(); i++){
		int between = choice;
		choice += chances.at(i);
		if (between < random && choice > random){
			switch (i){
			case 1:
				search((Item *)FWApplication::GetInstance()->getItem(), 255, 255, 0);
				return;
			case 2:
				search((Item *)FWApplication::GetInstance()->getWeapon(), 200, 200, 200);
				return;
			default:
				flee();
				return;
			}
		}
	}
}
