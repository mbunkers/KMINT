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

	mVelocity = SVector2D(0, 0);
	mHeading = SVector2D(1, 0);
	mSide = SVector2D(1, 0);

	mSpeed = 100;
	mMass = 1;
	mMaxSpeed = 150;
	mMaxForce = 400;
	mMaxTurnRate = 1;

	mSteering = new SteeringBehaviors(this);
	mSteering->wanderOn();
}


Bunny::~Bunny(){
}

void Bunny::Update(float deltaTime){
	Character::Update(deltaTime);

	SVector2D toPursuer = mSteering->target()->position() - position();

	if (dynamic_cast<WanderingState *>(mCurrentState)){
		if (hasThreat(toPursuer)){
			mSpeed = 150;
			mMaxSpeed = 250;
			flee();
			mCurrentState->Update();
		}

		return;
	}

	if (dynamic_cast<FleeState *>(mCurrentState)){
		if (isSafe(toPursuer)){
			mMaxSpeed = 150;
			mSpeed = 100;
			wander();
		}
		mCurrentState->Update();
		return;
	}
}

double Bunny::distanceToPersuer(SVector2D distanceVector){
	return distanceVector.LengthSq();
}

bool Bunny::isSafe(SVector2D distance){
	return distanceToPersuer(distance) > pow(mSafeRange, 2);
}

bool Bunny::hasThreat(SVector2D distance){
	return distanceToPersuer(distance) < pow(mThreatRange, 2);
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
		mCurrentState = new WanderingState();
		wander();
	}
}
