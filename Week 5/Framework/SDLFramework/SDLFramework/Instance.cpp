#include "Instance.h"
#include "FWApplication.h"
#include <cstdlib>
#include <ctime>

Instance::Instance(int ID){

	mID = ID;

	mCow = new Cow(FWApplication::GetInstance()->LoadTexture("cow-1.png"), nullptr);
	mBunny = new Bunny(FWApplication::GetInstance()->LoadTexture("rabbit-2.png"), nullptr);
	mWeapon = new Item(FWApplication::GetInstance()->LoadTexture("gun - metal.png"));
	mPill = new Item(FWApplication::GetInstance()->LoadTexture("pill.png"));

	mWeapon->mIsWeapon = true;
	mBunny->chase(mCow);
	mBunny->mSteering->setTarget(mCow);
	mCow->wander();
	mCow->mSteering->setTarget(mCow);

	mCow->mID = ID;
	mBunny->mID = ID;
	mPill->mID = ID;
	mWeapon->mID = ID;

	mCow->setNewPosition(100, 150);
	mBunny->setNewPosition(400, 300);

	defineColor();
	addToWorld();
}


Instance::~Instance(){

}

void Instance::defineColor(){
	vector<IGameObject *> objects = vector<IGameObject *>();
	objects.push_back(mBunny);
	objects.push_back(mCow);
	objects.push_back(mPill);
	objects.push_back(mWeapon);

	for (size_t i = 0; i < objects.size(); i++){
		SDL_Texture *texture = objects.at(i)->GetTexture();

		switch (mID){
		case 0:
			SDL_SetTextureColorMod(texture, 0, 0, 0);
			break;
		case 1:
			SDL_SetTextureColorMod(texture, 255, 0, 0);
			break;
		case 2:
			SDL_SetTextureColorMod(texture, 0, 255, 0);
			break;
		case 3: 
			SDL_SetTextureColorMod(texture, 0, 0, 255);
			break;
		default:
			break;
		}
	}
}

void Instance::setDefaultStates(){
	mCow->defaultState();
	mBunny->defaultState();
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
