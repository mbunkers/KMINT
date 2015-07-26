#include "Bunny.h"
#include "WanderingState.h"
#include "SpeedWanderingState.h"


Bunny::Bunny(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mCurrentState = new WanderingState();
	mCurrentState->mOwner = this;
}


Bunny::~Bunny()
{
}

void Bunny::move(){
	mCurrentState->Move();
}

void Bunny::changeState(){
	if (dynamic_cast<WanderingState *>(mCurrentState)){
		mCurrentState = new SpeedWanderingState();
	}
	else {
		if (dynamic_cast<SpeedWanderingState *>(mCurrentState)){
			mCurrentState = new WanderingState();
		}
	}
	mCurrentState->mOwner = this;
}
