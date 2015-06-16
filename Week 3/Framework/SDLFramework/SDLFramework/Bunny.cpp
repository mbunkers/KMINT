#include "Bunny.h"
#include "WanderingState.h"


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
