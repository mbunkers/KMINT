#include "ChaseState.h"
#include "AStar.h"
#include "FWApplication.h"
#include <SDL.h>

ChaseState::ChaseState() : State(){
	mMoveTarget = true;
}


ChaseState::~ChaseState(){
}

void ChaseState::Move(float deltaTime){

}