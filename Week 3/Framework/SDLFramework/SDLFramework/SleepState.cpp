#include "SleepState.h"


SleepState::SleepState() : State("Aan het slapen"){
	mMoveTarget = false;
}


SleepState::~SleepState(){
}

void SleepState::Move(){
	// Doesn't move
}
