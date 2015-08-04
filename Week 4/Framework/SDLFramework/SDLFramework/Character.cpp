#include "Character.h"
#include <SDL_Rect.h>

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

void Character::flee(){

}

void Character::sleep(){

}

void Character::wakeup(){

}

void Character::speedUp(){
	mSpeed++;
}
void Character::speedDown(){
	mSpeed--;
}
