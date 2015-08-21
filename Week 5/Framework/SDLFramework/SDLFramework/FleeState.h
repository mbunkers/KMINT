#ifndef __FleeState__
#define __FleeState__

#include "State.h"
class FleeState :
	public State
{
public:
	FleeState();
	~FleeState();
	void Move(float deltaTime);
	void Update();
};

#endif