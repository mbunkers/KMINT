#include "Cow.h"
#include "WanderingState.h"
#include "SleepState.h"
#include "FWApplication.h"
#include "SDL_render.h"

Cow::Cow(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
	mCurrentState = new ChaseState();
	mCurrentState->mTarget = FWApplication::GetInstance()->getBunny();
	SDL_SetTextureColorMod(texture, 0, 255, 0);
	mCurrentState->mOwner = this;

	mVelocity = SVector2D(0, 0);
	mHeading = SVector2D(1, 0);
	mSide = SVector2D(1, 0);

	mSpeed = 100;
	mMass = 1.0;
	mMaxSpeed = 150;
	mMaxForce = 200;
	mMaxTurnRate = 1;

	mSteering = new SteeringBehaviors(this);
	mSteering->setTarget((Character *)FWApplication::GetInstance()->getBunny());
	mSteering->persuitOn();
}


Cow::~Cow(){
}

//void Cow::Update(float deltaTime){
//	move();
//}

void Cow::move(){
	mCurrentState->Move(10);
}

void Cow::wakeup(){
	SDL_Texture *texture = getTexture();
	mCurrentState = new ChaseState();
	mCurrentState->mTarget = FWApplication::GetInstance()->getBunny();
	SDL_SetTextureColorMod(texture, 0, 255, 0);
	mCurrentState->mOwner = this;
}

void Cow::sleep(){
	SDL_Texture *texture = getTexture();
	mCurrentState = new SleepState();
	mCurrentState->mOwner = this;
	SDL_SetTextureColorMod(texture, 100, 100, 100);
}

void Cow::changeState(){
	SDL_Texture *texture = getTexture();
	//if (dynamic_cast<ChaseState *>(mCurrentState)){
	//	mCurrentState = new WanderingState();
	//	mStateChangeCounter = 3;
	//	SDL_SetTextureColorMod(texture, 255, 0, 255);
	//}
	//else {
	//	if (dynamic_cast<SearchState *>(mCurrentState)){
	//		mCurrentState = new ChaseState();
	//		mCurrentState->mTarget = FWApplication::GetInstance()->getBunny();
	//		SDL_SetTextureColorMod(texture, 0, 255, 0);
	//	}
	//	else {
	//		if (dynamic_cast<WanderingState *>(mCurrentState)){
	//			mCurrentState = new SearchState();
	//			mCurrentState->mTarget = FWApplication::GetInstance()->getItem();
	//			SDL_SetTextureColorMod(texture, 0, 255, 255);
	//		}
	//	}
	//}

	mCurrentState->mOwner = this;
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
