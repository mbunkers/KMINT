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
	mStateChangeCounter--;

	if (dynamic_cast<SleepState *>(((Character *)FWApplication::GetInstance()->getCow())->mCurrentState)){
		if (mStateChangeCounter < 0){
			changeState();
			Character *cow = (Character *)FWApplication::GetInstance()->getCow();
			cow->wakeup((Character *)FWApplication::GetInstance()->getBunny());
		}
	}
}

void Bunny::flee(){
	Character::flee();
	mStateChangeCounter = 5;
	
}

void Bunny::changeState(){
	SDL_Texture *texture = getTexture();
	if (dynamic_cast<WanderingState *>(mCurrentState)){
		if (mCurrentLocation->mNeighbours.size() == 2){
			flee();
		}
		else {
			// Change of 50%
			int random = (0 + rand() % (int)2);
			Item *item = nullptr;
			int r, g, b = 0;
			if (random == 0){
				item = (Item *)FWApplication::GetInstance()->getItem();
				r = 255;
				g = 255;
				b = 255;
			}
			else {
				item = (Item *)FWApplication::GetInstance()->getWeapon();
				r = 200;
				g = 200;
				b = 200;
			}

			search(item, r, g, b);
		}
	}
	else if (dynamic_cast<FleeState *>(mCurrentState)){
		wander();
	}
	else if (dynamic_cast<SearchState *>(mCurrentState)){
		if (mCurrentLocation->mItem == mCurrentState->mTarget){
			chase((Character *)FWApplication::GetInstance()->getCow());
		}
		else {
			wander();
		}
	}
	else if (dynamic_cast<ChaseState *>(mCurrentState)){
		wander();
	}
}
