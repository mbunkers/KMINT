#include "Bunny.h"
#include "WanderingState.h"
#include "SearchState.h"
#include "FleeState.h"
#include "ChaseState.h"
#include "SleepState.h"
#include "SDL_render.h"

Bunny::Bunny(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mCurrentState = new WanderingState();
	mCurrentState->mOwner = this;
	SDL_SetTextureColorMod(texture, 255, 0, 255);
	mStateChangeCounter = 5;

	mVelocity = SVector2D(0, 0);
	mHeading = SVector2D(1, 0);
	mSide = SVector2D(1, 0);

	mSpeed = 100;
	mMass = 1;
	mMaxSpeed = 300;
	mMaxForce = 400;
	mMaxTurnRate = 1;

	mSteering = new SteeringBehaviors(this);
	mSteering->wanderOn();
}


Bunny::~Bunny(){
}

void Bunny::Update(float deltaTime){
	Character::Update(deltaTime);
	SVector2D evaderPosition = ((Character *)FWApplication::GetInstance()->getCow())->position();
	double distance = evaderPosition.Distance(position());

	if (distance > 300){
		mSpeed = 100;
		mCurrentState = new WanderingState();
		mCurrentState->mOwner = this;
		SDL_SetTextureColorMod(GetTexture(), 255, 0, 255);
	}
	else {
		if (distance < 200){
			mSpeed = 200;
			flee();
		}
	}
	mCurrentState->Update();
}

void Bunny::move(){
	mCurrentState->Move(10);
	mStateChangeCounter--;

	if (dynamic_cast<SleepState *>(((Character *)FWApplication::GetInstance()->getCow())->mCurrentState)){
		if (mStateChangeCounter < 0){
			changeState();
			Character *cow = (Character *)FWApplication::GetInstance()->getCow();
			cow->wakeup();
		}
	}
}

void Bunny::flee(){
	SDL_Texture *texture = getTexture();
	// Flee state
	mCurrentState = new FleeState();
	mCurrentState->mOwner = this;
	SDL_SetTextureColorMod(texture, 0, 0, 0);
	mItem = nullptr;
	mStateChangeCounter = 5;
}

void Bunny::changeState(){
	SDL_Texture *texture = getTexture();
	if (dynamic_cast<WanderingState *>(mCurrentState)){
		if (mCurrentLocation->mNeighbours.size() == 2){
			// Flee state
			mCurrentState = new FleeState();
			mCurrentState->mOwner = this;
			SDL_SetTextureColorMod(texture, 0, 0, 0);
			mItem = nullptr;
		}
		else {
			// Change of 50%
			mCurrentState = new SearchState();
			mCurrentState->mOwner = this;
			int random = (0 + rand() % (int)2);
			if (random == 0){
				mCurrentState->mTarget = FWApplication::GetInstance()->getItem();
				mItem = (Item *)mCurrentState->mTarget;
				SDL_SetTextureColorMod(texture, 255, 255, 255);
			}
			else {
				mCurrentState->mTarget = FWApplication::GetInstance()->getWeapon();
				mItem = (Item *)mCurrentState->mTarget;
				SDL_SetTextureColorMod(texture, 200, 200, 200);
			}
		}
		//move();
	}
	else if (dynamic_cast<FleeState *>(mCurrentState)){
		mCurrentState = new WanderingState();
		mCurrentState->mOwner = this;
		SDL_SetTextureColorMod(texture, 255, 0, 255);
		mItem = nullptr;
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
			mItem = nullptr;
		}
	}
	else if (dynamic_cast<ChaseState *>(mCurrentState)){
		mCurrentState = new WanderingState();
		mCurrentState->mOwner = this;
		SDL_SetTextureColorMod(texture, 255, 0, 255);
		mItem = nullptr;
	}
}
