#include "Cow.h"
#include "WanderingState.h"
#include "SleepState.h"
#include "FWApplication.h"
#include "SDL_render.h"
#include "Instance.h"

Cow::Cow(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;

	mSpeed = 100;
	mMass = 1.0;
	mMaxSpeed = 150;
	mMaxForce = 400;
	mMaxTurnRate = 1;

	mSteering = new SteeringBehaviors(this);
	respawn();
}


Cow::~Cow(){
}

void Cow::Update(float deltaTime){
	Character::Update(deltaTime);
	mCurrentState->Update();
}

void Cow::defaultState(){
	mSteering->wanderOn();
	wander();
}

void Cow::respawn(){
	mVelocity = SVector2D(0, 0);
	mHeading = SVector2D(1, 0);
	mSide = SVector2D(1, 0);
	setPosition(FWApplication::GetInstance()->bunnySpawnPoint());
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
		chanceCalculation += chanceOptions.at(i);
		if (chance < chanceCalculation){
			switch (i){
			case 0:
				// Flee from bunny
				break;
			case 1:
				// Flee from bunny and search for pill
				// When got pill, Pass SVector(0,0) but is invincible: Create Invincible state which should be in search state
				break;
			case 2:
				// Pass SVector2D(0,0): Should be in Hide state
				break;
			case 3:
				// Flee from bunny and search for weapon
				// When got weapon, hide: Should be in search state
				break;
			default:
				break;
			}
			return;
		}
	}
	
}

void Cow::changeTarget(Character *target){
	mCurrentState->setTarget(target);
}

