#ifndef __WANDERINGSTATE__
#define __WANDERINGSTATE__

#include "State.h"
class WanderingState : public State{
public:
	WanderingState();
	~WanderingState();
	void Move(float deltaTime);
	void Update();
};

#endif
