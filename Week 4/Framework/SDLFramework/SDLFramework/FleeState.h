#pragma once
#include "State.h"
class FleeState :
	public State
{
public:
	FleeState();
	~FleeState();
	void Move();
};

