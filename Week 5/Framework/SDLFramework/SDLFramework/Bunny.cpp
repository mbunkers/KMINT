#include "Bunny.h"
#include "WanderingState.h"
#include "SearchState.h"
#include "FleeState.h"
#include "ChaseState.h"
#include "SleepState.h"
#include "SDL_render.h"
#include "Instance.h"

Bunny::Bunny(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mStateChangeCounter = 5;

	mSpeed = 200;
	mMass = 1;
	mMaxSpeed = 300;
	mMaxForce = 400;
	mMaxTurnRate = 1;

	respawn();
	mSteering = new SteeringBehaviors(this);
}


Bunny::~Bunny(){
	
}

void Bunny::defaultState(){
	Instance *instance = FWApplication::GetInstance()->instance(mID);
	if (instance != nullptr){
		mSteering->setTarget(instance->mCow);
		mSteering->persuitOn();
		chase(instance->mCow);
	}
}
void Bunny::respawn(){
	mVelocity = SVector2D(0, 0);
	mHeading = SVector2D(1, 0);
	mSide = SVector2D(1, 0);
	setPosition(FWApplication::GetInstance()->bunnySpawnPoint());
	defaultState();
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

void Bunny::flee(){
	Character::flee();
	mStateChangeCounter = 5;
}

