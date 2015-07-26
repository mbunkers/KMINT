#include "State.h"

State::State(string name){
	mName = name;
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

string State::name(){
	return mName;
}
