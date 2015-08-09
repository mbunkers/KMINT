#include "Character.h"
#include <SDL_Rect.h>
#include "FleeState.h"
#include "WanderingState.h"
#include "SearchState.h"
#include "ChaseState.h"
#include "SleepState.h"

Character::Character(SDL_Texture *texture){
	SetTexture(texture);
	SetSize(70, 70);
	mMaxForce = 400;
}

Character::~Character(){
}

void Character::Draw(){
	IGameObject::Draw();
}

SDL_Texture * Character::getTexture(){
	return GetTexture();
}

void Character::Update(float deltaTime){
	mTimeElapsed = deltaTime;
	SVector2D steeringForce = mSteering->calculate();
	SVector2D acceleration = steeringForce / mMass;
	acceleration = acceleration * deltaTime;

	mVelocity = mVelocity + acceleration;

	mVelocity.Truncate(mMaxSpeed);

	SVector2D newPosition = position();
	newPosition = newPosition + (mVelocity * deltaTime);
	setPosition(newPosition);

	if (mVelocity.LengthSq() > 0.00000001){
		mHeading = Vec2DNormalize(mVelocity);
		mSide = mHeading.Perp();
	}

	SVector2D position(GetBoundingBox().x, GetBoundingBox().y);
	WrapAround(position, 800, 600);
	setPosition(position);
}

SVector2D Character::position(){
	return SVector2D(GetBoundingBox().x, GetBoundingBox().y);
}

void Character::setNewPosition(int x, int y){
	SetOffset(x, y);
}
void Character::setPosition(SVector2D position){
	SetOffset((uint32_t)position.x, (uint32_t)position.y);
}

void Character::changeState(){

}

void Character::defaultState(){
	wander();
}

void Character::respawn(){

}

void Character::wakeup(){
	wander();
}

void Character::flee(){
	mCurrentState = new FleeState();
	mCurrentState->mOwner = this;
	mItem = nullptr;
}

void Character::sleep(){
	mCurrentState = new SleepState();
	mCurrentState->mOwner = this;
}

void Character::wakeup(Character *target){
	chase(target);
}

void Character::search(class Item *item, int r, int g, int b){
	mCurrentState = new SearchState();
	mCurrentState->mOwner = this;
	mItem = item;
	mCurrentState->mTarget = mItem;
}

void Character::chase(Character *target){
	mCurrentState = new ChaseState();
	mCurrentState->mOwner = this;
	if (target != nullptr){
		mCurrentState->mTarget = target;
	}
}

void Character::wander(){
	mCurrentState = new WanderingState();
	mCurrentState->mOwner = this;
	mItem = nullptr;
}

void Character::speedUp(){
	mSpeed++;
}
void Character::speedDown(){
	mSpeed--;
}
