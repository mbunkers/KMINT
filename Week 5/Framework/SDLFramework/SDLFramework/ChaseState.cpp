#include "ChaseState.h"
#include "AStar.h"
#include "FWApplication.h"
#include <SDL.h>
#include "FleeState.h"
#include "SearchState.h"

ChaseState::ChaseState() : State(){
	mMoveTarget = true;
}


ChaseState::~ChaseState(){
}

void ChaseState::Update(){
	if (mOwner->CheckCollision(mOwner->mSteering->target())){
		if (dynamic_cast<FleeState *>(mOwner->mSteering->target()->mCurrentState) || dynamic_cast<SearchState *>(mOwner->mSteering->target()->mCurrentState)){
			mOwner->respawn();
			mOwner->mSteering->target()->respawn();
			// Owner gets 10 points
		}
		else {
			// TODO: Hide
			if (dynamic_cast<FleeState *>(mOwner->mSteering->target()->mCurrentState)){
				mOwner->respawn();
				mOwner->mSteering->target()->respawn();
			}
		}
	}

}

void ChaseState::Move(float deltaTime){

}