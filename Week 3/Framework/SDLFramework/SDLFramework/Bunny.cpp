#include "Bunny.h"
#include "WanderingState.h"
#include "SearchState.h"
#include "FleeState.h"
#include "ChaseState.h"
#include "SDL_render.h"

Bunny::Bunny(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mCurrentState = new WanderingState();
	mCurrentState->mOwner = this;
	SDL_SetTextureColorMod(texture, 255, 0, 255);
}


Bunny::~Bunny(){
}

void Bunny::move(){
	mCurrentState->Move();
}

void Bunny::changeState(){
	SDL_Texture *texture = getTexture();
	if (dynamic_cast<WanderingState *>(mCurrentState)){
		if (mCurrentLocation->mNeighbours.size() == 2){
			// Flee state
			mCurrentState = new FleeState();
			mCurrentState->mOwner = this;
			SDL_SetTextureColorMod(texture, 0, 0, 0);
		}
		else {
			// Change of 50%
			mCurrentState = new SearchState();
			mCurrentState->mOwner = this;
			int random = (0 + rand() % (int)2);
			if (random == 0){
				mCurrentState->mTarget = FWApplication::GetInstance()->getItem();
				SDL_SetTextureColorMod(texture, 255, 255, 255);
			}
			else {
				mCurrentState->mTarget = FWApplication::GetInstance()->getItem();
				SDL_SetTextureColorMod(texture, 255, 255, 255);
			}
		}
		//move();
	}
	else if (dynamic_cast<FleeState *>(mCurrentState)){
		mCurrentState = new WanderingState();
		mCurrentState->mOwner = this;
		SDL_SetTextureColorMod(texture, 255, 0, 255);
	}
	else if (dynamic_cast<SearchState *>(mCurrentState)){
		if (mCurrentLocation->mItem == mCurrentState->mTarget){
			mCurrentState = new ChaseState();
			mCurrentState->mOwner = this;
			mCurrentState->mTarget = FWApplication::GetInstance()->getCow();
			SDL_SetTextureColorMod(texture, 0, 255, 0);
		}
		else {
			mCurrentState = new WanderingState();
			mCurrentState->mOwner = this;
			SDL_SetTextureColorMod(texture, 255, 0, 255);
		}
	}
	else if (dynamic_cast<ChaseState *>(mCurrentState)){
		mCurrentState = new WanderingState();
		mCurrentState->mOwner = this;
		SDL_SetTextureColorMod(texture, 255, 0, 255);
	}
}
