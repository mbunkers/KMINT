#ifndef __CHASESTATE__
#define __CHASESTATE__


#include "State.h"
class ChaseState : public State{
public:
	ChaseState();
	~ChaseState();

	void Update();
	void Move(float deltaTime);
};

#endif