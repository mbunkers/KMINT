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
		else {
			if (dynamic_cast<WanderingState *>(mCurrentState)){
				search((Item *)FWApplication::GetInstance()->getItem(), 100, 100, 100);
			}
		}
	}
}

void Cow::Update(float dt){
}

void Cow::changeTarget(Character *target){
	mCurrentState->setTarget(target);
}
