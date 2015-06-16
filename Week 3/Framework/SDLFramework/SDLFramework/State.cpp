#include "State.h"

State::State()
{
}


State::~State()
{
}

void State::setTarget(Character *target){
	mTarget = (IGameObject *)target;
}

void State::Move(){

}

void State::Update(){

}
