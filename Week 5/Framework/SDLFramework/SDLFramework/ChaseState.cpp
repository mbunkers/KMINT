#include "ChaseState.h"
#include "AStar.h"
#include "FWApplication.h"
#include <SDL.h>
#include "FleeState.h"
#include "SearchState.h"
#include "HideState.h"
#include "InvincibleState.h"

ChaseState::ChaseState() : State(){
	mMoveTarget = true;
}


ChaseState::~ChaseState(){
}

void ChaseState::Update(){
	if (mOwner->CheckCollision(mOwner->mSteering->target())){
		if (dynamic_cast<FleeState *>(mOwner->mSteering->target()->mCurrentState) || dynamic_cast<SearchState *>(mOwner->mSteering->target()->mCurrentState)){
			mOwner->mTargetPoints += 10;
			mOwner->respawn();
			mOwner->mSteering->target()->respawn(true);
		}
		else {
			if (dynamic_cast<HideState *>(mOwner->mSteering->target()->mCurrentState)){
				mOwner->respawn();
				mOwner->mSteering->target()->respawn(true);
			}
			else {
				if (dynamic_cast<InvincibleState *>(mOwner->mSteering->target()->mCurrentState)){
					mOwner->respawn();
					mOwner->mSteering->target()->respawn(false);
					mOwner->mSteering->target()->mTargetPoints += 1;
				}
			}
		}
	}

}

void ChaseState::Move(float deltaTime){

}