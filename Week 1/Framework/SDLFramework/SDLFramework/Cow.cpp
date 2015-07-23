#include "Cow.h"

Cow::Cow(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mCurrentState = new ChaseState();
	mCurrentState->mOwner = this;
}


Cow::~Cow(){
}

void Cow::move(){
	mCurrentState->Move();
}

void Cow::changeTarget(Character *target){
	mCurrentState->setTarget(target);
}
