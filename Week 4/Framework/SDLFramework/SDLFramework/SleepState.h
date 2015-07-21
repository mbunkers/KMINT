#pragma once
#include "State.h"
class SleepState :
	public State
{
public:
	SleepState();
	~SleepState();
	void Move();
};

