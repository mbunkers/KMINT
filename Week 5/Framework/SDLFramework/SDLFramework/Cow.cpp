#include "Cow.h"
#include "WanderingState.h"
#include "SleepState.h"
#include "FWApplication.h"
#include "SDL_render.h"
#include "Instance.h"

Cow::Cow(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;

	mSpeed = 50;
	mMass = 1.0;
	mMaxSpeed = 150;
	mMaxForce = 400;
	mMaxTurnRate = 1;

	mSteering = new SteeringBehaviors(this);
	respawn(true);
}


Cow::~Cow(){
}

void Cow::Update(float deltaTime){
	Character::Update(deltaTime);
	mCurrentState->Update();
}

void Cow::defaultState(){
	mSteering->reset();
	mSteering->wanderOn();
	wander();
}

void Cow::respawn(bool newState){
	mVelocity = SVector2D(1, 0);
	mHeading = SVector2D(1, 0);
	mSide = SVector2D(1, 0);
	setPosition(FWApplication::GetInstance()->cowSpawnPoint());
	if (newState){
		respawn();
	}
}

void Cow::respawn(){
	defaultState();
}

void Cow::move(){
	mCurrentState->Move(10);
}

void Cow::changeState(){
	int chance = rand() % 101;

	vector<int> chanceOptions = vector<int>();
	chanceOptions.push_back(fleeChance());
	chanceOptions.push_back(fleePillSearchChance());
	chanceOptions.push_back(hideChance());
	chanceOptions.push_back(fleeAndWeaponSearchChance());

	int chanceCalculation = 0;
	for (size_t i = 0; i < chanceOptions.size(); i++){
		int between = chanceCalculation;
		chanceCalculation += chanceOptions.at(i);
		if (between < chance && chanceCalculation > chance){
			Instance *instance = FWApplication::GetInstance()->instance(mID);
			switch (i){
			case 0:
				mSteering->reset();
				mSteering->fleeOn();
				return;
			case 1:
				mSteering->reset();
				mSteering->evadeOn();
				mSteering->seekOn();
				mSteering->setTarget(instance->mPill->position());
				search(instance->mPill, 0,0,0);
				return;
			case 2:
				mSteering->reset();
				hide();
				return;
			case 3:
				mSteering->reset();
				mSteering->evadeOn();
				mSteering->seekOn();
				mSteering->setTarget(instance->mWeapon->position());
				search(instance->mWeapon, 0, 0, 0);
				return;
			default:
				mSteering->reset();
				mSteering->evadeOn();
				mSteering->seekOn();
				mSteering->setTarget(instance->mPill->position());
				search(instance->mPill, 0, 0, 0);
				return;
			}
		}
	}
	
}

void Cow::changeTarget(Character *target){
	mCurrentState->setTarget(target);
}

