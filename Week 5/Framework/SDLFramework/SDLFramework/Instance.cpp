#include "Instance.h"
#include "FWApplication.h"
#include <cstdlib>
#include <ctime>

Instance::Instance(){

	mCow = new Cow(FWApplication::GetInstance()->LoadTexture("cow-1.png"), nullptr);
	mBunny = new Bunny(FWApplication::GetInstance()->LoadTexture("rabbit-2.png"), nullptr);
	mWeapon = new Item(FWApplication::GetInstance()->LoadTexture("rabbit-2.png"));
	mPill = new Item(FWApplication::GetInstance()->LoadTexture("rabbit-2.png"));

	mWeapon->mIsWeapon = true;
	mBunny->chase(mCow);
	mBunny->mSteering->setTarget(mCow);
	mCow->wander();
	mCow->mSteering->setTarget(mCow);

	addToWorld();
}


Instance::~Instance(){

}

// Random for first run
void Instance::setCowStateChance(){
	// 4 random numbers between 10 and 30

	int total = 0;
	vector<int> stateChances = vector<int>();
	for (int i = 0; i < 4; i++){
		int randomChance = rand() % (31 - 10) + 10;
		total += randomChance;
		stateChances.push_back(randomChance);
	}

	// Normalize these numbers
	for (size_t i = 0; i < stateChances.size(); i++){
		stateChances.at(i) *= 100 / total;
	}

	setCowStateChance(stateChances[0], stateChances[1], stateChances[2], stateChances[3]);
}

// Inheritance from previous generation
void Instance::setCowStateChance(int flee, int fleeAndSearchPill, int hide, int fleeAndSearchWeapon){

}

void Instance::addToWorld(){
	FWApplication::GetInstance()->AddRenderable(mCow);
	FWApplication::GetInstance()->AddRenderable(mBunny);
	FWApplication::GetInstance()->AddRenderable(mWeapon);
	FWApplication::GetInstance()->AddRenderable(mPill);
}

void Instance::removeFromWorld(){
	FWApplication::GetInstance()->RemoveRenderable(mCow);
	FWApplication::GetInstance()->RemoveRenderable(mBunny);
	FWApplication::GetInstance()->RemoveRenderable(mWeapon);
	FWApplication::GetInstance()->RemoveRenderable(mPill);
}
