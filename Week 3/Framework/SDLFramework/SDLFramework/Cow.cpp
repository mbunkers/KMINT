#include "Cow.h"
#include "WanderingState.h"
#include "SleepState.h"
#include "FWApplication.h"
#include "SDL_render.h"

Cow::Cow(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	chase((Character *)FWApplication::GetInstance()->getBunny());
}


Cow::~Cow(){
}

void Cow::move(){
	mCurrentState->Move();
	mCurrentState->moveUpdate();
}

void Cow::changeState(){
	SDL_Texture *texture = getTexture();
	if (dynamic_cast<ChaseState *>(mCurrentState)){
		wander();
	}
	else {
		if (dynamic_cast<SearchState *>(mCurrentState)){
			chase((Character *)FWApplication::GetInstance()->getBunny());
		}
	}
}

void Cow::Update(float deltaTime){
	if (mCurrentState->mMoveTarget){
		if (dynamic_cast<ChaseState *>(mCurrentState)){
			if (mCurrentLocation->mCharacters.size() > 1){
				Character *bunny = ((Character *)FWApplication::GetInstance()->getBunny());
				// Otherwise should the bunny takes the according action as it wins
				if (bunny->mItem == nullptr || bunny->mItem->mIsWeapon){
					bunny->wander();
					bunny->respawn();
				}
			}
		}
	}

	if (mCurrentState->willReset()){
		chase((Character *)FWApplication::GetInstance()->getBunny());
	}
}

void Cow::changeTarget(Character *target){
	mCurrentState->setTarget(target);
}
