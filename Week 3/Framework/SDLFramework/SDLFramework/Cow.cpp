#include "Cow.h"
#include "WanderingState.h"
#include "FWApplication.h"
#include "SDL_render.h"

Cow::Cow(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mCurrentState = new WanderingState();
	SDL_SetTextureColorMod(texture, 255, 0, 255);
	mCurrentState->mOwner = this;
}


Cow::~Cow(){
}

void Cow::move(){
	if (dynamic_cast<WanderingState *>(mCurrentState)){
		mStateChangeCounter--;
		if (mStateChangeCounter < 0){
			changeState();
		}
	}
	mCurrentState->Move();
}

void Cow::changeState(){
	SDL_Texture *texture = getTexture();
	if (dynamic_cast<ChaseState *>(mCurrentState)){
		mCurrentState = new WanderingState();
		mStateChangeCounter = 3;
		SDL_SetTextureColorMod(texture, 255, 0, 255);
	}
	else {
		if (dynamic_cast<SearchState *>(mCurrentState)){
			mCurrentState = new ChaseState();
			mCurrentState->mTarget = FWApplication::GetInstance()->getBunny();
			SDL_SetTextureColorMod(texture, 0, 255, 0);
		}
		else {
			if (dynamic_cast<WanderingState *>(mCurrentState)){
				mCurrentState = new SearchState();
				mCurrentState->mTarget = FWApplication::GetInstance()->getItem();
				SDL_SetTextureColorMod(texture, 0, 255, 255);
			}
		}
	}

	mCurrentState->mOwner = this;
}

void Cow::Update(float dt){
}

void Cow::changeTarget(Character *target){
	mCurrentState->setTarget(target);
}

Node* Cow::moveToNextLocation(Node *startNode, Node *targetNode){
	reset(startNode, targetNode);
	return mAStar->getNextNode();
}

void Cow::reset(Node *startNode, Node *targetNode){
	delete mAStar;
	mAStar = new AStar(startNode, targetNode);
}
